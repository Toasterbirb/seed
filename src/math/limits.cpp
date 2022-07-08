#include "Math.hpp"
#include "doctest/doctest.h"

namespace seed
{
	/*** Template tests ***/
	TEST_CASE("Find the lowest value from a list of values")
	{
		SUBCASE("Integers")
		{
			int ValueArray[6] 				= { 3, 6, 1, -5, 6 };
			std::vector<int> ValueVector 	= { 3, 6, 1, -5, 6 };

			CHECK(Min(ValueArray, 6) 	== -5);
			CHECK(Min(ValueVector) 		== -5);
		}

		SUBCASE("Floats")
		{
			float ValueArray[6] 			= { 3.32f, 6.446f, 1.12f, -5.004f, 6.999f };
			std::vector<float> ValueVector 	= { 3.32f, 6.446f, 1.12f, -5.004f, 6.999f };

			CHECK(Min(ValueArray, 6) 	== -5.004f);
			CHECK(Min(ValueVector) 		== -5.004f);
		}

		SUBCASE("Doubles")
		{
			double ValueArray[6] 			= { 3.32, 6.446, 1.12, -5.004, 6.999 };
			std::vector<double> ValueVector = { 3.32, 6.446, 1.12, -5.004, 6.999 };

			CHECK(Min(ValueArray, 6) 	== -5.004);
			CHECK(Min(ValueVector) 		== -5.004);
		}

		SUBCASE("Empty array / vector")
		{
			int emptyArray[0];
			CHECK(Min(emptyArray, 0) 	== 0);
			CHECK(Min(emptyArray, -2) 	== 0);

			std::vector<int> emptyVector;
			CHECK(Min(emptyVector) == 0);

			int arrayWithOneObject[1] = { 5 };
			CHECK(Min(arrayWithOneObject, 1) == 5);
		}
	}

	TEST_CASE("Find the highest value from a list of values")
	{
		SUBCASE("Integers")
		{
			int ValueArray[6] 				= { 3, 6, 1, -5, 6 };
			std::vector<int> ValueVector 	= { 3, 6, 1, -5, 6 };

			CHECK(Max(ValueArray, 6) 	== 6);
			CHECK(Max(ValueVector) 		== 6);
		}

		SUBCASE("Floats")
		{
			float ValueArray[6] 			= { 3.32f, 6.446f, 1.12f, -5.004f, 6.999f };
			std::vector<float> ValueVector 	= { 3.32f, 6.446f, 1.12f, -5.004f, 6.999f };

			CHECK(Max(ValueArray, 6) 	== 6.999f);
			CHECK(Max(ValueVector) 		== 6.999f);
		}

		SUBCASE("Doubles")
		{
			double ValueArray[6] 			= { 3.32, 6.446, 1.12, -5.004, 6.999 };
			std::vector<double> ValueVector = { 3.32, 6.446, 1.12, -5.004, 6.999 };

			CHECK(Max(ValueArray, 6) 	== 6.999);
			CHECK(Max(ValueVector) 		== 6.999);
		}

		SUBCASE("Empty array / vector")
		{
			int emptyArray[0];
			CHECK(Max(emptyArray, 0) 	== 0);
			CHECK(Max(emptyArray, -2) 	== 0);

			std::vector<int> emptyVector;
			CHECK(Max(emptyVector) == 0);

			int arrayWithOneObject[1] = { 5 };
			CHECK(Max(arrayWithOneObject, 1) == 5);
		}
	}
}
