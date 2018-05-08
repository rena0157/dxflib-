#include "dxflib++/include/reader.h"
#include <string>

dxflib::utilities::dxf_reader::dxf_reader(const char* path):
	path_(path), is_binary_(false), bin_data_(nullptr)
{
	// Open the DXF file and read in 22 bytes of data to check if the file is
	// Binary or not
	dxf_file_.open(path, std::ios_base::binary | std::ios_base::ate);
	auto* data = new char[sentenial_size];
	if (dxf_file_.good())
	{
		file_size_ = dxf_file_.tellg(); // get file size
		dxf_file_.seekg(0, std::ios_base::beg);
		dxf_file_.read(data, sentenial_size);
	}
	// Compare the sentenial with a binary sentenial
	if (strcmp(data, sentenial) == 0)
	{
		is_binary_ = true;
	}

	// Clean up
	delete[] data;
	data = nullptr;
}

dxflib::utilities::dxf_reader::~dxf_reader()
{
	if (is_binary_)
	{
		delete[] bin_data_;
		bin_data_ = nullptr;
	}
}


std::vector<std::string> dxflib::utilities::dxf_reader::ascii_reader()
{
	// Throw exception if using the wrong reader
	if (is_binary_)
		throw reader_error("Trying to read a binary file with the ascii reader");
	std::vector<std::string> ascii_data;
	// Close and reopen the file in normal mode
	dxf_file_.close();
	dxf_file_.open(path_.c_str());

	// Read the data
	for (std::string line; std::getline(dxf_file_, line);)
	{
		ascii_data.push_back(line);
	}
	return ascii_data;
}

void dxflib::utilities::dxf_reader::binary_reader()
{
	// Throw exception if using the wrong reader
	if (!is_binary_)
		throw reader_error("Trying to read a ascii file with the binary reader");
	// Read file into memory
	bin_data_ = new char[file_size_];
	dxf_file_.read(bin_data_, file_size_);
}

void dxflib::utilities::dxf_reader::get_data(char* destination, size_t* start, size_t num_bytes) const
{
	// The starting point cannot be a null pointer
	if (start == nullptr)
		throw reader_error("Start cannot be a null pointer");

	// if the starting point plus the number of bytes is greater than the file size then
	// There should be an error
	if (*start + num_bytes > file_size_)
		throw reader_error("access data error - index error");
	size_t buf_pos{ 0 };

	// Iterate through the data array and extract data into the buffer
	for (size_t data_pos{0}; data_pos < *start + num_bytes; ++data_pos)
		destination[buf_pos++] = bin_data_[data_pos];
	*start = num_bytes - 1; // move the pointer
}
