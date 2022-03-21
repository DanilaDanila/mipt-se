cmake_minimum_required(VERSION 3.15)
set (CMAKE_CXX_STANDARD 14)

project(Rational)

add_library(Rational rational.cpp)

add_executable(test tests.cpp)
target_link_libraries(test Rational)
