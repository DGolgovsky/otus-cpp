#!/bin/bash

#mkdir build
#cd build
cmake -DBUILD_TESTING=ON .
cmake --build . -- -j2
ctest -j2
