#include "std.hpp"
#include "Crypto.hpp"

namespace seed
{
	void HelloWorld()
	{
		std::cout << "Hello world from the Seed library!\nHere's a random MD5 checksum I happened to find: " << random_md5() << std::endl;
	}
}
