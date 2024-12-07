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

struct Cell {
	int x, y;
	char value;
	int direction;
};


struct Matrix {
	vector<vector<Cell>> cells;

	// Default constructor
	Matrix() = default;

	// Set a cell value
	void set(int x, int y, char value) {
		while (cells.size() <= y) {
			cells.push_back(vector<Cell> {});
		}
		while (cells[y].size() <= x) {
			cells[y].push_back(Cell{ -1, -1, '.', -1 });
		}

		cells[y][x] = Cell{ x, y, value, -1 };
	}

	// Get a cell value
	Cell get(int x, int y) {
		if (y < cells.size() && x < cells[y].size()) {
			return cells[y][x];
		}
		return Cell{ -1, -1, '?', -1 }; // Return an empty cell if out of bounds
	}

	// Remove a cell
	bool erase(int x, int y) {
		if (y < cells.size() && x < cells[y].size()) {
			cells[y][x] = Cell{ -1, -1, '?', -1 }; // Empty cell
			return true;
		}
		return false;
	}

	// Find a cell
	Cell* find(int x, int y) {
		if (y < cells.size() && x < cells[y].size()) {
			return &cells[y][x];
		}
		return nullptr;
	}

};

struct Sequence {
	string direction;
	vector<Cell> cells;

	void add(const Cell& cell) {
		cells.push_back(cell);
	}
};

Cell checkBound(Matrix& matrix, pair<int, int> p) {
	int x = p.first;
	int y = p.second;

	if (y >= 0 && y < matrix.cells.size() && x >= 0 && x < matrix.cells[0].size()) {
		return matrix.get(x, y);
	}
	return Cell{ -1, -1, '?', -1 };
}

vector<vector<Cell>> traverse(Matrix& matrix, Cell cell) {
	int x = cell.x;
	int y = cell.y;

	auto pcb = [&matrix](pair<int, int> p) { return checkBound(matrix, p); };


	vector<Cell> top = { pcb({x - 1, y - 1}), pcb({x + 0, y - 1}), pcb({x + 1, y - 1}) };
	vector<Cell> mid = { pcb({x - 1, y + 0}), pcb({x + 0, y + 0}), pcb({x + 1, y + 0}) };
	vector<Cell> bot = { pcb({x - 1, y + 1}), pcb({x + 0, y + 1}), pcb({x + 1, y + 1}) };
	vector<vector<Cell>> result = {
		top, mid, bot
	};

	return result;
}

int main() {
	int y = 0;
	int result = 0;
	Matrix matrix;
	Cell current_point = {};
	string line;
	ifstream file("input.txt");
	// obstructions : #
	unordered_map<char, int> directions = {
		{'^', 0},
		{'>', 90},
		{'v', 180},
		{'<', 270}
	};

	//
	while (getline(file, line)) {
		for (size_t x = 0; x < line.size(); x++) {
			for (auto it : directions) {
				if (it.first == line[x]) {
					current_point = { (int)(x), y, it.first, it.second };
				}
			}
			matrix.set(x, y, line[x]);
		}
		++y;
	}

	file.close();



	bool out_of_map = false;
	while (!out_of_map) {
		vector<vector<Cell>> around = traverse(matrix, matrix.get(current_point.x, current_point.y));

		Cell next_point = {};
		if (current_point.direction == 0) {
			next_point = around[0][1];
		}
		if (current_point.direction == 90) {
			next_point = around[1][2];
		}
		if (current_point.direction == 180) {
			next_point = around[2][1];
		}
		if (current_point.direction == 270) {
			next_point = around[1][0];
		}
		next_point.direction = current_point.direction;

		if (next_point.value == '#') {
			if (current_point.direction == 0) {
				next_point = around[1][2];
			}
			if (current_point.direction == 90) {
				next_point = around[2][1];
			}
			if (current_point.direction == 180) {
				next_point = around[1][0];
			}
			if (current_point.direction == 270) {
				next_point = around[0][1];
			}
			next_point.direction = current_point.direction + 90 > 270 ? 0 : current_point.direction + 90;

		}

		current_point = next_point;

		if (current_point.value == '.') {
			matrix.set(current_point.x, current_point.y, 'X');
			result++;
		}

		if (next_point.value == '?') {
			out_of_map = true;
			result++;
			break;
		}
	}

	cout << result << endl; // 5129

	return 0;
}