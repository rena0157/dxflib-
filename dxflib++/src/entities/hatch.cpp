#include "dxflib++/include/entities/hatch.h"
#include <utility>
#include "dxflib++/include/mathlib.h"

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
	if (edge_type == null_edge_type)
	{
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
		case group_codes::hatch::edge_type:
			edge_type = std::stoi(nl);
			return 1;
		case group_codes::hatch::edge_count:
			// TODO: Implement Later
			return 1;
		case group_codes::hatch::solid_fill_color:
			// TODO: Implement
			return 1;
		case group_codes::hatch::hatch_style:
			// TODO: Implement
			return 1;
		case group_codes::hatch::hatch_pattern_type:
			// TODO: Implement
			return 1;
		case group_codes::hatch::pattern_line_count:
			// TODO: Implement
			return 1;
		case group_codes::hatch::seed_count:
			// TODO: Implement
			return 1;
		case group_codes::hatch::offset_vector:
			return 1;
		default:
			return 0;
		}
	}
	// TODO: Need to come back to this
	if (!is_associative)
	{
		switch (static_cast<group_codes::boundary_paths>(edge_type))
		{
		case group_codes::boundary_paths::line:

			switch (static_cast<group_codes::line_path>(code))
			{
			case group_codes::line_path::starting_point_x:
				x_values.push_back(std::stod(nl));
				bulge_values.push_back(geoline::bulge_null);
				return 1;
			
			case group_codes::line_path::ending_point_x:
				x_values.push_back(std::stod(nl));
				bulge_values.push_back(geoline::bulge_null);
				return 1;

			case group_codes::line_path::starting_point_y:
				y_values.push_back(std::stod(nl));
				return 1;

			case group_codes::line_path::ending_point_y:
				y_values.push_back(std::stod(nl));
				edge_type = null_edge_type;
				return 1;

			default: return 0;
			}

		case group_codes::boundary_paths::circular_arc:
			switch (static_cast<group_codes::arc>(code))
			{
			case group_codes::arc::center_point_x:
				center_point_x = std::stod(nl);
				return 1;

			case group_codes::arc::center_point_y:
				center_point_y = std::stod(nl);
				return 1;

			case group_codes::arc::center_point_z:
				center_point_z = std::stod(nl);
				return 1;

			case group_codes::arc::start_angle:
				start_angle = std::stod(nl);
				x_values.push_back(center_point_x + radius * cos(mathlib::deg2_rad(start_angle)));
				y_values.push_back(center_point_y + radius * sin(mathlib::deg2_rad(start_angle)));
				return 1;

			case group_codes::arc::end_angle:
				end_angle = std::stod(nl);
				x_values.push_back(center_point_x + radius * cos(mathlib::deg2_rad(end_angle)));
				x_values.push_back(center_point_y + radius * cos(mathlib::deg2_rad(end_angle)));
				bulge_values.push_back(tan(mathlib::deg2_rad(end_angle - start_angle)));
				return 1;

			case group_codes::arc::is_ccw:
				is_ccw = std::stoi(nl);
				edge_type = null_edge_type;
				return 1;
			default: return 0;
			}
		default: return 0;
		}
	}
	return 0;
}

void dxflib::entities::hatch_buffer::free()
{
	lwpolyline_buffer::free();
	arc_buffer::free();
	elevation_point_x = 0; elevation_point_y = 0; elevation_point_z = 0;
	hatch_pattern = "";
	is_solid = false;
	is_associative = false;
	path_count = 0;
	pattern_angle = 0;
	pattern_scale = 0;
	edge_type = null_edge_type;
}

dxflib::entities::exceptions::no_associated_lwpolyline::no_associated_lwpolyline(std::string error):
	error_(std::move(error))
{

}

dxflib::entities::hatch::hatch(hatch_buffer& hb):
	entity(hb), elevation_(hb.elevation_point_x, hb.elevation_point_y, hb.elevation_point_z),
	hatch_pattern_(hb.hatch_pattern), is_solid_(hb.is_solid), is_associative_(hb.is_associative),
	path_count_(hb.path_count), pattern_angle_(hb.pattern_angle), pattern_scale_(hb.pattern_scale)
{
	if (!is_associative_)
	{
		geolines_ = { geoline::geoline_binder(
		hb.x_values, hb.y_values, hb.bulge_values, true) };
		calc_geometry();
	}
}

const dxflib::entities::lwpolyline* dxflib::entities::hatch::get_lwpolyline() const
{
	// If there is not associated polyline then throw an exception
	if (polyline_ptr_ == nullptr)
		throw exceptions::no_associated_lwpolyline("There is no assocated lwpolyline with: '" + 
			handle_ + "', Cannot return nullptr");
	// If everything checks out then return the polyline pointer
	return polyline_ptr_;
}

double dxflib::entities::hatch::get_area() const
{
	return polyline_ptr_ == nullptr ? area_ : polyline_ptr_->get_area();
}

double dxflib::entities::hatch::get_perimeter() const
{
	return polyline_ptr_ == nullptr ? perimeter_ : polyline_ptr_->get_length();
}

void dxflib::entities::hatch::calc_geometry()
{
	double total_length{ 0 };
	double total_area{ 0 };

	// iterate through all geolines and return a total length & area
	for (const auto& line : geolines_)
	{
		total_length += line.get_length();
		total_area += mathlib::trapz_area(line[0], line[1]);
	}

	// set the total length of the polyline
	perimeter_ = total_length;

	/*
	* Note: Clockwise yeilds a positive area, Counterclockwise drawing yeilds a negative area.
	* Since area is always positive though we take to abs() of the yeild
	*/
	area_ = abs(total_area);
}
