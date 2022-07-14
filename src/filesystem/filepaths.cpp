#include "Files.hpp"
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

	std::string Basename(const std::string& filepath, const bool& no_filetype)
	{
		/* Find the last '/' and '.' chars */
		int slash_index = 0;
		int dot_index = 0;
		bool ends_with_slash = false;

		for (int i = filepath.length() - 1; i > 0; i--)
		{
			if (filepath[i] == '/')
			{
				if (i == filepath.length() - 1)
				{
					/* The last character of the filepath is '/' */
					ends_with_slash = true;
					continue;
				}

				slash_index = i;
				continue;
			}

			if (!dot_index && !ends_with_slash && filepath[i] == '.')
			{
				dot_index = i;
				continue;
			}

			/* If the slash was found, assume that the dot was found aswell */
			if (slash_index)
				break;
		}

		/* Filepath ends in slash (is a directory) and no other slashes were found */
		if (ends_with_slash && !slash_index)
			return filepath.substr(0, filepath.length() - 1);

		if (no_filetype && dot_index)
			return filepath.substr(slash_index + 1, dot_index - slash_index - 1);
		else
			return filepath.substr(slash_index + 1, filepath.length() - slash_index - ends_with_slash - 1);
	}

	TEST_CASE("Get basename from a filepath")
	{
		/* Exclude the file extension */
		CHECK(Basename("./somefile.txt") == "somefile");
		CHECK(Basename("./directory/textfile.txt") == "textfile");
		CHECK(Basename("/home/user/directory/file.png") == "file");
		CHECK(Basename("./directory/textfile with spaces.txt") == "textfile with spaces");

		/* Include the file extensions */
		CHECK(Basename("./somefile.txt", false) == "somefile.txt");
		CHECK(Basename("./directory/textfile.txt", false) == "textfile.txt");
		CHECK(Basename("/home/user/directory/file.png", false) == "file.png");
		CHECK(Basename("./directory/textfile with spaces.txt", false) == "textfile with spaces.txt");

		/* Directories */
		CHECK(Basename("./directory/homework") == "homework");
		CHECK(Basename("./directory/homework", false) == "homework");
		CHECK(Basename("./homework") == "homework");
		CHECK(Basename("./homework", false) == "homework");
		CHECK(Basename("./homework/directory with some spaces") == "directory with some spaces");
		CHECK(Basename("./homework/directory with some spaces", false) == "directory with some spaces");
		CHECK(Basename("./directory/") == "directory");
		CHECK(Basename("./directory/", false) == "directory");
		CHECK(Basename("./directory./") == "directory.");
		CHECK(Basename("./directory./", false) == "directory.");
		CHECK(Basename("./directory/subdirectory/") == "subdirectory");
		CHECK(Basename("directory/") == "directory");
		CHECK(Basename("directory/subdirectory") == "subdirectory");
		CHECK(Basename("directory/subdirectory/") == "subdirectory");
	}
}
