#pragma once
#include "std.hpp"

namespace seed
{
	std::string md5sum(const std::string& text);
	std::string md5sum(char data[], const int& size);
	std::string random_md5(const int& sample_size = 512);
}
