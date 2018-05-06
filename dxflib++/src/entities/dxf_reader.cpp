#include "dxflib++/include/reader.h"
#include <string>

dxflib::utilities::dxf_reader::dxf_reader(const char* path):
	path_(path), is_binary_(false)
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

char* dxflib::utilities::dxf_reader::binary_reader()
{
	// Throw exception if using the wrong reader
	if (!is_binary_)
		throw reader_error("Trying to read a ascii file with the binary reader");
	// Allocate Memory
	auto* binary_data = new char[file_size_];
	// Read file into memory
	dxf_file_.read(binary_data, file_size_);
}
