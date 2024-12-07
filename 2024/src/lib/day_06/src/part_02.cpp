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


const unordered_map<char, int> directions = {
	{'^', 0},
	{'>', 90},
	{'v', 180},
	{'<', 270}
};

const unordered_map<string, char> terms = {
	{ "up",'^'},
	{ "left",'>'},
	{ "down",'v'},
	{ "right",'<'},
	{ "untouched",'.'},
	{ "vertical_path",'|'},
	{ "horizontal_path",'-'},
	{ "outbound_path",'?'},
	{ "intersection_path",'+'},
	{ "obstruction",'#'}
};

const auto um_key_by_value = [](const auto& um, const auto& a) {for (const auto& [k, v] : um) { if (v == a) { return k; } }};

struct Cell {
	int x, y;
	char value;
};

const Cell empty_cell = { -1, -1, '?' };

struct Matrix {
	vector<vector<Cell>> cells;

	Matrix() = default;

	// Set a cell value
	void set(int x, int y, char value) {
		while (cells.size() <= y) {
			cells.push_back(vector<Cell> {});
		}
		while (cells[y].size() <= x) {
			cells[y].push_back(empty_cell);
		}
		cells[y][x] = Cell{ x, y, value };
	}

	// Get a cell value
	Cell get(int x, int y) {
		if (y < cells.size() && x < cells[y].size()) {
			return cells[y][x];
		}
		return empty_cell;
	}

	// Remove a cell
	bool erase(int x, int y) {
		if (y < cells.size() && x < cells[y].size()) {
			cells[y][x] = empty_cell;
			return true;
		}
		return false;
	}

	int size(char ch) {
		int found = 0;
		for (auto& row : cells) {
			for (auto& c : row) {
				if (c.value == ch) found++;
			}
		}
		return found;
	}

	Cell next(int x, int y, int d) {
		int cx = x;
		int cy = y;
		int direction = d;
		if (d == 0) { cy--; }
		if (d == 90) { cx++; }
		if (d == 180) { cy++; }
		if (d == 270) { cx--; }
		Cell result = get(cx, cy);
		if (result.value == terms.at("outbound_path")) { return empty_cell; }
		return result;
	}

	Cell next(Cell c, int d) {
		int cx = c.x;
		int cy = c.y;
		int direction = d;
		if (d == 0) { cy--; }
		if (d == 90) { cx++; }
		if (d == 180) { cy++; }
		if (d == 270) { cx--; }
		Cell result = get(cx, cy);
		if (result.value == terms.at("outbound_path")) { return empty_cell; }
		return result;
	}
	Cell previous(Cell c, int d) {
		int cx = c.x;
		int cy = c.y;
		int direction = d;
		if (d == 0) { cy++; }
		if (d == 90) { cx--; }
		if (d == 180) { cy--; }
		if (d == 270) { cx++; }
		Cell result = get(cx, cy);
		if (result.value == terms.at("outbound_path")) { return empty_cell; }
		return result;
	}
};

struct Ray {
	int direction;
	Cell start;
	vector<Cell> cells;

	void add(const Cell& cell) {
		cells.push_back(cell);
	}

	bool check_intersection_by(Cell c) {
		for (auto& it : cells) { if (it.x == c.x && it.y == c.y) { return true; } }
		return false;
	}
	bool check_intersection_by(Ray r) {
		for (auto& it2 : r.cells) {
			for (auto& it : cells) { if (it.x == it2.x && it.y == it2.y) { return true; } }
		}
		return false;
	}

	void cast(Matrix& space, int x, int y, int d) { // pew 🔫
		int cx = x;
		int cy = y;
		start = space.get(x, y);
		direction = d;
		Cell current = space.get(cx, cy);
		while (current.value != terms.at("obstruction") && current.value != terms.at("outbound_path")) {
			add(current);
			if (d == 0) { cy--; }
			if (d == 90) { cx++; }
			if (d == 180) { cy++; }
			if (d == 270) { cx--; }
			current = space.get(cx, cy);
		}
	}

	bool cast2(Matrix& space, int x, int y, int d) {
		direction = d;
		int cx = x;
		int cy = y;
		Cell current = start = space.get(x, y);
		while (current.value != terms.at("outbound_path")) {
			if (current.value == terms.at("obstruction")) { return cells.size() == 0 ? false : true; }
			add(current);
			if (d == 0) { cy--; }
			if (d == 90) { cx++; }
			if (d == 180) { cy++; }
			if (d == 270) { cx--; }
			current = space.get(cx, cy);
		}
		return false;
	}
};

