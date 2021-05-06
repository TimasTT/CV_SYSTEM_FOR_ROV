cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(CV_SYSTEM_FOR_ROV VERSION 0.1.0)

option(BUILD_TESTS "Build tests" ON)

add_subdirectory(libs)
add_subdirectory(prog)

find_package(Threads)
add_subdirectory(tools/gate)

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif ()
