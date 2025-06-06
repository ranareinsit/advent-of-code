#include "common.cpp"
#include <fstream>
#include <regex>
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <sstream>
#include <optional>
#include <variant>
#include <array>
#include <set>
#include <map>
#include <deque>
using namespace std;


bool updates_are_already_in_the_right_order(std::vector<std::pair<long, long>>& ruleset, vector<long>& sequence) {
	bool valid = true;

	for (size_t i = 1; i < sequence.size(); i++) {
		auto prev = sequence[i - 1];
		auto curr = sequence[i];
		bool found = false;

		for (auto& rule : ruleset) {
			if (rule.first == prev && rule.second == curr) {
				found = true;
				break;
			}
		}

		if (!found) {
			valid = false;
			break;
		}
	}

	return valid;
}

vector<long> fix_incorrectly_ordered_updates(set <long>& unic, std::vector<std::pair<long, long>>& ruleset, vector<long>& sequence) {
	vector<long> copy = sequence;

	while (!updates_are_already_in_the_right_order(ruleset, copy)) {
		pair<int, int> temp;
		int shift = 0;

		for (size_t i = 1; i < copy.size(); i++) { // welp, it works.
			bool found = false;
			for (auto& rule : ruleset) {
				if (rule.second == copy[i - 1] && rule.first == copy[i]) {
					found = true;
					swap(copy[i - 1], copy[i]);
					break;
				}
			}
			if (found) {break;}
		}
	}

	return copy;
}



int main() {
	set <long> unic;
	std::vector<std::pair<long, long>> page_ordering_rules;
	std::vector<std::vector<long>> updates;
	//
	std::ifstream file("input.txt");
	std::string line;
	//
	while (std::getline(file, line)) {
		if (line.size() == 0) { break; }

		std::string left;
		std::string right;
		bool lft = true;
		for (size_t i = 0; i < line.size(); i++) {
			if (line[i] == '|') {
				lft = false;
				++i;
			}
			if (lft) { left += line[i]; }
			if (!lft) { right += line[i]; }
		}
		page_ordering_rules.push_back(std::pair<long, long>{ std::stoi(left), std::stoi(right) });
		unic.insert(std::stoi(left));
		unic.insert(std::stoi(right));
	}

	while (std::getline(file, line)) {
		std::string temp;
		std::vector<long> temp_vec;
		for (size_t i = 0; i < line.size(); i++) {
			if (line[i] == ',') {
				temp_vec.push_back(std::stoi(temp));
				temp = "";
				continue;
			}
			temp += line[i];

		}
		temp_vec.push_back(std::stoi(temp));
		temp = "";
		updates.push_back(temp_vec);
	}

	file.close();

	long result = 0;

	for (auto& update : updates) {
		bool check = updates_are_already_in_the_right_order(page_ordering_rules, update);
		if (!check) {
			auto fixed = fix_incorrectly_ordered_updates(unic, page_ordering_rules, update);
			long mid = floor(fixed.size() / 2);
			cout << "fixed mid: " << fixed[mid] << endl;
			result += fixed[mid];
		}

	}

	cout << result << endl; // 7380


	return 0;
}
