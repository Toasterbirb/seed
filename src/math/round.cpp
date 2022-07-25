#include "Math.hpp"
#include "doctest/doctest.h"

namespace seed
{
	double Round(const double& value, const int& accuracy)
	{
		/* How this thing works:
		 * 1. Multiply the value with 10 ^ decimal points. This will leave the needed values before the decimal point
		 * 2. Round to integer
		 * 3. Divide the value with 10 ^ decimal points to get the desired rounded decimal value
		 * */
		return std::round(value * std::pow(10, accuracy)) / std::pow(10, accuracy);
	}

	TEST_CASE("Rounding with specified accuracy")
	{
		double value1 = 0.013333333;
		float value2 = 0.017777777;

		CHECK(Round(value1, 6) == 0.013333);
		CHECK(Round(value1, 3) == 0.013);
		CHECK(Round(value1, 2) == 0.01);

		CHECK(Round(value2, 6) == 0.017778);
		CHECK(Round(value2, 3) == 0.018);
		CHECK(Round(value2, 2) == 0.02);
	}
}
