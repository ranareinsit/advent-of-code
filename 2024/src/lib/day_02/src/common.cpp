#include "day_02/common.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace day_02 {
	void parseInput(const std::string& fileName, std::vector<std::vector<int>>& data) {
		std::ifstream file(fileName);
		if (!file) {
			throw std::runtime_error("Failed to open " + fileName);
		}
		std::string line;
		while (std::getline(file, line)) {
			std::istringstream ss(line);
			std::vector<int> row;
			int value;
			while (ss >> value) {
				row.push_back(value);
			}
			data.push_back(row);
		}
	}

	bool isMonotonicAndValid(const std::vector<int>& row) {
		bool increasing = true, decreasing = true;
		for (size_t i = 1; i < row.size(); ++i) {
			if (row[i - 1] >= row[i]) increasing = false;
			if (row[i - 1] <= row[i]) decreasing = false;

			if (std::abs(row[i] - row[i - 1]) > 3) {
				return false;
			}
		}
		return increasing || decreasing;
	}

	bool canBeValidWithOneRemoval(const std::vector<int>& row) {
		auto isValid = [](const std::vector<int>& seq) {
			bool increasing = true, decreasing = true;
			for (size_t i = 1; i < seq.size(); ++i) {
				if (seq[i] - seq[i - 1] > 3 || seq[i - 1] - seq[i] > 3) return false;
				if (seq[i - 1] >= seq[i]) increasing = false;
				if (seq[i - 1] <= seq[i]) decreasing = false;
			}
			return increasing || decreasing;
			};

		if (isValid(row)) return true;

		for (size_t i = 0; i < row.size(); ++i) {
			std::vector<int> modifiedRow = row;
			modifiedRow.erase(modifiedRow.begin() + i);
			if (isValid(modifiedRow)) return true;
		}
		return false;
	}

}
