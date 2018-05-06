#pragma once
#include <fstream>

namespace dxflib::utilities
{
	class dxf_reader
	{
	public:
		explicit dxf_reader(const char* path);
		static constexpr int sentenial_size{ 22 };
		inline static const char* sentenial = "AutoCAD Binary DXF\x0d\x0a\x1a\x00";

		// Publib Interface
		bool is_binary() const { return is_binary_; }
		int get_file_size() const { return static_cast<int>(file_size_); }

	private:
		std::string path_;
		std::ifstream dxf_file_;
		bool is_binary_;
		std::size_t file_size_;
	};
}
