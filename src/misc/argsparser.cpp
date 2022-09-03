#include "doctest/doctest.h"
#include "ArgsParser.hpp"
#include "String.hpp"

namespace seed
{
	ArgsParser::ArgsParser(const int& argc, char** argv)
	:argc(argc), argv(argv)
	{
		valid_args = parse();
	}

	char** ArgsParser::c_args() const
	{
		return argv;
	}

	int ArgsParser::arg_count() const
	{
		return argc;
	}

	TEST_CASE("Initialize an ArgsParser")
	{
		char* arguments[2] = { (char*)"/some/path", (char*)"--help" };
		int arg_count = 2;
		ArgsParser parser(arg_count, arguments);

		CHECK(parser.arg_count() == 2);
		CHECK(parser.c_args()[0] == "/some/path");
		CHECK(parser.c_args()[1] == "--help");
	}

	bool is_key(char* str)
	{
		if (!strcmp(str, "--"))
			return false;

		if (str[0] == '-')
			return true;

		return false;
	}

	TEST_CASE("Check if arg key")
	{
		CHECK(is_key((char*)"-k"));
		CHECK(is_key((char*)"-key"));
		CHECK(is_key((char*)"--key"));
		CHECK_FALSE(is_key((char*)"key"));
		CHECK_FALSE(is_key((char*)"--"));
	}

	bool is_short_key(char* str)
	{
		if (strlen(str) == 2 && is_key(str))
			return true;

		return false;
	}

	TEST_CASE("Check if short arg key")
	{
		CHECK(is_short_key((char*)"-c"));
		CHECK(is_short_key((char*)"-P"));
		CHECK_FALSE(is_short_key((char*)"--"));
		CHECK_FALSE(is_short_key((char*)"--actually-long-key"));
	}

	bool is_long_key(char* str)
	{
		if (strlen(str) > 2 && is_key(str) && str[1] == '-')
			return true;

		return false;
	}

	TEST_CASE("Check if long arg key")
	{
		CHECK(is_long_key((char*)"--test"));
		CHECK_FALSE(is_long_key((char*)"-not-long-key"));
		CHECK_FALSE(is_long_key((char*)"-a"));
		CHECK_FALSE(is_long_key((char*)"asdf"));
		CHECK_FALSE(is_long_key((char*)"--"));
	}

	bool ArgsParser::parse()
	{
		/* Invalid argc value */
		if (argc < 1)
			return false;

		/* No args to parse */
		if (argc == 1)
			return true;

		for (int i = 1; i < argc; i++)
		{
			/* One letter keys */
			if (is_short_key(argv[i]) || is_long_key(argv[i]))
			{
				/* Check if the key has a value */
				seed::string trimmed_key = argv[i];
				trimmed_key = trimmed_key.trim('-');

				if (i < argc - 1 && !is_key(argv[i + 1]))
				{
					key_values[trimmed_key.data()] = argv[i + 1];
					i++;
				}
				else
				{
					/* No value found, so setting the keyvalue to "true" */
					key_values[trimmed_key.data()] = "true";
				}
			}
			else
			{
				/* Most likely an invalid key */
				return false;
			}
		}

		return true;
	}


	TEST_CASE("Arg parsing")
	{
		SUBCASE("Valid arguments")
		{
			const int arg_count = 7;
			char* valid_args[arg_count] = {
				(char*)"/some/path",
				(char*)"-t", (char*)"some title",
				(char*)"--enabled",
				(char*)"--test",
				(char*)"--foo", (char*)"bar"
			};
			ArgsParser arg_parser(arg_count, valid_args);

			/* Check that the values match */
			CHECK(arg_parser.key()["t"] == "some title");
			CHECK(arg_parser.key()["enabled"] == "true");
			CHECK(arg_parser.key()["test"] == "true");
			CHECK(arg_parser.key()["foo"] == "bar");

			CHECK(arg_parser.has_key("test"));
			CHECK_FALSE(arg_parser.has_key("testasdf"));

			CHECK(arg_parser.is_valid());
		}

		SUBCASE("A single argument")
		{
			const int arg_count = 2;
			char* arguments[arg_count] = {
				(char*)"/some/path",
				(char*)"--test"
			};
			ArgsParser arg_parser(arg_count, arguments);
			CHECK(arg_parser.has_key("test"));
			CHECK(arg_parser.key()["test"] == "true");
		}

		SUBCASE("Invalid arguments")
		{
			const int arg_count = 3;
			char* invalid_args[arg_count] = {
				(char*)"/some/path",
				(char*)"placeholder",
				(char*)"--test"
			};

			SUBCASE("Double dash")
			{
				invalid_args[1] = (char*)"--";
			}

			SUBCASE("Missing key")
			{
				invalid_args[1] = (char*)"no_key";
			}

			ArgsParser arg_parser(arg_count, invalid_args);

			CHECK_FALSE(arg_parser.parse());
			CHECK_FALSE(arg_parser.is_valid());
		}

		SUBCASE("Invalid arg count")
		{
			const int arg_count = -5;
			char* arguments[2] = {
				(char*)"/some/path",
				(char*)"--foo"
			};
			ArgsParser arg_parser(arg_count, arguments);

			CHECK_FALSE(arg_parser.parse());
			CHECK_FALSE(arg_parser.is_valid());
		}
	}

	std::map<std::string, std::string> ArgsParser::key() const
	{
		return key_values;
	}

	bool ArgsParser::has_key(const std::string& key)
	{
		if (key_values[key] != "")
			return true;

		return false;
	}

	bool ArgsParser::is_valid() const
	{
		return valid_args;
	}
}
