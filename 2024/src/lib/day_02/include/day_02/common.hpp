#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <stdexcept>


namespace day_02 {
	void parseInput(const std::string& fileName, std::vector<std::vector<int>>& data);

	bool isMonotonicAndValid(const std::vector<int>& row);

	bool canBeValidWithOneRemoval(const std::vector<int>& row);
}
