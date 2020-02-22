#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <chrono>
#include <cassert>

#include "maze.hpp"

using namespace std;

default_random_engine gen;
uniform_real_distribution<float> distribution(0, 1);

// Returns a random element from the given set
template <class T>
T choose_random(const set<T>& s)
{
	auto v = vector<T>(s.begin(), s.end());
	return v[int(distribution(gen) * s.size())];
}

// Generates a random maze
Maze generate_maze(int rows, int cols)
{
	Maze m(rows, cols);
	m.occupy(Point(0, 0)); // Start at (0, 0)
	while (!m.full()) {
		Point p = choose_random<Point>(m.inner_edge());
		auto p2 = choose_random<Point>(m.empty_neighbours(p));
		m.add_door(p, p2);
	}
	return m;
}

int main(int argc, char** argv)
{
	int row, col;
	unsigned seed;
	try {
		row = std::stoi(argv[1]);
		col = std::stoi(argv[2]);
		assert(row > 0 && col > 0);
		if (argc > 3) {
			seed = std::stoi(argv[3]);
		} else {
			// Default seed is from system clock
			seed = std::chrono::system_clock::now().time_since_epoch().count();
		}
		gen = default_random_engine(seed);
	} catch (...) {
		std::cout << "Usage: generate num_rows num_columns [random_seed]\nRows and columns must be > 0" << std::endl;
		return 1;
	}
	Maze m = generate_maze(row, col);
	
	// Print the connections between points in the maze
	for (const auto& door : m.get_doors()) {
		Point p1 = door.first, p2 = door.second;
		std::cout << p1.first << "\t" << p1.second << 
			"\t" << p2.first << "\t" << p2.second << std::endl;
	}
	return 0;
}

