#pragma once
#include "std.hpp"

namespace seed
{
	/*** Templates ***/
	template<typename T>
	T Clamp(const T& value, const T& min, const T& max)
	{
		if (value < min)
			return min;
		else if (value > max)
			return max;

		return value;
	}

	/* Find the lowest or highest value in a list */
	template<typename T>
	T Min(T values[], const int& value_count)
	{
		if (value_count < 1)
			return 0;

		T current_min = values[0];
		for (int i = 1; i < value_count; i++)
		{
			if (values[i] < current_min)
				current_min = values[i];
		}
		return current_min;
	}

	template<typename T>
	T Min(std::vector<T> values)
	{
		if (values.size() == 0)
			return 0;

		T current_min = values[0];
		for (int i = 1; i < values.size(); i++)
		{
			if (values[i] < current_min)
				current_min = values[i];
		}
		return current_min;
	}

	template<typename T>
	T Max(T values[], const int& value_count)
	{
		if (value_count < 1)
			return 0;

		T current_max = values[0];
		for (int i = 1; i < value_count; i++)
		{
			if (values[i] > current_max)
				current_max = values[i];
		}
		return current_max;
	}

	template<typename T>
	T Max(std::vector<T> values)
	{
		if (values.size() == 0)
			return 0;

		T current_max = values[0];
		for (int i = 1; i < values.size(); i++)
		{
			if (values[i] > current_max)
				current_max = values[i];
		}
		return current_max;
	}

}
