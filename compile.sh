#!/bin/sh

TESTS=FALSE
COVERAGE=TRUE

if [[ -e build ]]; then
    rm -r build
fi

mkdir build
cd build

cmake -DBUILD_TESTING:BOOL=${TESTS} -DENABLE_COVERAGE:BOOL=${COVERAGE} ..
cmake --build . -- -j2

case ${TESTS} in
    TRUE) ctest -j2
esac

#cpack .
