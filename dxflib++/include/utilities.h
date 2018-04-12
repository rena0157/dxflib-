#pragma once
#include <string>
#include <algorithm>
#include <cctype>

namespace dxflib
{
	namespace utilities
	{
		/**
		 * \brief Test if a string is a number. Note: this function does not ignore whilespace.
		 * \param str string reference
		 * \return True: String is a number, False: String is not a number
		 */
		inline bool is_number(const std::string& str)
		{
			return !str.empty() && std::find_if(str.begin(),
				str.end(), [](const char c) {return !isdigit(c); }) == str.end();
		}

		/**
		 * \brief trim the white space of a string from the left
		 * \param str string reference
		 */
		inline void ltrim(std::string& str)
		{
			str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](char c) {return !std::isspace(c); }));
		}

		/**
		 * \brief Trims string from the left
		 * \param str string to be trimed
		 * \return returns the trimmed string
		 */
		inline std::string ltrim_copy(std::string str)
		{
			str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](char c) {return !std::isspace(c); }));
			return str;
		}

		/**
		 * \brief trim the whitespace of a string from the right
		 * \param str string reference
		 */
		inline void rtrim(std::string& str)
		{
			str.erase(std::find_if(str.rbegin(), str.rend(), [](char c) {return !std::isspace(c); }).base(), 
				str.end());
		}

		/**
		 * \brief trim a string from the left and the right
		 * \param str string reference
		 */
		inline void trim(std::string& str)
		{
			rtrim(str); ltrim(str);
		}

		/**
		 * \brief trim a string from the left and the right then return the string
		 * \param str string to be trimed (Copy)
		 * \return trimed string
		 */
		inline std::string trim(std::string str)
		{
			rtrim(str); ltrim(str);
			return str;
		}
	}
}
