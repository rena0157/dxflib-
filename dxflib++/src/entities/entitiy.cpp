#include "dxflib++/include/entities/entity.h"
#include "dxflib++/include/utilities.h"

dxflib::entities::entity_buffer_base::~entity_buffer_base()
= default;

/**
 * \brief Parse function for the base class for entity buffers
 * \param cl Current line
 * \param nl Next line
 * \return status -> 1: sucess, 0: failure
 */
int dxflib::entities::entity_buffer_base::parse(const std::string& cl, const std::string& nl)
{
	using namespace group_codes;
	// Group code conversion
	int code{0};
	try
	{
		if (utilities::is_number(utilities::ltrim_copy(cl)))
			code = std::stoi(cl);
	}
	catch (std::invalid_argument&)
	{
		// if failure then set to -1
		code = -1;
	}
	catch (std::out_of_range&)
	{
		// if failure then set to -1
		code = -1;
	}

	// Switch on the code
	switch (static_cast<entity_codes>(code))
	{
	case entity_codes::error:
		return 0;
	case entity_codes::layer:
		layer = nl;
		return -1;
	case entity_codes::handle:
		handle = nl;
		return -1;
	case entity_codes::soft_pointer:
		if (nl != "1F")
			soft_pointer = nl;
		return -1;
	case entity_codes::color_name:
		color_name = nl;
		return -1;
	case entity_codes::raw_color:
		raw_color = std::stoi(nl);
		return -1;
	case entity_codes::ignore1:
		return -1;
	default:
		return code;
	}
}

/**
 * \brief Free the memory in vectors held by the base class
 */
void dxflib::entities::entity_buffer_base::free()
{
	// Free memory in vetors
	soft_pointer.clear();
	soft_pointer.shrink_to_fit();

	// Reset values to defaults
	layer = "";
	handle = "";
	color_name = "";
	raw_color = 0;
}

/**
* \brief Entity base class constructor
* \param eb entity buffer base struct
*/
dxflib::entities::entity::entity(entity_buffer_base& eb) :
	layer_(eb.layer), handle_(eb.handle), soft_pointer_(eb.soft_pointer),
	color_name_(eb.color_name), raw_color_(eb.raw_color),
	color_(eb.raw_color)
{
}

dxflib::entities::entity::entity() :
	layer_(""), handle_(""),
	soft_pointer_(""), raw_color_(0), color_(0)
{
}

dxflib::entities::entity::entity(const entity& e):
	layer_(e.layer_), handle_(e.handle_), soft_pointer_(e.soft_pointer_),
	raw_color_(e.raw_color_), color_(raw_color_)
{
}
