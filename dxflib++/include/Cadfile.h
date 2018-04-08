#pragma once
#include <vector>
#include "entities/line.h"

namespace dxflib
{
	class cadfile
	{
	public:
		explicit cadfile(const char* path);
		std::vector<line> lines;

	private:
		void read_file();
		void parse_data();

		const char* filename_;
		std::vector<std::string> data_;
	};

	// Group Codes
	namespace group_codes
	{
		struct g_common
		{
			const char* end_marker{ "  0" };
		};

		struct g_line
		{
			const char* start_marker{ "LINE" };
		};
	}
}
