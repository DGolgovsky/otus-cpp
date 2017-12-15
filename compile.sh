#!/bin/sh

mkdir build
cd build
cmake -DBUILD_TESTING=ON .. -- -j2 --coverage
cmake --build . -- -j2
ctest -j2

