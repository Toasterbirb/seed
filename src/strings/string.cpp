#include "doctest/doctest.h"
#include "String.hpp"
#include "Strings.hpp"

namespace seed
{
	string::string()
	{
		p_data = "";
	}

	TEST_CASE("Empty string")
	{
		string seed_string;
		CHECK(seed_string == "");
	}

	string::string(const char* text)
	:p_data(text)
	{}

	TEST_CASE("Initialize a string with const char*")
	{
		string seed_string = "Hello world!";
		CHECK(seed_string == "Hello world!");

		seed_string = "Hello from another world";
		CHECK(seed_string == "Hello from another world");
	}

	string::string(char text[])
	:p_data(text)
	{}

	TEST_CASE("Initialize string with char array")
	{
		char test[] = "test";
		char testB[] = "test";

		string seed_string = test;
		CHECK(seed_string == test);

		seed_string = testB;
		CHECK(seed_string == testB);
	}

	string::string(const std::string& text)
	:p_data(text)
	{}

	TEST_CASE("Initialize string with std::string")
	{
		std::string test = "test";
		std::string testB = "testB";

		string seed_string = test;
		CHECK(seed_string == test);

		seed_string = testB;
		CHECK(seed_string == testB);
	}

	string::string(const seed::string& text)
	:p_data(text.data())
	{}

	TEST_CASE("Initialize a string with another string")
	{
		string lineA = "test";
		string lineB = "not a test";

		lineA = lineB;
		CHECK(lineA == lineB);
	}

	string::string(const int& value)
	{
		p_data = std::to_string(value);
	}

	string::string(const float& value)
	{
		p_data = std::to_string(value);
	}

	string::string(const double& value)
	{
		p_data = std::to_string(value);
	}

	string::string(const long& value)
	{
		p_data = std::to_string(value);
	}

	TEST_CASE("Initialize strings with numbers")
	{
		int int_val 		= 45;
		float float_val 	= 45.00f;
		double double_val 	= 45.00;
		long long_val 		= 45;

		/* Integer */
		string seed_string = int_val;
		CHECK(seed_string == "45");

		/* Float */
		seed_string = float_val;
		CHECK(seed_string == "45.000000");

		/* Double */
		seed_string = double_val;
		CHECK(seed_string == "45.000000");

		/* Long */
		seed_string = long_val;
		CHECK(seed_string == "45");
	}

	std::string string::data() const
	{
		return this->p_data.data();
	}

	TEST_CASE("Get the value of a string")
	{
		string seed_string = "hello world";
		std::string std_string = "hello world";
		CHECK(seed_string.data() == std_string);
	}

	int string::size() const
	{
		return p_data.size();
	}

	TEST_CASE("Get the size of the seed::string")
	{
		string seed_string = "test";
		CHECK(seed_string.size() == 4);
	}

	bool string::starts_with(seed::string text) const
	{
		/* Check if the token string is longer */
		if (text.size() > data().size())
			return false;

		if (data().substr(0, text.size()) == text.data())
			return true;

		return false;
	}

	TEST_CASE("Check if a string starts with something")
	{
		string hello_world = "Hello world!";

		CHECK(hello_world.starts_with("Hello"));
		CHECK(hello_world.starts_with(hello_world));

		CHECK_FALSE(hello_world.starts_with("world"));
		CHECK_FALSE(hello_world.starts_with("hello another world"));
	}

	bool string::ends_with(seed::string text) const
	{
		/* Check if the token string is longer */
		if (text.size() > data().size())
			return false;

		if (data().substr(size() - text.size(), text.size()) == text.data())
			return true;

		return false;
	}

	TEST_CASE("Check if a string ends with something")
	{
		string hello_world = "Hello world!";

		CHECK(hello_world.ends_with("world!"));
		CHECK(hello_world.ends_with(hello_world));

		CHECK_FALSE(hello_world.ends_with("worl"));
		CHECK_FALSE(hello_world.ends_with("hello another world"));
	}

	bool string::is_digit() const
	{
		/* An empty string can't really be a number */
		if (size() == 0)
			return false;

		for (int i = 0; i < size(); i++)
			if (data()[i] < 44 || data()[i] > 58)
				return false;

		return true;
	}

