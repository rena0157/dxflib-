#include "dxflib++/include/entities/lwpolyline.h"
#include "dxflib++/include/mathlib.h"
#include "dxflib++/include/utilities.h"
#include <cassert>

dxflib::entities::geo_line::geo_line(const vertex& v0, const vertex& v1, const double bulge):
	v0(v0), v1(v1), bulge(bulge),
	length(bulge == lwpolyline::bulge_null ? mathlib::distance(v0, v1) : mathlib::distance(v0, v1, bulge))
{

}

int dxflib::entities::lwpolyline_buffer::parse(const std::string& cl, const std::string& nl)
{
	// First send to the buffer base parse function 
	if (entity_buffer_base::parse(cl, nl))
		return 1;

	int code{}; // group code of the current line if one exists

	// See if the current line is a group code
	try
	{
		if (utilities::is_number(utilities::trim(cl)))
			code = std::stoi(cl);
	}
	catch (std::out_of_range&)
	{
		code = -1;
	}
	catch (std::invalid_argument&)
	{
		code = -1;
	}

	// parse swtich
	switch (static_cast<group_codes::lwpolyline>(code))
	{
	case group_codes::lwpolyline::x_value:
		bulge_values.push_back(lwpolyline::bulge_null);
		x_values.push_back(std::stod(nl));
		return 1;

	case group_codes::lwpolyline::y_value:
		y_values.push_back(std::stod(nl));
		return 1;

	case group_codes::lwpolyline::polyline_flag:
		polyline_flag = std::stoi(nl);
		return 1;

	case group_codes::lwpolyline::elevation:
		elevation = std::stod(nl);
		return 1;

	case group_codes::lwpolyline::vertex_count:
		vertex_count = std::stoi(nl);
		return 1;

	case group_codes::lwpolyline::bulge:
		/*
		 * A bulge null is pushed back at the extraction of an x value.
		 * When a bulge is found the bulge null is poped off and
		 * the actual bulge value is pushed back
		 */
		bulge_values.pop_back();
		bulge_values.push_back(std::stod(nl));
		return 1;

	case group_codes::lwpolyline::starting_width:
		starting_width = std::stod(nl);
		return 1;

	case group_codes::lwpolyline::ending_width:
		ending_width = std::stod(nl);
		return 1;

	case group_codes::lwpolyline::width:
		width = std::stod(nl);
		return 1;

	case group_codes::lwpolyline::vertex_id:
		// TODO: Add vertex_id
		return 1;

	default:
		return 0;
	}
}

void dxflib::entities::lwpolyline_buffer::free()
{
	// Vector clearing
	x_values.clear(); x_values.shrink_to_fit();
	y_values.clear(); y_values.shrink_to_fit();
	bulge_values.clear(); bulge_values.shrink_to_fit();

	// Property resetting
	polyline_flag = false;
	elevation = 0;
	vertex_count = 0;
}

dxflib::entities::lwpolyline::lwpolyline(lwpolyline_buffer& lwb) : entity(lwb),
	vertex_count(lwb.vertex_count), is_closed(lwb.polyline_flag), elevation(lwb.elevation),
	starting_width(lwb.starting_width), ending_width(lwb.ending_width), width(lwb.width),
	lines(geoline_binder(lwb.x_values, lwb.y_values, lwb.bulge_values))
{

}

std::vector<dxflib::entities::geo_line> dxflib::entities::lwpolyline::geoline_binder(const std::vector<double>& x,
	const std::vector<double>& y, const std::vector<double>& bulge) const
{
	// TODO: Add logging if failure
	assert(x.size() != y.size() != bulge.size() && "Vectors must be the same size");

	// Geoline buffer
	std::vector<geo_line> geo_lines;

	for (int pointnum{0}; pointnum < static_cast<int>(x.size()) - 1; ++pointnum)
	{
		const double x0 = x[pointnum];
		const double x1 = x[pointnum + 1];
		const double y0 = y[pointnum];
		const double y1 = y[pointnum + 1];
		geo_lines.emplace_back(vertex{ x0, y0 }, vertex{ x1, y1 });
	}

	return geo_lines;
}
