#!/bin/bash

TESTS=OFF

mkdir build && cd "$_"
cmake -DBUILD_TESTING=${TESTS} ..
cmake --build . -- -j2
case $TESTS in
    ON) ctest -j2
esac
cpack .
