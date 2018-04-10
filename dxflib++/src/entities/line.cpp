#include "dxflib++/include/entities/line.h"
#include "dxflib++/include/utilities.h"

// linebuf parse
/**
 * \brief Parse Function for the line buffer
 * \param cl Current line
 * \param nl Next line
 * \return status -> 1: sucess, 0: no success
 */
int dxflib::entities::line_buf::parse(const std::string& cl, const std::string& nl)
{
	using namespace group_codes;
	// Call the entity buffer parse function first
	if (entity_buffer_base::parse(cl, nl))
		return 1;

	// Group code
	int code{};

	// Try to convert the current line to a group code
	try
	{
		if (utilities::is_number(cl))
			code = std::stoi(cl);
	}
	catch (std::invalid_argument&)
	{
		// If error then set to -1
		code = -1;
	}
	catch (std::out_of_range&)
	{
		// If error then set to -1
		code = -1;
	}

	// Switch on the code and set the aproprate value in the line buffer
	switch (static_cast<line_codes>(code))
	{
	case line_codes::error:
		return 0;
	case line_codes::subclassmarker:
		break;
	case line_codes::thickness:
		break;
	case line_codes::x0:
		x0 = std::stod(nl);
		return 1;
	case line_codes::x1:
		x1 = std::stod(nl);
		return 1;
	case line_codes::y0:
		y0 = std::stod(nl);
		return 1;
	case line_codes::y1:
		y1 = std::stod(nl);
		return 1;
	case line_codes::z0:
		z0 = std::stod(nl);
		return 1;
	case line_codes::z1:
		z1 = std::stod(nl);
		return 1;
	default:
		return 0;
	}
	return 0;
}

/**
 * \brief Line buffer constructor for the line entity
 * \param lb Line Buffer
 */
dxflib::entities::line::line(line_buf& lb) : entity(lb), v0(lb.x0, lb.y0, lb.z0),
    v1(lb.x1, lb.y1, lb.z1)
{
	
}

