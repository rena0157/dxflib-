#include "dxflib++/include/entities/lwpolyline.h"
#include "dxflib++/include/mathlib.h"
#include "dxflib++/include/utilities.h"

dxflib::entities::geo_line::geo_line(const vertex& v0, const vertex& v1, const double bulge):
	v0(v0), v1(v1), bulge(bulge),
	length(bulge == 0 ? mathlib::distance(v0, v1) : mathlib::distance(v0, v1, bulge))
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
		if (utilities::is_number(cl))
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

		// TODO: Add bulge value
		// TODO: Add vertex_id
	default:
		return 0;
	}
}

dxflib::entities::lwpolyline::lwpolyline(lwpolyline_buffer& lwb) : entity(lwb)
{
	// TODO: Add points binder
	// TODO: Add geoline constructor
}
