#!/bin/sh

TESTS=OFF

mkdir build
cd build

cmake -D BUILD_TESTING=${TESTS} -D ENABLE_COVERAGE:BOOL=TRUE ..
cmake --build . -- -j2

case ${TESTS} in
    ON) ctest -j2
esac

cpack .
