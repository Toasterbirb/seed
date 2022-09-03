#pragma once
#include "std.hpp"

namespace seed
{
	class ArgsParser
	{
	public:
		ArgsParser(const int& argc, char** argv);
		char** c_args() const;
		int arg_count() const;

		bool parse();
		std::map<std::string, std::string> key() const;
		bool has_key(const std::string& key);
		bool is_valid() const;

	private:
		std::map<std::string, std::string> key_values;
		int argc;
		char** argv;
		bool valid_args;
	};
}
