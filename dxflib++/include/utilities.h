#pragma once
#include <string>
#include <algorithm>

namespace dxflib
{
	namespace utilities
	{
		inline bool is_number(const std::string& str)
		{
			return !str.empty() && std::find_if(str.begin(),
				str.end(), [](char c){return !isdigit(c); }) == str.end();
		}
	}
}
