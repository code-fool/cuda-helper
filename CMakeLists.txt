cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
option(HIP_HELPER_BUILD "Enable building HIP" OFF)
if(HIP_HELPER_BUILD)
    message(INFO "chichichichichichichichichichichichi")
endif()
# project(cuda-helper LANGUAGES CXX CUDA)
project(blake3_cuda LANGUAGES CXX HIP)

# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# include(CheckLanguage)
# check_language(CUDA)
# set(CMAKE_CUDA_STANDARD 11)
# set(CMAKE_CUDA_STANDARD_REQUIRED ON)

# if(NOT CUDAToolkit_FOUND)
#     include(FindCUDAToolkit)
# endif()
# include_directories(${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES})

include_directories(include)


list(APPEND CMAKE_PREFIX_PATH /opt/rocm/hip /opt/rocm)
find_package(hip REQUIRED)


file(GLOB_RECURSE source_file LIST_DIRECTORIES false src/*.cpp src/*.c src/*.cu)
message(${PROJECT_NAME})
add_library(${PROJECT_NAME} STATIC ${source_file})
target_link_libraries(${PROJECT_NAME}
                        # PRIVATE CUDA::cudart
                        # PRIVATE CUDA::cuda_driver
                        PRIVATE hip::device
                        )
option(CUDA_HELPER_BUILD_TESTS "Enable building google test units" OFF)

if(CUDA_HELPER_BUILD_TESTS)
    #Google Unit Test
    option(BUILD_GMOCK "" OFF)
    option(INSTALL_GTEST "" OFF)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.12.0
    )
    FetchContent_MakeAvailable(googletest)

    file(GLOB_RECURSE test_files LIST_DIRECTORIES false test/*.cpp test/*.c test/*.cu src/*.cpp src/*.c)
    set(TEST_EXE ${PROJECT_NAME}-test)
    add_executable(${TEST_EXE} ${test_files})
    target_link_libraries(${TEST_EXE}
                        #   PRIVATE CUDA::cudart
                        #   PRIVATE CUDA::cuda_driver
                        #   这里这个可以暂时先不用上···
                        #   PRIVATE CUDA::cupti   
                          PRIVATE hip::device
                          PRIVATE gtest
                          PRIVATE gtest_main)
    include(GoogleTest)
    gtest_discover_tests(${TEST_EXE})
endif()

if(APPLE)
    message(FATAL_ERROR "Unsupported on mac")
endif()
