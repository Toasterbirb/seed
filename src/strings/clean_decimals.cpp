#include "Strings.hpp"
#include "doctest/doctest.h"

namespace seed
{
	std::string CleanDecimals(const double& value)
	{
		std::string result = std::to_string(value);
		int size = (int)result.size();
		for (int i = size - 1; i > 0; i--)
		{
			if (result[i] != '0' && i < size - 1)
			{
				result.erase(i + 1, size);
				break;
			}
		}

		/* Check if the last char is a dot */
		if (result[result.size() - 1] == '.')
			result.erase(result.size() - 1, 1);

		return result;
	}

	TEST_CASE("Clean unnecessary decimals from floating point values")
	{
		double values[7] = {
			1.987200,
			2.0000,
			4.3429000,
			4.00,
			5.020,
			-1.0001,
			-1.555
		};

		CHECK(CleanDecimals(values[0]) == "1.9872");
		CHECK(CleanDecimals(values[1]) == "2");
		CHECK(CleanDecimals(values[2]) == "4.3429");
		CHECK(CleanDecimals(values[3]) == "4");
		CHECK(CleanDecimals(values[4]) == "5.02");
		CHECK(CleanDecimals(values[5]) == "-1.0001");
		CHECK(CleanDecimals(values[6]) == "-1.555");
	}
}
