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
#include <deque>
#include <array>

struct Cell {
	int x, y;
	char value;
};

struct Matrix {
	std::vector<std::vector<Cell>> cells;

	// Default constructor
	Matrix() = default;

	// Set a cell value
	void set(int y, int x, char value) {
		while (cells.size() <= y) {
			cells.push_back(std::vector<Cell> {});
		}


		while (cells[y].size() <= x) {
			cells[y].push_back(Cell{ -1, -1, '?' });
		}

		cells[y][x] = Cell{ x,y,value };
	}

	// Get a cell value
	Cell get(int x, int y) {
		if (y < cells.size() && x < cells[y].size()) {
			return cells[y][x];
		}
		return Cell{ -1, -1, '\0' }; // Return an empty cell if out of bounds
	}

	// Remove a cell
	bool erase(int x, int y) {
		if (y < cells.size() && x < cells[y].size()) {
			cells[y][x] = Cell{ -1, -1, '?' }; // Empty cell
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
	std::string direction;

	std::vector<Cell> cells;

	void add(const Cell& cell) {
		cells.push_back(cell);
	}
};


Cell checkBound(Matrix& matrix, std::pair<int, int> p) {
	int x = p.first;
	int y = p.second;

	if (y >= 0 && y < matrix.cells.size() && x >= 0 && x < matrix.cells[0].size()) {
		return matrix.get(x, y);
	}
	return Cell{ -1, -1, '?' };
}

std::vector<std::vector<Cell>> traverse(Matrix& matrix, Cell cell) {
	int x = cell.x;
	int y = cell.y;

	auto pcb = [&matrix](std::pair<int, int> p) { return checkBound(matrix, p); };


	std::vector<Cell> top = { pcb({x - 1, y - 1}), pcb({x + 0, y - 1}), pcb({x + 1, y - 1}) };
	std::vector<Cell> mid = { pcb({x - 1, y + 0}), pcb({x + 0, y + 0}), pcb({x + 1, y + 0}) };
	std::vector<Cell> bot = { pcb({x - 1, y + 1}), pcb({x + 0, y + 1}), pcb({x + 1, y + 1}) };
	std::vector<std::vector<Cell>> result = {
		top, mid, bot
	};

	return result;
}


int main() {

	std::ifstream file("input.txt");
	Matrix matrix;
	std::string line;
	int y = 0;

	while (std::getline(file, line)) {
		for (size_t x = 0; x < line.size(); ++x) {
			matrix.set(y, static_cast<int>(x), line[x]);
		}
		++y;
	}

	file.close();

	std::deque<Cell> points;

	for (const auto& row : matrix.cells) {
		for (const auto& cell : row) {
			if (cell.value == 'X') {
				points.push_back(cell);
			}
		}
	}
	// std::cout << "found X:" << points.size() << "\n";

	std::vector<Sequence> finally_found;

	std::vector<char> search_sequence = { 'M', 'A', 'S' };

	std::vector<Sequence> sequences(points.size());

	// init
	for (auto& sequence : sequences) {
		if (!points.empty()) {
			sequence.add(points.front());
			points.pop_front();
		}
	}

	std::cout << "create sequences: " << sequences.size() << "\n";

	while (sequences.size() > 0) {
		Sequence sequence = sequences.back();
		sequences.pop_back();

		if (sequence.cells.size() == 4) {
			finally_found.push_back(sequence);

			sequences.erase(
				std::remove_if(sequences.begin(), sequences.end(),
					[&sequence](const Sequence& seq) {
						return
							seq.direction == sequence.direction &&
							seq.cells[0].x == sequence.cells[0].x &&
							seq.cells[0].y == sequence.cells[0].y;
					}),
				sequences.end());
			continue;
		}

		for (int i = 0; i < sequence.cells.size(); ++i) {
			std::cout << "sequence " << sequence.cells[i].y << " " << sequence.cells[i].x << "\n";

			// get candidate

			std::vector<std::vector<Cell>> value = traverse(matrix, sequence.cells[i]);


			// perform traverse

			std::vector top = value[0];
			std::vector mid = value[1];
			std::vector bot = value[2];

			// start search from top left
			int size = sequence.cells.size();
			char next = search_sequence[size - 1];

			// fork current
			for (size_t i = 0; i < top.size(); i++) {
				std::cout << top[i].value << "";

				if (i == 0 && top[i].value == next) {
					Sequence copy = sequence;
					std::string direction = "top-left";
					if (copy.direction.empty()) {
						copy.direction = direction;
						copy.cells.push_back(top[i]);
						sequences.push_back(copy);
					}
					else if (!copy.direction.empty() && copy.direction == direction) {
						copy.cells.push_back(top[i]);
						sequences.push_back(copy);
					}
				}
				if (i == 1 && top[i].value == next) {
					Sequence copy = sequence;
					std::string direction = "top";
					if (copy.direction.empty()) {
						copy.direction = direction;
						copy.cells.push_back(top[i]);
						sequences.push_back(copy);
					}
					else if (!copy.direction.empty() && copy.direction == direction) {
						copy.cells.push_back(top[i]);
						sequences.push_back(copy);
					}
				}
				if (i == 2 && top[i].value == next) {
					Sequence copy = sequence;
					std::string direction = "top-right";
					if (copy.direction.empty()) {
						copy.direction = direction;
						copy.cells.push_back(top[i]);
						sequences.push_back(copy);
					}
					else if (!copy.direction.empty() && copy.direction == direction) {
						copy.cells.push_back(top[i]);
						sequences.push_back(copy);
					}
				}
			}

			for (size_t i = 0; i < mid.size(); i++) {

				if (i == 0 && mid[i].value == next) {
					Sequence copy = sequence;
					std::string direction = "left";
					if (copy.direction.empty()) {
						copy.direction = direction;
						copy.cells.push_back(mid[i]);
						sequences.push_back(copy);
					}
					else if (!copy.direction.empty() && copy.direction == direction) {
						copy.cells.push_back(mid[i]);
						sequences.push_back(copy);
					}
				}
				if (i == 1 && mid[i].value == next) {
					// ignore it
					continue;
				}
				if (i == 2 && mid[i].value == next) {
					Sequence copy = sequence;
					std::string direction = "right";
					if (copy.direction.empty()) {
						copy.direction = direction;
						copy.cells.push_back(mid[i]);
						sequences.push_back(copy);
					}
					else if (!copy.direction.empty() && copy.direction == direction) {
						copy.cells.push_back(mid[i]);
						sequences.push_back(copy);
					}
				}


			}

			for (size_t i = 0; i < bot.size(); i++) {
				if (i == 0 && bot[i].value == next) {
					Sequence copy = sequence;
					std::string direction = "bot-left";
					if (copy.direction.empty()) {
						copy.direction = direction;
						copy.cells.push_back(bot[i]);
						sequences.push_back(copy);
					}
					else if (!copy.direction.empty() && copy.direction == direction) {
						copy.cells.push_back(bot[i]);
						sequences.push_back(copy);
					}
				}
				if (i == 1 && bot[i].value == next) {
					Sequence copy = sequence;
					std::string direction = "bot";
					if (copy.direction.empty()) {
						copy.direction = direction;
						copy.cells.push_back(bot[i]);
						sequences.push_back(copy);
					}
					else if (!copy.direction.empty() && copy.direction == direction) {
						copy.cells.push_back(bot[i]);
						sequences.push_back(copy);
					}
				}
				if (i == 2 && bot[i].value == next) {
					Sequence copy = sequence;
					std::string direction = "bot-right";
					if (copy.direction.empty()) {
						copy.direction = direction;
						copy.cells.push_back(bot[i]);
						sequences.push_back(copy);
					}
					else if (!copy.direction.empty() && copy.direction == direction) {
						copy.cells.push_back(bot[i]);
						sequences.push_back(copy);
					}
				}
			}

			//
			std::cout << "current size of sequences: " << sequences.size() << std::endl;

		}
	}

	std::cout << "finally found sequences: " << finally_found.size() << std::endl;

	// for (auto& sequence : finally_found) {
	// 	std::cout
	// 		<< "sequences: "
	// 		<< sequence.cells[0].value
	// 		<< ""
	// 		<< sequence.cells[1].value
	// 		<< ""
	// 		<< sequence.cells[2].value
	// 		<< ""
	// 		<< sequence.cells[3].value
	// 		<< std::endl;
	// }

	return 0;
}
