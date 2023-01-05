#!/bin/bash
BUILD_DIR="build-release"
mkdir -p $BUILD_DIR
# cmake -DCUDA_HELPER_BUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Release -S . -B $BUILD_DIR
# cmake --build $BUILD_DIR --clean-first

cmake -S . -B $BUILD_DIR -DCMAKE_CXX_COMPILER=/opt/rocm-5.4.0/llvm/bin/clang++ -DCMAKE_BUILD_TYPE=release -DCUDA_HELPER_BUILD_TESTS=ON -DHIP_HELPER_BUILD=ON


cmake --build $BUILD_DIR --clean-first

cd $BUILD_DIR
./cuda_helper-test
