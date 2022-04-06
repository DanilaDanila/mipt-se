cmake_minimum_required(VERSION 3.15)
set (CMAKE_CXX_STANDARD 14)


add_library(BitSet BitSet.h BitSet.cpp)

add_executable(bs_test BitSet.h tests.cpp)
target_link_libraries(bs_test BitSet)
