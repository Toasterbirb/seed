#pragma once
#include "std.hpp"

namespace seed
{
	std::string ExpandHomePath(const std::string& filepath);
	std::string Basename(const std::string& filepath, const bool& no_filetype = true);

	std::string ReadFile(const std::string& filepath);
	std::vector<std::string> ReadFileLines(const std::string& filepath, const bool& ignore_comments = false);

	bool WriteFile(const std::string& text, const std::string& filepath);
	std::string TmpFile(); /* Creates an empty temporary file */
}