Cell checkBound(Matrix& matrix, pair<int, int> p) {
	int x = p.first;
	int y = p.second;

	if (y >= 0 && y < matrix.cells.size() && x >= 0 && x < matrix.cells[0].size()) {
		return matrix.get(x, y);
	}
	return empty_cell;
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

bool bounce_90(Matrix& matrix, Cell point, int d, Cell start) {
	Cell refraction_point = point;
	int direction = d;
	Cell current_point = start;
	if (refraction_point.value == '?' || current_point.value == '?') return false;
	if (start.x == point.x && start.y == point.y) return false;
	char refraction_point_value_original = refraction_point.value;

	//
	matrix.set(refraction_point.x, refraction_point.y, '#');
	map<string, int> obstacles;
	for (auto& r : matrix.cells) {
		for (auto& c : r) {
			if (c.value == '#') {
				string obstacle_key = to_string(c.x) + ":" + to_string(c.y);
				obstacles[obstacle_key] = 0;
			}
		}
	}
	//
	int safe = obstacles.size() * 2;
	while (safe-- > 0) {
		Ray current_ray;
		bool reason = current_ray.cast2(matrix, current_point.x, current_point.y, direction);
		if (!reason) { break; }
		Cell last_ray_point = current_ray.cells.back();
		Cell next = matrix.next(last_ray_point, direction);
		string obstacle_key = to_string(next.x) + ":" + to_string(next.y);
		auto& obstacle = obstacles.at(obstacle_key);
		if (++obstacle > 2) {
			matrix.set(refraction_point.x, refraction_point.y, refraction_point_value_original);
			return true;
		}

		direction = direction + 90 > 270 ? 0 : direction + 90;
		current_point = last_ray_point;
	}
	matrix.set(refraction_point.x, refraction_point.y, refraction_point_value_original);
	return false;
}


tuple<Cell, Matrix, int> init(string filename) {
	int y = 0;
	int direction;
	Matrix matrix;
	Cell start_point = {};
	string line;
	ifstream file(filename);
	while (getline(file, line)) {
		for (size_t x = 0; x < line.size(); x++) {
			for (auto& it : directions) {
				if (line[x] == it.first) {
					start_point = { (int)(x),y,it.first };
					direction = it.second;
				}
			}
			matrix.set(x, y, line[x]);
		}
		++y;
	}
	matrix.set(start_point.x, start_point.y, '.');
	start_point.value = '.';
	file.close();
	return { start_point, matrix, direction };
}


int main() {
	int y = 0;
	int result = 0;
	auto [current_point, matrix, direction] = init("input.txt");
	auto copy_current_point = current_point;
	auto copy_direction = direction;
	vector<Ray> rays;
	bool out_of_map = false;

	while (!out_of_map) {
		Ray current_ray;
		current_ray.cast(matrix, current_point.x, current_point.y, direction);
		rays.push_back(current_ray);

		Cell last_ray_point = current_ray.cells.back();
		vector<vector<Cell>> around = traverse(matrix, matrix.get(last_ray_point.x, last_ray_point.y));

		if (direction == 0) { current_point = around[0][1]; }
		if (direction == 90) { current_point = around[1][2]; }
		if (direction == 180) { current_point = around[2][1]; }
		if (direction == 270) { current_point = around[1][0]; }

		if (current_point.value == '#') {
			if (direction == 0) { current_point = around[1][2]; }
			if (direction == 90) { current_point = around[2][1]; }
			if (direction == 180) { current_point = around[1][0]; }
			if (direction == 270) { current_point = around[0][1]; }
			direction = direction + 90 > 270 ? 0 : direction + 90;
		}

		current_point = last_ray_point;

		if (matrix.next(last_ray_point.x, last_ray_point.y, direction).value == empty_cell.value) {
			out_of_map = true;
			break;
		}
	}

	set<pair<int, int>> unique_pairs;

	for (auto& ray : rays) {
		for (auto& cell : ray.cells) {
			if (cell.x == copy_current_point.x && cell.y == copy_current_point.y) continue;
			bool temp = bounce_90(matrix, cell, copy_direction, copy_current_point);
			if (temp) {
				unique_pairs.emplace(cell.x, cell.y);
				matrix.set(cell.x, cell.y, 'O');
			}
		}
	}

	// for (auto& r : matrix.cells) {
	// 	for (auto& c : r) {
	// 		cout << c.value;
	// 	}
	// 	cout << endl;
	// }
	// cout << endl;

	cout << "result: " << unique_pairs.size()-1 << endl; // 1888

	return 0;
}
