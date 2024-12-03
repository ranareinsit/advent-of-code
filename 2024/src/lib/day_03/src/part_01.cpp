#include <day_03/common.hpp>
#include <iostream>
#include <vector>

int main() {
	std::string filePath = "input.txt";
	std::string operationName = "mul";
	int result = 0;

	std::vector<day_03::Term> terms = day_03::extractAndParseTerms(filePath, operationName);

	for (const auto& term : terms) {
		int sub_result = term.operand1 * term.operand2;
		// std::cout << term.operationName << "(" << term.operand1 << "," << term.operand2 << ") = " << sub_result << std::endl;
		result += sub_result;
	}

	std::cout << "result is: " << result << std::endl;

	return 0;
}
