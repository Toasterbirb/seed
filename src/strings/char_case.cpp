#include "doctest/doctest.h"
#include "Strings.hpp"

namespace seed
{
	bool is_letter(char c)
	{
		return (is_upper_case(c) || is_lower_case(c));
	}

	TEST_CASE("Test if char belongs to the alphabet a-z")
	{
		char low_alphabet[] = "abcdefghijklmnopqrstuvwxyz";
		for (int i = 0; i < strlen(low_alphabet); i++)
			CHECK(is_letter(low_alphabet[i]));

		char up_alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		for (int i = 0; i < strlen(up_alphabet); i++)
			CHECK(is_letter(up_alphabet[i]));

		char random_special_chars_and_numbers[] = "!\"#¤%&/()=?`0123456789@£$‰‚{[]}\\";
		for (int i = 0; i < strlen(random_special_chars_and_numbers); i++)
			CHECK_FALSE(is_letter(random_special_chars_and_numbers[i]));
	}

	bool is_upper_case(char c)
	{
		return (c > 64 && c < 91);
	}

	TEST_CASE("Check if a char is uppercase")
	{
		char low_alphabet[] = "abcdefghijklmnopqrstuvwxyz";
		for (int i = 0; i < strlen(low_alphabet); i++)
			CHECK_FALSE(is_upper_case(low_alphabet[i]));

		char up_alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		for (int i = 0; i < strlen(up_alphabet); i++)
			CHECK(is_upper_case(up_alphabet[i]));
	}

	bool is_lower_case(char c)
	{
		return (c > 96 && c < 123);
	}

	TEST_CASE("Check if a char is lowercase")
	{
		char low_alphabet[] = "abcdefghijklmnopqrstuvwxyz";
		for (int i = 0; i < strlen(low_alphabet); i++)
			CHECK(is_lower_case(low_alphabet[i]));

		char up_alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		for (int i = 0; i < strlen(up_alphabet); i++)
			CHECK_FALSE(is_lower_case(up_alphabet[i]));

	}
}
