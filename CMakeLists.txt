cmake_minimum_required(VERSION 3.12)

project(seed
	VERSION 0.0.1
	LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(TESTS "Compile the test binary" ON)

# Headers
include_directories(include/ vendor/)

if (TESTS)
	set(MATH_SRC
		src/math/average.cpp
		src/math/normalize.cpp
		src/math/limits.cpp
		src/math/round.cpp)

	set(STRING_SRC
		src/strings/clean_decimals.cpp
		src/strings/trim_char.cpp)

	add_executable(seed_tests
		src/main.cpp
		${MATH_SRC}
		${STRING_SRC})

	target_precompile_headers(seed_tests
		PRIVATE include/std.hpp)
endif()
