#include "dxflib++/include/Cadfile.h"
#include "dxflib++/include/entities/entity.h"
#include "dxflib++/include/entities/line.h"
#include "dxflib++/include/entities/lwpolyline.h"
#include <fstream>
#include <iostream>
#include <string>

/**
 * \brief cadfile Constructor
 * \param path Path to the DXF file
 */
dxflib::cadfile::cadfile(const char* path) : filename_(path)
{
	read_file();
	parse_data();
}

/**
 * \brief Reads the Dxf File
 */
void dxflib::cadfile::read_file()
{
	std::ifstream fs;

	try
	{
		fs.open(filename_);
		if (fs.good())
		{
			// Preallocating memory
			fs.seekg(0, std::istream::end);
			const size_t size{ static_cast<size_t>(fs.tellg())/sizeof(int64_t) };
			fs.seekg(0, std::istream::beg);
			data_.reserve(size);
			// get data
			for (std::string line; std::getline(fs, line);)
			{
				data_.push_back(std::move(line));
			}
			fs.close();
		}
		else { throw std::ios::failure("File failed to open/read/close"); }
	}
	catch (std::ios::failure& e)
	{
		std::cerr << e.code() << " Error: " << e.what();
		fs.close();
	}
}

/**
 * \brief Parses data in the dxf file
 */
void dxflib::cadfile::parse_data()
{
	// Loop Variables
	entities::entity_types current_entity{entities::entity_types::line }; // Current Entity
	bool extraction_flag{ false };                     // Extraction Flag
	const group_codes::g_common gc;                    // Common Group Codes
	const group_codes::start_markers start_markers;    // Line Group Codes

	// Buffers
	entities::line_buf lb;           // Line Buffer
	entities::lwpolyline_buffer lwb; // Lwpolyline Buffer

	for (int linenum{0}; linenum < static_cast<int>(data_.size()) - 1; ++linenum)
	{
		std::string& cl = data_[linenum];
		std::string& nl = data_[linenum + 1];

		/*
		 * Assignment Path
		 */
		if (!extraction_flag)
		{
			if (cl == start_markers.line)
			{
				extraction_flag = true;
				current_entity = entities::entity_types::line;
				continue;
			}
			if (cl == start_markers.lwpolyline)
			{
				extraction_flag = true;
				current_entity = entities::entity_types::lwpolyline;
				continue;
			}
		}
		/*
		 * Extraction Path
		 */
		if (extraction_flag)
		{
			switch (current_entity)
			{
			case entities::entity_types::line:
				if (lb.parse(cl, nl))
					linenum++;
				break;

			case entities::entity_types::lwpolyline:
				if (lwb.parse(cl, nl))
					linenum++;
				break;
			}
		}
		/*
		 * Build Path
		 */
		if (cl == gc.end_marker && extraction_flag)
		{
			switch (current_entity)
			{
			case entities::entity_types::line:
				lines.emplace_back(lb);
				lb.free();
				extraction_flag = false;
				break;

			case entities::entity_types::lwpolyline:
				lwpolylines.emplace_back(lwb);
				lwb.free();
				extraction_flag = false;
				break;
			}
		}
	}
}

