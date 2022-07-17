#pragma once
#include "std.hpp"

namespace seed
{
	std::string CleanDecimals(const std::string& value); 	// Remove decimal points from the end of a string

	std::string CleanDecimals(const double& value); // Convert floating point numbers to strings and remove
													// unnecessary decimal values

	std::string TrimChar(const std::string& text, const char& c); 	// Remove every occurrence of a given char from the beginning and end
																	// of a string

	bool is_letter(char c); /* Check if the char belongs to alphabet a-z */
	bool is_upper_case(char c); /* Check if a char is uppercase */
	bool is_lower_case(char c); /* Check if a char is lowercase */
}
