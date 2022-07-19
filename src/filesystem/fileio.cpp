#include "Files.hpp"
#include "std.hpp"
#include "doctest/doctest.h"
#include "Crypto.hpp"

namespace seed
{
	std::string ReadFile(const std::string& filepath)
	{
		/* Shamelessly stolen from https://stackoverflow.com/a/2912614 */
		std::ifstream ifs(filepath);
		std::string content( 	(std::istreambuf_iterator<char>(ifs) ),
							   	(std::istreambuf_iterator<char>()    ) );

		return content;
	}

	std::vector<std::string> ReadFileLines(const std::string& filepath, const bool& ignore_comments)
	{
		std::vector<std::string> lines;

		std::ifstream file(filepath);
		std::string tmp_line;

		if (ignore_comments)
		{
			while (std::getline(file, tmp_line))
			{
				if (tmp_line[0] == '#')
					continue;

				lines.push_back(tmp_line);
			}
		}
		else
		{
			while (std::getline(file, tmp_line))
			{
				lines.push_back(tmp_line);
			}
		}

		return lines;
	}

	bool WriteFile(const std::string& text, const std::string& filepath)
	{
		std::ofstream file(filepath);
		if (!file.is_open())
			return false;

		file << text;
		file.close();
		return true;
	}

	TEST_CASE("Write to a file and read the contents")
	{
		std::string temporary_file = TmpFile();
		const std::string text = "line one\nline two\nthird line\n# comment line\nlast line\n";

		/* Write to a file */
		CHECK(WriteFile(text, temporary_file));
		CHECK(std::filesystem::exists(temporary_file));
		CHECK(std::filesystem::is_regular_file(temporary_file));

		/* Read the whole file at once */
		CHECK(ReadFile(temporary_file) == text);

		/* Read the file line by line */
		std::vector<std::string> lines = ReadFileLines(temporary_file);
		CHECK(lines.size() == 5);
		CHECK(lines[0] == "line one");
		CHECK(lines[1] == "line two");
		CHECK(lines[2] == "third line");
		CHECK(lines[3] == "# comment line");
		CHECK(lines[4] == "last line");

		/* Read the file line by line again, but this time ignore comment lines */
		lines = ReadFileLines(temporary_file, true);
		CHECK(lines.size() == 4);
		CHECK(lines[0] == "line one");
		CHECK(lines[1] == "line two");
		CHECK(lines[2] == "third line");
		CHECK(lines[3] == "last line");

		if (std::filesystem::exists(temporary_file))
			std::filesystem::remove(temporary_file);
	}

	std::string TmpFile()
	{
		std::string filename = "";
		do
		{
			filename = "/tmp/seed_" + random_md5();
		}
		while (std::filesystem::exists(filename));
		return filename;
	}

	TEST_CASE("Generate filenames that shouldn't exists already")
	{
		for (int i = 0; i < 5; i++)
		{
			std::string filepath = seed::TmpFile();
			CHECK_FALSE(std::filesystem::exists(filepath));
		}
	}
}
