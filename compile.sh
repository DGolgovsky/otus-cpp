#!/bin/sh

TESTS=OFF

mkdir build
cd build

cmake -DBUILD_TESTING=${TESTS} -DENABLE_COVERAGE:BOOL=TRUE ..
cmake --build . -- -j2

case ${TESTS} in
    ON) ctest -j2
esac

cpack .
