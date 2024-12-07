#include "common.cpp"
#include <array>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <optional>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>
using namespace std;



vector<pair<intmax_t, vector<pair<char, intmax_t>>>> init(string filename) {
	string line;
	ifstream file(filename);
	vector<pair<intmax_t, vector<pair<char, intmax_t>>>>  equations;
	while (getline(file, line)) {
		string sum;
		vector<pair<char, intmax_t>> nums;
		size_t i = 0;
		for (; i < line.size(); i++) {
			if (line[i] == ':') { ++i; break; }
			sum += line[i];
		}

		string num;
		for (; i < line.size(); i++) {
			if (line[i] == ' ') {
				if (num.size() > 0) {
					nums.push_back({ '+',stoll(num) });
				}
				num = "";
				continue;
			}
			num += line[i];
		}
		if (num.size() > 0) {
			nums.push_back({ '+',stoll(num) });
		}

		equations.push_back({ stoll(sum), nums });
	}
	file.close();
	return equations;
}



intmax_t evaluate(vector<pair<char, intmax_t>> nums) {
	intmax_t result = nums[0].second;
	intmax_t current_sign = 0;
	for (size_t i = 1; i < nums.size(); i++) {
		if (nums[i].first == '+') {
			result += nums[i].second;
			current_sign++;
		}
		if (nums[i].first == '*') {
			result *= nums[i].second;
			current_sign++;
		}
	}

	return result;
}


int main() {
	vector<pair<intmax_t, vector<pair<char, intmax_t>>>> equations = init("input.txt");

	vector<intmax_t> total;
	intmax_t total2 = 0;


	for (auto& equation : equations) {
		auto [result, elements] = equation;
		bool found = false;

		intmax_t sub_res = evaluate(elements);
		if (sub_res == equation.first) {
			total.push_back(sub_res);
			total2 += sub_res;
			found = true;
			continue;
		}

		// TODO
	}


	cout << "result: " << total.size() << endl;


	return 0;
}

/*

*/