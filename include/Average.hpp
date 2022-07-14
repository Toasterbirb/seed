#pragma once
#include "std.hpp"

namespace seed
{
	/* Get the arverage value of an array / vector */
	template<typename T>
	double Average(std::vector<T> values)
	{
		T total = 0;
		for (int i = 0; i < values.size(); i++)
			total += values[i];

		return (double)total / values.size();
	}

	template<typename T>
	double Average(T values[], const int& value_count)
	{
		T total = 0;
		for (int i = 0; i < value_count; i++)
			total += values[i];

		return (double)total / value_count;
	}
}
