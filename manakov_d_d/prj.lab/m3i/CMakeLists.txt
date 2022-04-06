cmake_minimum_required(VERSION 3.15)

project(M3i)

add_library(M3i m3i.h m3i.cpp)

add_executable(test_m3i m3i.h tests.cpp)
target_link_libraries(test_m3i M3i)
