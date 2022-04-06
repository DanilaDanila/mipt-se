cmake_minimum_required(VERSION 3.15)
set (CMAKE_CXX_STANDARD 14)

add_library(Rational rational.h rational.cpp)

add_executable(rational_test rational.h tests.cpp)
target_link_libraries(rational_test Rational)
