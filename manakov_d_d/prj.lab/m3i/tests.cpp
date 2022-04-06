#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <m3i/m3i.h>

TEST_CASE("just compiles") { M3i m3i(3, 4, 5); }
