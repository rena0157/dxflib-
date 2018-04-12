#pragma once
#include "dxflib++/include/entities/line.h"
#include "dxflib++/include/entities/lwpolyline.h"
#include <vector>
#include <deque>

namespace dxflib
{
	class cadfile
	{
	public:
		explicit cadfile(const char* path);

		// Entities
		std::vector<entities::line> lines;
		std::vector<entities::lwpolyline> lwpolylines;

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

		struct start_markers
		{
			const char* line{ "LINE" };
			const char* lwpolyline{ "LWPOLYLINE" };
		};
	}
}
