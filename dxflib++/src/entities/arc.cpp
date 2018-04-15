#include "dxflib++/include/entities/arc.h"

int dxflib::entities::arc_buffer::parse(const std::string& cl, const std::string& nl)
{
	if (entity_buffer_base::parse(cl, nl))
		return 1;

	int code{}; // group code of the current line

	// see if the current line is a group code
	try
	{
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

	// Parse switch;
	switch (static_cast<group_codes::arc>(code))
	{
	case group_codes::arc::thickness:
		thickness = std::stod(nl);
		return 1;

	case group_codes::arc::center_point_x:
		center_point_x = std::stod(nl);
		return 1;

	case group_codes::arc::center_point_y:
		center_point_y = std::stod(nl);
		return 1;

	case group_codes::arc::center_point_z:
		center_point_z = std::stod(nl);
		return 1;

	case group_codes::arc::radius:
		radius = std::stod(nl);
		return 1;

	case group_codes::arc::start_angle:
		start_angle = std::stod(nl);
		return 1;

	case group_codes::arc::end_angle:
		end_angle = std::stod(nl);
		return 1;
	}
}

void dxflib::entities::arc_buffer::free()
{
	entity_buffer_base::free();
	thickness = 0;
	center_point_x = 0; center_point_y = 0; center_point_z = 0;
	radius = 0; start_angle = 0; end_angle = 0;
}

dxflib::entities::arc::arc(arc_buffer& ab):
	center_point(ab.center_point_x, ab.center_point_y, ab.center_point_z),
	radius(ab.radius), thickness(ab.thickness), start_angle(ab.start_angle),
	end_angle(ab.end_angle), total_angle(end_angle - start_angle)
{
	calc_other_points();
}

void dxflib::entities::arc::calc_other_points()
{
	// TODO: Add this
}
