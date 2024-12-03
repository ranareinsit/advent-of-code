#include "day_03/common.hpp"
#include <fstream>
#include <regex>
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <sstream>
#include <optional>

namespace day_03 {

	std::vector<Term> extractAndParseTerms(const std::string& filePath, const std::string& operationName) {
		std::vector<Term> parsedTerms;
		std::ifstream inputFile(filePath);

		if (!inputFile.is_open()) {
			std::cerr << "Error: Unable to open file: " << filePath << std::endl;
			return parsedTerms;
		}

		// Dynamically build the regular expression with the given operation name
		std::string regexPattern = operationName + R"(\((\d{1,3}),(\d{1,3})\))";
		std::regex validTermRegex(regexPattern);
		std::smatch match;
		std::string line;

		while (std::getline(inputFile, line)) {
			std::string::const_iterator searchStart(line.cbegin());
			while (std::regex_search(searchStart, line.cend(), match, validTermRegex)) {
				// Parse the operation and operands into the structure
				Term term;
				term.operationName = operationName;
				term.operand1 = std::stoi(match[1].str());
				term.operand2 = std::stoi(match[2].str());
				parsedTerms.push_back(term);
				searchStart = match.suffix().first; // Move past the current match
			}
		}

		inputFile.close();
		return parsedTerms;
	}

	std::vector<std::string> splitByStrings(const std::string& text, const std::vector<std::string>& delimiters) {
		std::vector<std::string> result;
		size_t start = 0;

		while (start < text.size()) {
			size_t minPos = std::string::npos;
			std::string currentDelimiter;

			// Find the next delimiter in the text
			for (const auto& delim : delimiters) {
				size_t pos = text.find(delim, start);
				if (pos != std::string::npos && (minPos == std::string::npos || pos < minPos)) {
					minPos = pos;
					currentDelimiter = delim;
				}
			}

			// If no delimiter was found, add the rest of the text
			if (minPos == std::string::npos) {
				result.push_back(text.substr(start));
				break;
			}

			// Add the text before the delimiter
			if (minPos > start) {
				result.push_back(text.substr(start, minPos - start));
			}

			// Add the delimiter itself
			result.push_back(currentDelimiter);

			// Move past the delimiter
			start = minPos + currentDelimiter.size();
		}

		return result;
	}

	class Search {
	public:
		bool ignore = false;
		std::string temp = "";
		//
		std::string target = "mul";
		//
		std::string start_ignore = "don\'t()";
		//
		std::string stop_ignore = "do()";

		std::vector<std::string> found;


		void drop_temp() {
			temp = "";
		}

		std::vector<std::string> start(std::istringstream& inputStream) {
			char ch;

			while (inputStream.get(ch)) {
				bool erase = true;

				temp = temp + ch;

				// if found name
				if (temp == stop_ignore) {
					ignore = false;
					drop_temp();
				}
				if (temp == start_ignore) {
					ignore = true;
					drop_temp();
				}
				if (temp == target) {
					// search value
					std::optional<std::string>  foundValue = valueSearch(inputStream);
					if (!ignore && foundValue.has_value()) {
						found.push_back(temp + foundValue.value());
						drop_temp();
					}
				}

				// if not
				if (temp.size() <= stop_ignore.size()) { // 2
					std::string sliced_stop_ignore = stop_ignore.substr(0, temp.size());
					if (sliced_stop_ignore == temp) {
						// but have part of it
						erase = false;
					}
				}

				if (temp.size() <= target.size()) { // 3
					std::string sliced_target = target.substr(0, temp.size());
					if (sliced_target == temp) {
						// but have part of it
						erase = false;
					}
				}

				if (temp.size() <= start_ignore.size()) { // 5
					std::string sliced_start_ignore = start_ignore.substr(0, temp.size());
					if (sliced_start_ignore == temp) {
						// but have part of it
						erase = false;
					}
				}

				// temp is not a part of any word
				if (erase) {
					drop_temp();
				}
			}

			return found;
		}

		bool checkIfNumber(char c) {
			return c >= '0' && c <= '9';
		}

		std::optional<std::string> valueSearch(std::istringstream& inputStream) {
			char ch;
			std::string current = "";
			inputStream.get(ch);

			if (ch != '(') {
				inputStream.unget();
				return std::nullopt;
			}
			current += ch;

			while (inputStream.get(ch)) {
				if (checkIfNumber(ch)) {
					current += ch;
					continue;
				}
				if (ch == ',') {
					break;
				}
				inputStream.unget();
				break;
			}

			if (ch != ',') {
				inputStream.unget();
				return std::nullopt;
			}
			current += ch;

			while (inputStream.get(ch)) {
				if (checkIfNumber(ch)) {
					current += ch;
					continue;
				}
				if (ch == ')') {
					break;
				}
				inputStream.unget();
				break;
			}

			if (ch != ')') {
				inputStream.unget();
				return std::nullopt;
			}
			current += ch;
			return current;
		};
	};

};