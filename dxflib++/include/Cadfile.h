#pragma once
#include "dxflib++/include/entities/line.h"
#include "dxflib++/include/entities/lwpolyline.h"
#include "entities/hatch.h"
#include <vector>

namespace dxflib
{
	/**
	 * \brief the main class for dxf files: contains all other objects
	 */
	class cadfile
	{
	public:
		/**
		 * \brief Constructor for the cadfile class
		 * \param path Path to the DXF file
		 */
		explicit cadfile(const char* path);

		// Entities
		std::vector<entities::line> lines;             // LINE Entities
		std::vector<entities::lwpolyline> lwpolylines; // LWPOLYLINE Entities
		std::vector<entities::hatch> hatches;          // HATCH Entities

	private:
		/**
		 * \brief Reads the file that is stored in filename_
		 */
		void read_file();
		/**
		 * \brief Main parse function for the dxf file: iterates through the data_ vector and
		 * populates the Entities vectors
		 */
		void parse_data();

		const char* filename_;          // Path to the DXF file
		std::vector<std::string> data_; // raw data from the dxf file
	};

	// Group Codes
	namespace group_codes
	{
		/**
		 * \brief common group codes: for all entities
		 */
		struct g_common
		{
			const char* end_marker{ "  0" };
		};

		/**
		 * \brief start markers for entities: AutoCAD LT 2013
		 */
		struct start_markers
		{
			const char* line{ "LINE" };
			const char* lwpolyline{ "LWPOLYLINE" };
			const char* hatch{ "HATCH" };
		};
	}
}
