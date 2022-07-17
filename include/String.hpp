#pragma once
#include "std.hpp"

/* std::string replacement */

namespace seed
{
	class string
	{
	public:
		string();
		string(const char* text);
		string(char text[]);
		string(const std::string& text);
		string(const seed::string& text);

		string(const int& value);
		string(const float& value);
		string(const double& value);
		string(const long& value);

		std::string data() const;
		int size() const;

		bool starts_with(const seed::string& text) const;
		bool ends_with(const seed::string& text) const;
		bool is_digit() const;

		string clean_decimals() const;

		/* Compare to another seed::string */
		bool operator==(const seed::string& other) const
		{
			return (p_data == other.data());
		}

		/* Compare seed::string to char* */
		bool operator==(const char* other)
		{
			return (p_data == other);
		}

		/* Compare seed::string to std::string */
		//bool operator==(const std::string& other) const
		//{
		//	return (p_data == other);
		//}

		/* Add two or more seed::strings together */
		string operator+(const string& other) const
		{
			return p_data + other.data();
		}

		/* Construct seed::string from multiple const* chars */
		string operator+(const char* other) const
		{
			return p_data + other;
		}

		string operator*(const int& count) const
		{
			std::string result = "";
			for (int i = 0; i < count; i++)
				result += p_data;

			return result;
		}

		void operator*=(const int& count)
		{
			std::string result = "";
			for (int i = 0; i < count; i++)
				result += p_data;

			p_data = result;
		}


	private:
		std::string p_data;
	};

	/* ostream overload for seed::string */
	inline std::ostream& operator<<(std::ostream& stream, const string& other)
	{
		stream << other.data();
		return stream;
	}
}