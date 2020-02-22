#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <string>
#include <set>

#include "bfs.hpp"

using namespace std;

typedef pair<int,int> Point;
typedef pair<Point,Point> Door;

// This maze is different from the class we used to generate the maze
class Maze
{
public:
	// Loads maze from file as a set of doors
	void load(string filename)
	{
		ifstream fin;
		fin.open(filename);
		string line;
		while (getline(fin, line)) {
			vector<int> vec;
			istringstream iss(line);
			for (int i = 0; i < 4; ++i) {
				double x;
				iss >> x;
				vec.push_back(x);
			}
			doors.insert({{vec[0], vec[1]}, {vec[2], vec[3]}});
			min_row = min(min(vec[0], vec[2]), min_row);
			max_row = max(max(vec[0], vec[2]), max_row);
			min_col = min(min(vec[1], vec[3]), min_col);
			max_col = max(max(vec[1], vec[3]), max_col);
		}
		fin.close();
	}
	bool is_valid(Point p) {
		return (min_row <= p.first) && (p.first <= max_row) &&
			(min_col <= p.second) && (p.second <= max_col);
	}
	// Returns the points accessible from a given point
	vector<Point> neighbours(Point p)
	{
		set<Point> ps;
		for (const auto &d : doors) {
			if (d.first == p) {
				ps.insert(d.second);
			} else if (d.second == p) {
				ps.insert(d.first);
			}
		}
		vector<Point> pv(ps.begin(), ps.end());
		return pv;
	}
	int get_min_row() { return min_row; }
	int get_max_row() { return max_row; }
	int get_min_col() { return min_col; }
	int get_max_col() { return max_col; }
private:
	set<Door> doors;
	int min_row = std::numeric_limits<int>::max();
	int max_row = std::numeric_limits<int>::min();
	int min_col = std::numeric_limits<int>::max();
	int max_col = std::numeric_limits<int>::min();
};



int main(int argc, char** argv)
{
	Maze m;
	string filename;
	if (argc < 2 || argc > 6) {
		cout << "Usage: solve maze_file [start_point_row start_point_col end_point_row end_point_col]" << endl;
		return 1;
	}
	// Load maze data from file
	filename = argv[1];
	m.load(filename);
	
	int start_r = m.get_min_row();
	int start_c = m.get_min_col();
	int end_r = m.get_max_row();
	int end_c = m.get_max_col();

	if (argc == 6) {
		start_r = stoi(argv[2]);
		start_c = stoi(argv[3]);
		end_r = stoi(argv[4]);
		end_c = stoi(argv[5]);
		if (!m.is_valid(Point(start_r, start_c)) || !m.is_valid(Point(end_r, end_c))) {
			cout << "The given start and end points aren't in the maze." << endl;
			return 1;
		}
	} else if (argc != 2) {
		cout << "Must provide coordinates of start and end points." << endl;
		return 1;
	}

	// Returns the neighbours of a point in the maze
	auto neighbours = [&](Point p) {
		return m.neighbours(p);
	};

	// Do breadth first search
	BreadthFirstSearch<Point> bfs(Point(start_r,start_c), neighbours);
	Point goal {end_r, end_c};

	while (!bfs.empty()) {
		if (bfs.current() == goal) {
			// Print the path once we've reached the goal
			auto solution = bfs.path();
			for (const auto& x : solution) {
				cout << x.first << "\t" << x.second << endl;
			}
			return 0;
		}
		bfs.next();
	}
	cout << "No solution found." << endl;
	return 1;
}

