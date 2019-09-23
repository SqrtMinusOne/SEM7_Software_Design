cmake_minimum_required(VERSION 3.14)
project(L1)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
include_directories(src/figures ${GTEST_INCLUDE_DIRS})

set (FIGURES src/figures/point.cpp src/figures/shape.cpp src/figures/pentagram.cpp src/figures/text.cpp)

set (TESTSOURCE src/test.cpp)

add_executable(test ${FIGURES} ${TESTSOURCE})
target_link_libraries(test ${GTEST_LIBRARIES} pthread)