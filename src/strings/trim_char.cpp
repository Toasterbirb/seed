#include "Strings.hpp"
#include "doctest/doctest.h"

namespace seed
{
	std::string TrimChar(const std::string& text, const char& c)
	{
		int start = 0;
		int end = 0;

		/* Trim from the beginning */
		for (int i = 0; i < text.length(); i++)
		{
			if (text[i] != c)
			{
				start = i;
				break;
			}
		}

		/* Trim from the end */
		for (int i = text.length() - 1; i > -1; i--)
		{
			if (text[i] != c)
			{
				end = i;
				break;
			}
		}

		std::string result =  text.substr(start, end + 1 - start);

		/* In case the string only contained the char to be removed,
		 * return nothing */
		if (result[0] == c)
			return "";
		else
			return result;

		return result;
	}

	TEST_CASE("Trimming whitespace or any other characters from the beginning and end of a string")
	{
		char char_to_trim;
		std::string char_start;
		std::string char_end;
		std::string char_both;
		std::string no_char;
		std::string answer = "Hello world";

		SUBCASE("Whitespace")
		{
			char_to_trim = ' ';
			char_start 	= "     Hello world";
			char_end 	= "Hello world         ";
			char_both 	= "    Hello world         ";
			no_char 	= "Hello world";
		}

		SUBCASE("@-symbols")
		{
			char_to_trim = '@';
			char_start 	= "@@@@Hello world";
			char_end 	= "Hello world@@@@@@@@";
			char_both 	= "@Hello world@@@";
			no_char 	= "Hello world";
		}

		SUBCASE("Number")
		{
			char_to_trim = '5';
			char_start 	= "55555Hello world";
			char_end 	= "Hello world5555555";
			char_both 	= "55Hello world5555";
			no_char 	= "Hello world";
		}

		SUBCASE("Short string")
		{
			char_to_trim = ' ';
			char_start 	= " A";
			char_end 	= "A  ";
			char_both 	= "   A  ";
			no_char 	= "A";

			answer = "A";
		}

		SUBCASE("Only has the char that gets removed")
		{
			char_to_trim = '#';
			char_start 	= "###";
			char_end 	= "####";
			char_both 	= "######";
			no_char 	= "";

			answer = "";
		}

		CHECK(TrimChar(char_start, char_to_trim) == answer);
		CHECK(TrimChar(char_end, char_to_trim) == answer);
		CHECK(TrimChar(char_both, char_to_trim) == answer);
		CHECK(TrimChar(no_char, char_to_trim) == answer);
	}
}
