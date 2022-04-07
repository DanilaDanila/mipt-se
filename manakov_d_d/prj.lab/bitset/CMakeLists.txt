cmake_minimum_required(VERSION 3.15)
set (CMAKE_CXX_STANDARD 14)


add_library(bitset bitset.h bitset.cpp)

add_executable(bs_test bitset.h tests.cpp)
target_link_libraries(bs_test bitset)