	TEST_CASE("Check if the string is a digit")
	{
		string text = "asdf";
		CHECK_FALSE(text.is_digit());

		text = "1234asdf";
		CHECK_FALSE(text.is_digit());

		text = "ö'asöfvy6835";
		CHECK_FALSE(text.is_digit());

		text = "";
		CHECK_FALSE(text.is_digit());

		text = " ";
		CHECK_FALSE(text.is_digit());

		/* Go trough a few negative and positive numbers */
		for (int i = -10; i < 10; i++)
		{
			text = i;
			CHECK(text.is_digit());
		}

		for (float i = -10.05f; i < 10.0f; i += 2.4f)
		{
			text = i;
			CHECK(text.is_digit());
		}
	}

	string string::clean_decimals() const
	{
		/* Check if the string even has any chars in it.
		 * If so, cancel */
		if (!is_digit())
			return *this;

		return CleanDecimals(data());
	}

	TEST_CASE("Clean unnecessary decimals from floating point values")
	{
		string decimal_value = 49.025f;
		CHECK(decimal_value.clean_decimals() == "49.025");

		decimal_value = 12.00000f;
		CHECK(decimal_value.clean_decimals() == "12");

		decimal_value = -12.00000f;
		CHECK(decimal_value.clean_decimals() == "-12");

		decimal_value = "testing...";
		CHECK(decimal_value.clean_decimals() == "testing...");

		decimal_value = "-testing...";
		CHECK(decimal_value.clean_decimals() == "-testing...");

		decimal_value = 0.000;
		CHECK(decimal_value.clean_decimals() == "0");

		decimal_value = "0,9300";
		CHECK(decimal_value.clean_decimals() == "0,93");

		decimal_value = "-0,9300";
		CHECK(decimal_value.clean_decimals() == "-0,93");
	}

	string string::trim(char c) const
	{
		return TrimChar(data(), c);
	}

	TEST_CASE("Trim chars around the string")
	{
		string string_with_whitespaces;

		SUBCASE("Trim the beginning")
		{
			string_with_whitespaces = "    asdf";
		}

		SUBCASE("Trim the end")
		{
			string_with_whitespaces = "asdf     ";
		}

		SUBCASE("Trim both begnning and the end")
		{
			string_with_whitespaces = "     asdf    ";
		}

		CHECK(string_with_whitespaces.trim(' ') == "asdf");
	}

	int string::find(seed::string text) const
	{
		/* Check if the text we are looking for even fits into the parent string */
		if (size() < text.size())
			return -1;

		/* Find the first character */
		for (int i = 0; i < size(); i++)
		{
			if (data()[i] == text.data()[0])
			{
				/* First char was found, check if the characters next to it are
				 * the rest of the text we are looking for */
				bool mismatch = false;

				for (int j = 0; j < text.size(); j++)
				{
					if (data()[i + j] != text.data()[j])
					{
						mismatch = true;
						break;
					}
				}

				if (!mismatch)
					return i;
			}
		}

		return -1;
	}

	TEST_CASE("Find the first occurrence of a string inside of another string")
	{
		string text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit";
		CHECK(text.find("ipsum") == 6);
		CHECK(text.find("amet") == 22);
		CHECK(text.find("lmao") == -1);

		string short_text = "test";
		CHECK(text.find("longer text") == -1);
	}

	string string::replace(seed::string old_str, seed::string new_str) const
	{
		/* Find the old_str */
		int start_index = this->find(old_str);

		/* If the old_str wasn't found, don't do anything */
		if (start_index == -1)
			return *this;

		/* Replace old_str in result with new_str */
		return data().replace(start_index, old_str.size(), new_str.data());
	}

	TEST_CASE("Replace parts of the string")
	{
		string hello = "hello world";

		CHECK(hello.replace("world", "planet") == "hello planet");
		CHECK(hello.replace("hi", "bye") == "hello world");
		CHECK(hello.replace("asaalskjdhflaskjdhflaksjdhf", "asdf") == "hello world");
		CHECK(hello.replace("", "p") == "hello world");
		CHECK(hello.replace(" ", "_") == "hello_world");
	}

	/* Operator overload tests */
	TEST_CASE("Add multiple strings together")
	{
		string hello = "hello ";
		string world = "world";
		string test = hello + world;

		CHECK(test == "hello world");

		string hello_cat = hello + "cat";
		CHECK(hello_cat == "hello cat");

		string hello_cats_and_dogs = hello + "cats " + "and " + "dogs";
		CHECK(hello_cats_and_dogs == "hello cats and dogs");

		std::string exclamation_mark = "!";
		string loud_hello_world = test + exclamation_mark;
		CHECK(loud_hello_world == "hello world!");
	}

	TEST_CASE("String multiplication")
	{
		string line = "-";
		string multiple_lines = line * 5;
		CHECK(multiple_lines == "-----");

		line *= 3;
		CHECK(line == "---");
	}
}
