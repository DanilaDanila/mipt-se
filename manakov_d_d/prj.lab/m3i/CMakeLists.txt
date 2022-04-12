cmake_minimum_required(VERSION 3.15)

project(M3i)

add_library(m3i m3i.h m3i.cpp)

add_executable(m3i_test m3i.h tests.cpp)
target_link_libraries(m3i_test m3i)
