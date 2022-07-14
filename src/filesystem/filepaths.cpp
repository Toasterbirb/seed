#include "Filepaths.hpp"
#include "doctest/doctest.h"

namespace seed
{
	std::string ExpandHomePath(const std::string& filepath)
	{
		if (filepath[0] != '~')
			return filepath;

		std::string home_dir = (std::string)getenv("HOME");

		return home_dir + filepath.substr(1, filepath.length() - 1);
	}

	TEST_CASE("Expand path with tilde to full path")
	{
		std::string user_home = (std::string)getenv("HOME");
		CHECK(ExpandHomePath("~/.local/share/some/path") == user_home + "/.local/share/some/path");
		CHECK(ExpandHomePath("./some/path") == "./some/path");
	}
}
