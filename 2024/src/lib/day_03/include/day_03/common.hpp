#pragma once
#include <string>
#include <vector>

namespace day_03 {
    // Define Term structure
    struct Term {
        std::string operationName;
        int operand1;
        int operand2;
    };

    // Function declaration
    std::vector<Term> extractAndParseTerms(const std::string& filePath, const std::string& operationName);

}
