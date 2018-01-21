#!/bin/bash

mkdir build && cd "$_"
cmake -DBUILD_TESTING=OFF ..
cmake --build . -- -j2
ctest -j2
cpack .
