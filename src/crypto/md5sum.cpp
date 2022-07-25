#include <openssl/md5.h>
#include "Crypto.hpp"
#include "doctest/doctest.h"

namespace seed
{
	std::string md5sum(const std::string& text)
	{
		unsigned char result_chararr[MD5_DIGEST_LENGTH];
		MD5((unsigned char*)text.c_str(), text.length(), result_chararr);

		std::string result;
		char buffer[sizeof(int)];
		for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
		{
			snprintf(buffer, sizeof(int), "%02x", result_chararr[i]);
			result += buffer;
		}
		return result;
	}

	TEST_CASE("MD5 string hashing")
	{
		std::string hello_world = "hello world";
		std::string lorem_ipsum = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";

		CHECK(md5sum(hello_world) == "5eb63bbbe01eeed093cb22bb8f5acdc3");
		CHECK(md5sum(lorem_ipsum) == "db89bb5ceab87f9c0fcc2ab36c189c2c");
	}

	std::string md5sum(char data[], const int& size)
	{
		unsigned char result_chararr[MD5_DIGEST_LENGTH];
		MD5((unsigned char*)data, size, result_chararr);

		std::string result;
		char buffer[sizeof(int)];
		for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
		{
			snprintf(buffer, sizeof(int), "%02x", result_chararr[i]);
			result += buffer;
		}
		return result;
	}

	TEST_CASE("MD5 char[] hashing")
	{
		char hello_world[] = "hello world";
		char lorem_ipsum[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";

		CHECK(md5sum(hello_world, strlen(hello_world)) == "5eb63bbbe01eeed093cb22bb8f5acdc3");
		CHECK(md5sum(lorem_ipsum, strlen(lorem_ipsum)) == "db89bb5ceab87f9c0fcc2ab36c189c2c");
	}

	static std::string previous_md5hash = "";
	std::string random_md5(const int& sample_size)
	{
		std::ifstream random_file("/dev/urandom");
		if (!random_file.is_open())
		{
			std::cerr << "Coudn't open /dev/urandom for reading!" << std::endl;
		}

		char buffer[sample_size];
		random_file.read(buffer, sample_size);

		/* Also use the previous md5 hash as entropy to help in case
		 * this function is called repeatedly. Dunno how secure this is though */
		std::string md5hash = md5sum(buffer + previous_md5hash);
		previous_md5hash = md5hash;
		return md5hash;
	}

	TEST_CASE("Generate random md5 hashes")
	{
		/* Generate 100 hashes rapidly and make sure that there are no duplicates */
		int hash_count = 100;
		std::vector<std::string> hash_array;
		for (int i = 0; i < hash_count - 1; i++)
			hash_array.push_back(random_md5());

		/* Generate one hash with a custom sample size */
		hash_array.push_back(random_md5(1024));

		/* Compare the hashes to eachother */
		bool duplicate_found = false;
		int duplicate_count = 0;
		for (int i = 0; i < hash_count; i++)
		{
			for (int j = 1; j < hash_count; j++)
				if (i != j && hash_array[i] == hash_array[j])
				{
					duplicate_found = true;
					duplicate_count++;
				}
		}

		if (duplicate_found)
			std::cout << "Duplicate hash count: " << duplicate_count << std::endl;

		CHECK_FALSE(duplicate_found);
	}
}
