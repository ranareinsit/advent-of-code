#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

namespace day_01 {

	void parseInput(const std::string& fileName, std::vector<int>& left, std::vector<int>& right) {
		std::ifstream file(fileName);
		if (!file) {
			throw std::runtime_error("Failed to open " + fileName);
		}
		std::string line;
		while (std::getline(file, line)) {
			std::istringstream ss(line);
			int l, r;
			ss >> l >> r;
			left.push_back(l);
			right.push_back(r);
		}
	}

	int findAndEjectMin(std::vector<int>& vec) {
		if (vec.empty()) throw std::runtime_error("Vector is empty");
		auto minIt = std::min_element(vec.begin(), vec.end());
		int minValue = *minIt;
		vec.erase(minIt);
		return minValue;
	}

	int countOccurrences(const std::vector<int>& vec, int value) {
		return std::count(vec.begin(), vec.end(), value);
	}
}