#include "Math.hpp"
#include "doctest/doctest.h"

namespace seed
{
	double 	Normalize(const double& value, const double& min, const double& max, const double& normalized_maximum)
	{
		return ((value - min) / (max - min)) * normalized_maximum;
	}

	TEST_CASE("Normalize a value to set range")
	{
		double values[13] = {
			12, 19, 21, 23, 25, 35, 47, 48, 59, 65, 66, 67, 68
		};

		double lowestValue 	= Min(values, 13);
		double highestValue = Max(values, 13);
		double normalized_maximum = 100;

		CHECK(Normalize(values[0], lowestValue, highestValue, normalized_maximum) == 0);
		CHECK(Normalize(values[1], lowestValue, highestValue, normalized_maximum) == 12.5);
		CHECK(Round(Normalize(values[2], lowestValue, highestValue,normalized_maximum), 2) == 16.07);
		CHECK(Round(Normalize(values[11], lowestValue, highestValue, normalized_maximum), 2) == 98.21);
		CHECK(Normalize(values[12], lowestValue, highestValue, normalized_maximum) == 100);
	}
}
