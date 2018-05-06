#include "dxflib++/include/reader.h"

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
