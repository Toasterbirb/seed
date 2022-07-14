#pragma once
#include "std.hpp"

namespace seed
{
	std::string ExpandHomePath(const std::string& filepath);
	std::string Basename(const std::string& filepath, const bool& no_filetype = true);
}
