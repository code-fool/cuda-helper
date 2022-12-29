#!/bin/bash
BUILD_DIR="build-release"
mkdir -p $BUILD_DIR
cmake -DCUDA_HELPER_BUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Release -S . -B $BUILD_DIR
cmake --build $BUILD_DIR --clean-first


cd $BUILD_DIR
./cuda-helper-test
