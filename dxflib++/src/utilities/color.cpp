#include "dxflib++/include/utilities.h"
#include <sstream>
dxflib::utilities::color::color(const int raw_color) : red(0), green(0),
	blue(0), raw_color_(raw_color)
{
	std::stringstream ss;
	ss << std::hex << raw_color;
	std::string string = ss.str();

	std::stringstream s_red{string.substr(0, 2)};
	s_red >> std::hex >> red;
	if (string.length() > 2)
	{
		std::stringstream s_green{ string.substr(2, 2) };
		s_green >> std::hex >> green;
	}
	if (string.length() > 4)
	{
		std::stringstream s_blue{ string.substr(4, 2) };
		s_blue >> std::hex >> blue;
	}
	hex = "0x" + string;
}

dxflib::utilities::color::color(const char* hex_string) :
	red(0), green(0), blue(0), raw_color_(0)
{
	std::string string = hex_string;
	std::stringstream s_red{string.substr(0, 2)};
	s_red >> std::hex >> red;
	if (string.length() > 2)
	{
		std::stringstream s_green{string.substr(2, 2)};
		s_green >> std::hex >> green;
	}
	if (string.length() > 4)
	{
		std::stringstream s_blue{string.substr(4, 2)};
		s_blue >> std::hex >> blue;
	}
	hex = "0x" + string;
}
