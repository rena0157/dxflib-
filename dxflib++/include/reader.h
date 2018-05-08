#pragma once
#include <fstream>
#include <vector>

namespace dxflib::utilities
{
	class reader_error : std::exception
	{
		std::string message_;
	public:
		explicit reader_error(const char* message) : message_(message)
		{
		};
		char const* what() const override { return message_.c_str(); }
	};

	class dxf_reader
	{
	public:
		// Constructors
		explicit dxf_reader(const char* path);
		~dxf_reader();
		static constexpr int sentenial_size{22};
		inline static const char* sentenial = "AutoCAD Binary DXF\x0d\x0a\x1a\x00";

		// Publib Interface
		bool is_binary() const { return is_binary_; }
		int get_file_size() const { return static_cast<int>(file_size_); }

		// Readers
		std::vector<std::string> ascii_reader();
		void binary_reader();
		void get_data(char* destination, size_t* start, size_t num_bytes) const;

	private:
		std::string path_;
		std::ifstream dxf_file_;
		bool is_binary_;
		std::size_t file_size_;
		char* bin_data_;
	};
}
