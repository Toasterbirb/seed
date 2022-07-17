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

	bool string::starts_with(const seed::string& text) const
	{
		/* Check if the token string is longer */
		if (text.size() > p_data.size())
			return false;

		if (p_data.substr(0, text.size()) == text.data())
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

	bool string::ends_with(const seed::string& text) const
	{
		/* Check if the token string is longer */
		if (text.size() > p_data.size())
			return false;

		if (p_data.substr(p_data.size() - text.size(), text.size()) == text.data())
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
			if (p_data[i] < 44 || p_data[i] > 58)
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

		return CleanDecimals(p_data);
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