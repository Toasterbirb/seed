#include "Math.hpp"
#include "doctest/doctest.h"

namespace seed
{
	TEST_CASE("Calculate average from double array")
	{
		double values[5] =
		{
			4, 5, 1.6, 16.5, 3.6
		};

		std::vector<double> valueVector =
		{
			4, 5, 1.6, 16.5, 3.6
		};

		CHECK(Round(Average(values, 5), 2) == 6.14);
		CHECK(Round(Average(valueVector), 2) == 6.14);
	}

	TEST_CASE("Calculate average from float array")
	{
		float values[5] =
		{
			4, 5, 1.6f, 16.5f, 3.6f
		};

		CHECK(Round(Average(values, 5), 2) == 6.14);
	}

	TEST_CASE("Calculate average from int array")
	{
		int values[5] =
		{
			4, 5, 1, 16, 3
		};

		CHECK(Round(Average(values, 5), 2) == 5.8);
	}

}
