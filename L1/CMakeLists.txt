cmake_minimum_required(VERSION 3.14)
project(L1)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
include_directories(src/figures src/container src ${GTEST_INCLUDE_DIRS})

set (FIGURES
        src/figures/point.cpp
        src/figures/shape.cpp
        src/figures/pentagram.cpp
        src/figures/text.cpp
        src/figures/atanSegment.cpp
        src/figures/pentagramText.cpp
        )

set (HASHMAP src/container/hashMap.cpp)

set (TESTSOURCE src/test.cpp)
set (DEMOSOURCE src/demo.cpp)

add_executable(test ${FIGURES} ${HASHMAP} ${TESTSOURCE})
add_executable(demo ${FIGURES} ${HASHMAP} ${DEMOSOURCE})
target_link_libraries(test ${GTEST_LIBRARIES} pthread)