#include <catch2/catch_test_macros.hpp>

#include <day_01/common.hpp>

TEST_CASE("parse input to vectors", "[day_01]")
{
	std::vector<int> left, right;
	day_01::parseInput("test-input.txt", left, right);
	/*
	3   4
	4   3
	2   5
	1   3
	3   9
	3   3
	*/
	CHECK(left[0] == 3);
	CHECK(left[5] == 3);
	CHECK(right[0] == 4);
	CHECK(right[5] == 3);
}

TEST_CASE("find And Eject Min from vector", "[day_01]") {
	std::vector<int> left, right;
	day_01::parseInput("test-input.txt", left, right);
	/*
	3   4
	4   3
	2   5
	1   3
	3   9
	3   3
	*/
	CHECK(day_01::findAndEjectMin(left) == 1);
	CHECK(day_01::findAndEjectMin(right) == 3);
}
