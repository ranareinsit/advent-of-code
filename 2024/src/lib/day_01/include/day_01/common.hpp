#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <stdexcept>

namespace day_01 {
    void parseInput(const std::string& fileName, std::vector<int>& left, std::vector<int>& right);

    int findAndEjectMin(std::vector<int>& vec);

    int countOccurrences(const std::vector<int>& vec, int value);
};
