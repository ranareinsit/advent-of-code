#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <optional>
#include "common.cpp"

/*
63866497
*/

int main() {
	std::ifstream inputFile("input.txt");
	if (!inputFile.is_open()) {
		std::cerr << "Failed to open file!" << std::endl;
		return 1;
	}

	std::string text((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
	inputFile.close();

	std::vector<std::string> delimiters = { "do()" };
	std::vector<std::string> lines = day_03::splitByStrings(text, delimiters);

	int sum = 0;

	for (const auto& line : lines) {
		if (!line.empty()) {
			std::cout << line << std::endl;
			day_03::Search sm;  
			std::istringstream stream(line);  // Convert line to stream
			std::vector<std::string> found = sm.start(stream);  // Process the line as a stream
			for (const auto& str : found) {
				size_t start = str.find('(');
				size_t end = str.find(')');
				if (start != std::string::npos && end != std::string::npos && start < end) {
					std::string numbers = str.substr(start + 1, end - start - 1);
					std::istringstream iss(numbers);
					std::string num1, num2;
					if (std::getline(iss, num1, ',') && std::getline(iss, num2, ',')) {
						int n1 = std::stoi(num1);
						int n2 = std::stoi(num2);
						std::cout << "numbers: " << num1 << " " << num2 << std::endl;
						sum += n1 * n2;  // Multiply and add to sum
					}
				}
			}
		}
	}

	std::cout << "Sum of results: " << sum << std::endl;

	return 0;
}
