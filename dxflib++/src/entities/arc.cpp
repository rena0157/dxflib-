/*
 * arc.cpp
 * By: Adam Renaud
 * 2018
 * Purpose: To define the decarlations made in the arc.h file for the arc_buffer and the
 * arc enity class
 */
#include "dxflib++/include/entities/arc.h"
#include "dxflib++/include/mathlib.h"
#include <valarray>

int dxflib::entities::arc_buffer::parse(const std::string& cl, const std::string& nl)
{
	int code{entity_buffer_base::parse(cl, nl)}; // group code of the current line
	if (code == -1)
		return 1;
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

	case group_codes::arc::is_ccw:
		is_ccw = std::stoi(nl);
		return 1;
	default:
		return 0;
	}
}

void dxflib::entities::arc_buffer::free()
{
	entity_buffer_base::free();
	thickness = 0;
	center_point_x = 0;
	center_point_y = 0;
	center_point_z = 0;
	radius = 0;
	start_angle = 0;
	end_angle = 0;
}

dxflib::entities::arc::arc(arc_buffer& ab):
	center_point_(ab.center_point_x, ab.center_point_y, ab.center_point_z),
	radius_(ab.radius), thickness_(ab.thickness), start_angle_(ab.start_angle),
	end_angle_(ab.end_angle), is_ccw_(ab.is_ccw)
{
	calc_other_points();
}

void dxflib::entities::arc::calc_other_points()
{
	start_point_ = vertex{
		center_point_.x + radius_ * cos(mathlib::deg2_rad(start_angle_)),
		center_point_.y + radius_ * sin(mathlib::deg2_rad(start_angle_)), center_point_.z
	};
	end_point_ = vertex{
		center_point_.x + radius_ * cos(mathlib::deg2_rad(end_angle_)),
		center_point_.y + radius_ * sin(mathlib::deg2_rad(end_angle_)), center_point_.z
	};
}
