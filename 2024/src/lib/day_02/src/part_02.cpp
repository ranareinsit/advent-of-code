#include <day_02/common.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

int countValidRowsWithRemoval(const std::vector<std::vector<int>>& data) {
	int count = 0;
	for (const auto& row : data) {
		if (day_02::canBeValidWithOneRemoval(row)) {
			++count;
		}
	}
	return count;
}

int main() {
	std::vector<std::vector<int>> data;

	try {
		day_02::parseInput("input.txt", data);
	}
	catch (const std::exception& e) {
		std::cerr << e.what();
		return 1;
	}

	int monotonicCount = countValidRowsWithRemoval(data);
	std::cout << "Number of monotonic rows: " << monotonicCount << std::endl;

	return 0;
}

