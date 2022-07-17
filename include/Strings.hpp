#pragma once
#include "std.hpp"

namespace seed
{
	std::string CleanDecimals(const std::string& value); 	// Remove decimal points from the end of a string

	std::string CleanDecimals(const double& value); // Convert floating point numbers to strings and remove
													// unnecessary decimal values

	std::string TrimChar(const std::string& text, const char& c); 	// Remove every occurrence of a given char from the beginning and end
																	// of a string
}
