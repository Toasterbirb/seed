# Seed
Seed is the thing that a lot of plants and software grows out of (I guess)

Seed in this case is a C++ ~~standard~~ library with functions that I can't be bothered to remake anymore and instead just include from this library.

## Compiling the tests
```sh
mkdir build
cd build
cmake ..
make -j$(nproc)
```

## Using
Just add the directory as a subdirectory in a CMake project and simply include the headerfiles. Should also work without CMake
