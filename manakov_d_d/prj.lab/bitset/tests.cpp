#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <bitset/bitset.h>

TEST_CASE("just compiles") { BitSet bs; }

TEST_CASE("should compiles") { BitSet bset(7, false); }
