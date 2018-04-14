#include "dxflib++/include/entities/hatch.h"

int dxflib::entities::hatch_buffer::parse(const std::string& cl, const std::string& nl)
{
	// call buffer base parse
	if (entity_buffer_base::parse(cl, nl))
		return 1;

	int code{ 0 }; // Group code

	try
	{
		// convert current line to a group code
		if (utilities::is_number(utilities::ltrim_copy(cl)))
			code = std::stoi(cl);
	}
	catch(std::out_of_range&)
	{
		code = -1;
	}
	catch(std::invalid_argument&)
	{
		code = -1;
	}
	// Parse tree
	switch (static_cast<group_codes::hatch>(code))
	{
	case group_codes::hatch::elevation_point_x:
		elevation_point_x = std::stod(nl);
		return 1;

	case group_codes::hatch::elevation_point_y:
		elevation_point_y = std::stod(nl);
		return 1;

	case group_codes::hatch::elevation_point_z:
		elevation_point_z = std::stod(nl);
		return 1;

	case group_codes::hatch::hatch_pattern:
		hatch_pattern = nl;
		return 1;

	case group_codes::hatch::solid_fill_flag:
		is_solid = std::stoi(nl);
		return 1;

	case group_codes::hatch::associativity_flag:
		is_associative = std::stoi(nl);
		return 1;

	case group_codes::hatch::num_paths:
		path_count = std::stoi(nl);
		return 1;

	case group_codes::hatch::pattern_angle:
		pattern_angle = std::stoi(nl);
		return 1;

	case group_codes::hatch::pattern_scale:
		pattern_scale = std::stod(nl);
		return 1;
	default:
		return 0;
	}
}

void dxflib::entities::hatch_buffer::free()
{
	entity_buffer_base::free();
	elevation_point_x = 0; elevation_point_y = 0; elevation_point_z = 0;
	hatch_pattern = "";
	is_solid = false;
	is_associative = false;
	path_count = 0;
	pattern_angle = 0;
	pattern_scale = 0;
}

dxflib::entities::hatch::hatch(hatch_buffer& hb):
	entity(hb), elevation(hb.elevation_point_x, hb.elevation_point_y, hb.elevation_point_z),
	hatch_pattern(hb.hatch_pattern), is_solid(hb.is_solid), is_associative(hb.is_associative),
	path_count(hb.path_count), pattern_angle(hb.pattern_angle), pattern_scale(hb.pattern_scale)
{

}
