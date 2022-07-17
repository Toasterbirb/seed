cmake_minimum_required(VERSION 3.12)

project(seed
	VERSION 0.0.1
	LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(TESTS "Compile the test binary" ON)
option(BUILD_LIB "Compile the static library" ON)

# Headers
include_directories(include/ vendor/)

set(MATH_SRC
	src/math/average.cpp
	src/math/normalize.cpp
	src/math/limits.cpp
	src/math/round.cpp)

set(STRING_SRC
	src/strings/clean_decimals.cpp
	src/strings/trim_char.cpp
	src/strings/char_case.cpp
	src/strings/string.cpp)

set(FILESYSTEM_SRC
	src/filesystem/filepaths.cpp
	src/filesystem/fileio.cpp)

set(CRYPTO_SRC
	src/crypto/md5sum.cpp)

set(MISC_SRC
	src/misc/helloworld.cpp)

if (TESTS)
	add_executable(seed_tests
		src/main.cpp
		${CRYPTO_SRC}
		${MATH_SRC}
		${FILESYSTEM_SRC}
		${STRING_SRC}
		${MISC_SRC})

	target_precompile_headers(seed_tests
		PRIVATE include/std.hpp)

	target_link_libraries(seed_tests crypto)
endif()

if (BUILD_LIB)
	add_library(seed STATIC
		${CRYPTO_SRC}
		${MATH_SRC}
		${FILESYSTEM_SRC}
		${STRING_SRC}
		${MISC_SRC})

	target_compile_definitions(seed PRIVATE -DDOCTEST_CONFIG_DISABLE)
	target_link_libraries(seed crypto)
endif()
