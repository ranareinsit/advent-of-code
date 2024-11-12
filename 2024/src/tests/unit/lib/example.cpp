#include <catch2/catch_test_macros.hpp>

#include <example/example.hpp>

TEST_CASE("adding numbers work", "[example]")
{
    CHECK(example::add(0, 0) == 0);
    CHECK(example::add(0, 7) == 7);
    CHECK(example::add(7, 0) == 7);
    CHECK(example::add(7, 7) == 14);
}
