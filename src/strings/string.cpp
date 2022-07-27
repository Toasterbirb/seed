#include "doctest/doctest.h"
#include "String.hpp"
#include "Strings.hpp"

#define UPPERCASE_ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define LOWERCASE_ALPHABET "abcdefghijklmnopqrstuvwxyz"

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
		return this->p_data;
	}

	TEST_CASE("Get the value of a string")
	{
		string seed_string = "hello world";
		std::string std_string = "hello world";
		CHECK(seed_string.data() == std_string);
	}

	std::string& string::mutable_data()
	{
		return this->p_data;
	}

	TEST_CASE("Edit the std::string directly")
	{
		string text = "testing...";
		text.mutable_data()[1] = 'a';
		CHECK(text == "tasting...");
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
		if (empty())
			return false;

		for (int i = 0; i < size(); i++)
			if ((data()[i] < 48 || data()[i] > 58) && data()[i] != '-')
				return false;

		return true;
	}

	TEST_CASE("Check if a string is a digit (not floating point number)")
	{
		string text = "asdf";
		CHECK_FALSE(text.is_digit());

		text = "";
		CHECK_FALSE(text.is_number());

		text = " ";
		CHECK_FALSE(text.is_number());

		text = "0.005";
		CHECK_FALSE(text.is_digit());

		text = "0,005";
		CHECK_FALSE(text.is_digit());

		text = "1.2";
		CHECK_FALSE(text.is_digit());

		text = "0005";
		CHECK(text.is_digit());

		for (int i = -10; i < 10; i++)
		{
			text = i;
			CHECK(text.is_digit());
		}
	}

	bool string::is_number() const
	{
		/* An empty string can't really be a number */
		if (empty())
			return false;

		for (int i = 0; i < size(); i++)
			if (data()[i] < 44 || data()[i] > 58)
				return false;

		return true;
	}

	TEST_CASE("Check if the string is a number")
	{
		string text = "asdf";
		CHECK_FALSE(text.is_number());

		text = "1234asdf";
		CHECK_FALSE(text.is_number());

		text = "ö'asöfvy6835";
		CHECK_FALSE(text.is_number());

		text = "";
		CHECK_FALSE(text.is_number());

		text = " ";
		CHECK_FALSE(text.is_number());

		/* Go trough a few negative and positive numbers */
		for (int i = -10; i < 10; i++)
		{
			text = i;
			CHECK(text.is_number());
		}

		for (float i = -10.05f; i < 10.0f; i += 2.4f)
		{
			text = i;
			CHECK(text.is_number());
		}
	}

	bool string::is_upper() const
	{
		for (int i = 0; i < size(); i++)
			if (is_lower_case(data()[i]))
				return false;

		return true;
	}

	TEST_CASE("Check if the entire string is in uppercase")
	{
		string up_alphabet = UPPERCASE_ALPHABET;
		CHECK(up_alphabet.is_upper());

		string low_alphabet = LOWERCASE_ALPHABET;
		CHECK_FALSE(low_alphabet.is_upper());

		string mixed = (seed::string)UPPERCASE_ALPHABET + (seed::string)LOWERCASE_ALPHABET;
		CHECK_FALSE(mixed.is_upper());
	}

	bool string::is_lower() const
	{
		for (int i = 0; i < size(); i++)
			if (is_upper_case(data()[i]))
				return false;

		return true;
	}

	TEST_CASE("Check if the entire string is in lowercase")
	{
		string up_alphabet = UPPERCASE_ALPHABET;
		CHECK_FALSE(up_alphabet.is_lower());

		string low_alphabet = LOWERCASE_ALPHABET;
		CHECK(low_alphabet.is_lower());

		string mixed = (seed::string)UPPERCASE_ALPHABET + (seed::string)LOWERCASE_ALPHABET;
		CHECK_FALSE(mixed.is_lower());
	}

	bool string::is_letters(bool accept_whitespace) const
	{
		for (int i = 0; i < size(); i++)
			if (!is_letter(data()[i]))
			{
				if (!accept_whitespace)
					return false;
				else if (data()[i] == ' ')
					continue;
			}

		return true;
	}

	TEST_CASE("Check if the entire string consists of only letters")
	{
		string up_alphabet = UPPERCASE_ALPHABET;
		CHECK(up_alphabet.is_letters());

		string low_alphabet = LOWERCASE_ALPHABET;
		CHECK(low_alphabet.is_letters());

		string numbers = "0123456789";
		CHECK_FALSE(numbers.is_letters());

		string mixed = "ABSDF4234kljdfgf";
		CHECK_FALSE(mixed.is_letters());

		string special_chars = "!\"#¤%&/()=@£$‰‚{[]";
		CHECK_FALSE(special_chars.is_letters());

		string text_with_whitespaces = "Hello world";
		CHECK_FALSE(text_with_whitespaces.is_letters());
		CHECK(text_with_whitespaces.is_letters(true));
	}

	bool string::empty() const
	{
		return data().empty();
	}

	TEST_CASE("Check if a string is empty or not")
	{
		string text = "";
		CHECK(text.empty());

		text = "asd";
		CHECK_FALSE(text.empty());
	}



	int string::find(seed::string text) const
	{
		/* Check if the strings are the same */
		if (*this == text)
			return 0;

		int text_size = text.size();

		/* Check if the text we are looking for even fits into the parent string */
		if (size() < text_size)
			return -1;

		/* Check if the target text has any chars in it */
		if (text_size == 0)
			return -1;

		/* Find the first character */
		for (int i = 0; i < size(); i++)
		{
			if (data()[i] == text.data()[0])
			{
				/* First char was found, check if the characters next to it are
				 * the rest of the text we are looking for */
				bool mismatch = false;

				for (int j = 1; j < text_size; j++)
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
		CHECK(text.find("") == -1);
		CHECK(text.find(text) == 0);

		string short_text = "test";
		CHECK(text.find("longer text") == -1);
	}

	int string::find_char(char c) const
	{
		for (int i = 0; i < size(); i++)
			if (data()[i] == c)
				return i;

		return -1;
	}

	TEST_CASE("Find the first occurrence of a char")
	{
		string text = "lol";
		CHECK(text.find_char('o') == 1);
		CHECK(text.find_char('l') == 0);
		CHECK(text.find_char('a') == -1);

		string empty_string = "";
		CHECK(empty_string.find_char('a') == -1);

		string hyperlink = "<a href=\"https://example.com\">Link</a>";
		CHECK(hyperlink.find_char('>') == 29);
	}

	int string::find_last(seed::string text) const
	{
		/* Check if the strings are the same */
		if (*this == text)
			return 0;

		/* Check if the text we are looking for even fits into the parent string */
		if (size() < text.size())
			return -1;

		/* Check if the target text has any chars in it */
		if (text.size() == 0)
			return -1;

		/* Find the first last character */
		for (int i = size() -1; i > -1; i--)
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

	TEST_CASE("Find the last occurrence of a string inside of another string")
	{
		string text = "asd dsa asd dsa";
		CHECK(text.find_last("asd") == 8);
		CHECK(text.find_last("dsa") == 12);
		CHECK(text.find_last("") == -1);
		CHECK(text.find_last(text) == 0);

		string short_text = "test";
		CHECK(text.find_last("longer text") == -1);
	}

	int string::find_last_char(char c) const
	{
		/* Make sure the string isn't empty */
		if (empty())
			return -1;

		for (int i = size() - 1; i > -1; i--)
			if (data()[i] == c)
				return i;

		return -1;
	}

	string string::clean_decimals() const
	{
		/* Check if the string even has any chars in it.
		 * If so, cancel */
		if (!is_number())
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

	TEST_CASE("Find the first occurrence of a char, but in reverse")
	{
		string text = "lmao";
		CHECK(text.find_last_char('o') == 3);
		CHECK(text.find_last_char('l') == 0);
		CHECK(text.find_last_char('e') == -1);

		string empty_string = "";
		CHECK(empty_string.find_last_char('a') == -1);
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

	string string::replace_all(seed::string old_str, seed::string new_str) const
	{
		/* Don't operate on empty strings */
		if (size() == 0)
			return *this;

		string result = *this;
		string tmp_result = *this;

		while (true)
		{
			tmp_result = result.replace(old_str, new_str);
			if (tmp_result != result)
				result = tmp_result;
			else
				break;
		}

		return result;
	}

	TEST_CASE("Replace all matching parts in a string with something")
	{
		string test_str = "string string::replace_all(seed::string old_str, seed::string new_str) const";
		CHECK(test_str.replace_all("seed", "birb") == "string string::replace_all(birb::string old_str, birb::string new_str) const");
		CHECK(test_str.replace_all("non-existant stuff", "test") == test_str);

		string empty_string = "";
		CHECK(empty_string.replace_all("testing", "should be empty") == "");

		string short_string = "a";
		CHECK(short_string.replace_all("b", "c") == short_string);
		CHECK(short_string.replace_all("a", "b") == "b");

		string only_text_to_replace = "aaaa";
		CHECK(only_text_to_replace.replace_all("aa", "b") == "bb");
	}

	string string::reverse() const
	{
		/* You can't really reverse chars with length of <= 1 */
		if (size() < 2)
			return *this;

		char result[size() + 1];
		for (int i = size() - 1; i > -1; i--)
			result[(size() - 1) - i] = data()[i];

		/* Add the null termination char */
		result[size()] = 0;

		return result;
	}

	TEST_CASE("Reverse the string")
	{
		string numbers = "12345";
		CHECK(numbers.reverse() == "54321");

		string text = "asdf";
		CHECK(text.reverse() == "fdsa");

		string textB = "hello world";
		CHECK(textB.reverse() == "dlrow olleh");

		string empty_string = "";
		CHECK(empty_string.reverse() == "");

		string single_char_string = "a";
		CHECK(single_char_string.reverse() == "a");

		string short_str = "ab";
		CHECK(short_str.reverse() == "ba");

		string null_str;
		CHECK(null_str.reverse() == "");
	}

	string string::substr(int start_pos, int end_pos) const
	{
		int start 	= start_pos;
		int end 	= end_pos;

		if (start < 0)
			start = 0;

		if (end > size() - 1)
			end = size() - 1;

		if (end < start)
			return *this;

		if (start == 0 && end == size() -1)
			return *this;

		if (start == end)
			return data().substr(start, 1);

		return data().substr(start, end - start + 1);
	}

	TEST_CASE("Get a range of chars inside of the string")
	{
		string hello_world = "Hello world!";
		CHECK(hello_world.substr(0, hello_world.size() - 1) == hello_world);
		CHECK(hello_world.substr(1, hello_world.size() - 2) == "ello world");
		CHECK(hello_world.substr(3, 6) == "lo w");
		CHECK(hello_world.substr(4, 0) == hello_world);
		CHECK(hello_world.substr(0, hello_world.size() + 5) == hello_world);
		CHECK(hello_world.substr(3, hello_world.size() + 5) == "lo world!");
		CHECK(hello_world.substr(-1, 4) == "Hello");
		CHECK(hello_world.substr(-5, hello_world.size() + 5) == hello_world);
		CHECK(hello_world.substr(1, 1) == "e");
		CHECK(hello_world.substr(1, 2) == "el");
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

	string string::trim_between(char a, char b) const
	{
		/* Finds the first instance of a and b, and removes everything between them */
		int a_pos = find_char(a);
		int b_pos = find_char(b);

		if (a_pos == -1 || b_pos == -1)
			return *this;

		/* Don't do anything if b is after a */
		if (b < a)
			return *this;

		return data().erase(a_pos, b_pos - a_pos + 1);
	}

	TEST_CASE("Remove text between two given chars")
	{
		string link = "Here's some link: <a href=https://example.com>This is the link</a>";
		link = link.trim_between('<', '>');
		CHECK(link == "Here's some link: This is the link</a>");

		link = link.trim_between('<', '>');
		CHECK(link == "Here's some link: This is the link");
	}

	string string::trim_until(char c, trim_mode mode) const
	{
		seed::string result = data();
		int start_index = 0;
		int end_index = 0;

		/* Trim from the beginning */
		if (mode != string::trim_mode::end)
		{
			start_index = result.find_char(c);
			result = result.data().substr(start_index + 1, result.size() - start_index - 1);
		}

		/* Trim from the end */
		if (mode != string::trim_mode::start)
		{
			end_index = result.find_last_char(c);
			result = result.data().substr(0, end_index);
		}

		return result;
	}

	TEST_CASE("Trim the text until some specific char is encountered")
	{
		string text = "<div>text</div>";

		SUBCASE("Trim from the beginning")
		{
			CHECK(text.trim_until('>') == "text</div>");
			CHECK(text.trim_until('>', string::trim_mode::start) == "text</div>");
		}

		SUBCASE("Trim from the end")
		{
			CHECK(text.trim_until('<', string::trim_mode::end) == "<div>text");
		}

		SUBCASE("Trim from both sides")
		{
			CHECK(text.trim_until('t', string::trim_mode::both) == "ex");
		}
	}

	string string::to_upper() const
	{
		seed::string result = data();

		for (int i = 0; i < size(); i++)
		{
			if (is_lower_case(result.data()[i]))
				result.mutable_data()[i] -= 32;
		}

		return result;
	}

	TEST_CASE("Change all letters in the string to uppercase")
	{
		string alphabet = LOWERCASE_ALPHABET;
		CHECK(alphabet.to_upper() == UPPERCASE_ALPHABET);

		string text_with_special_chars = "hello -world_123!!?";
		CHECK(text_with_special_chars.to_upper() == "HELLO -WORLD_123!!?");

		string random_case = "HeLloWorld";
		CHECK(random_case.to_upper() == "HELLOWORLD");

		string empty_string = "";
		CHECK(empty_string.to_upper() == "");

		string short_string = "a";
		CHECK(short_string.to_upper() == "A");
	}

	string string::to_lower() const
	{
		seed::string result = data();

		for (int i = 0; i < size(); i++)
		{
			if (is_upper_case(result.data()[i]))
				result.mutable_data()[i] += 32;
		}

		return result;
	}

	TEST_CASE("Change all letters in the string to lowercase")
	{
		string alphabet = UPPERCASE_ALPHABET;
		CHECK(alphabet.to_lower() == LOWERCASE_ALPHABET);

		string text_with_special_chars = "HELLO -WORLD_123!!?";
		CHECK(text_with_special_chars.to_lower() == "hello -world_123!!?");

		string random_case = "HeLloWorld";
		CHECK(random_case.to_lower() == "helloworld");

		string empty_string = "";
		CHECK(empty_string.to_lower() == "");

		string short_string = "A";
		CHECK(short_string.to_lower() == "a");
	}

	void string::clear()
	{
		p_data.clear();
	}

	TEST_CASE("Clear the string")
	{
		string text = "asdf";
		CHECK(text == "asdf");

		text.clear();
		CHECK(text == "");
		CHECK(text.empty());
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

	TEST_CASE("Non-Equality check")
	{
		string a = "hello";
		string b = "world";
		CHECK(a != b);
	}
}
