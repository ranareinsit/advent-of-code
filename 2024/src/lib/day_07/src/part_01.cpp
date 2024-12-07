#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <set>
#include <ratio>
#include <chrono>

using namespace std;

struct qi {
	char op;
	int idx;
	intmax_t val;
};

bool sum_possible(const vector<intmax_t>& numbers, intmax_t target) {
	// last op, last index, last size
	std::deque<qi> queue = {
	   qi('+', 1, numbers[0] + numbers[1]),
	   qi('*', 1, numbers[0] * numbers[1]),
	};
	while (queue.size() > 0) {
		auto [op, idx, res] = queue.front();
		queue.pop_front();
		if (res > target) { continue; }
		if (idx == numbers.size() - 1) {
			if (res == target) { return true; }
			continue;
		}
		queue.push_back(qi('+', idx + 1, res + numbers[idx + 1]));
		queue.push_back(qi('*', idx + 1, res * numbers[idx + 1]));
	}
	return false;
}

vector<intmax_t > parseNumbers(const string& input) {
	vector<intmax_t > numbers;
	istringstream stream(input);
	intmax_t number;
	while (stream >> number) {
		numbers.push_back(number);
	}
	return numbers;
}

int main() {
	auto start = chrono::high_resolution_clock::now();
	intmax_t  result = 0;
	ifstream file("input.txt");
	string line;
	while (getline(file, line)) {
		auto del = line.find(':');
		intmax_t  target = stoll(line.substr(0, del));
		vector<intmax_t> numbers = parseNumbers(line.substr(del + 1));
		cout << target << endl;
		if (sum_possible(numbers, target)) {result += target;}
	}
	cout << "result:" << result << endl;
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> duration = end - start;
	cout << "duration: " << duration.count() << " sec" << endl;
	return 0;
}
