cmake_minimum_required(VERSION 3.14)
project(L1)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
include_directories(
        src/figures
        src/container
        src
        src/cli
        src/exceptions
        ${GTEST_INCLUDE_DIRS})

set (FIGURES
        src/figures/point.cpp
        src/figures/shape.cpp
        src/figures/pentagram.cpp
        src/figures/text.cpp
        src/figures/atanSegment.cpp
        src/figures/pentagramText.cpp
        )

set (CLI src/cli/myCli.cpp)

set (TESTSOURCE src/test.cpp)

add_executable(test ${FIGURES} ${TESTSOURCE})
add_executable(demo ${FIGURES} ${CLI} src/demo.cpp)
add_executable(demo2 ${CLI} src/demo2.cpp)
add_executable(demo3 ${FIGURES} ${CLI} src/demo3.cpp)
target_link_libraries(test ${GTEST_LIBRARIES} pthread)