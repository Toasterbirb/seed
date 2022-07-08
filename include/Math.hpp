#include "std.hpp"

namespace seed
{
	double Round(const double& value, const int& accuracy);
	double Normalize(const double& value, const double& min, const double& max, const double& normalized_maximum);


	/*** Templates ***/
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
