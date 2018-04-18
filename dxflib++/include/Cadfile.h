#pragma once
#include "dxflib++/include/entities/line.h"
#include "dxflib++/include/entities/lwpolyline.h"
#include "entities/hatch.h"
#include <vector>
#include "entities/text.h"

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
		std::vector<entities::text> basic_text;        // TEXT Entities

		// Public Interface
		std::string get_filename() const { return std::string{ filename_ }; } // Returns the filename of the cadfile
		const std::vector<std::string>& get_data() const { return data_; }    // Returns the data from the DXF file


	private:
		
		void read_file();  // Reads the file that is stored in filename_
		void parse_data(); // Main parse function for the dxf file: iterates through the data_ vector and
		void linker();     // Links entities to other entities, noteably hatches and polyline

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
			const char* text{ "TEXT" };
		};
	}
}
