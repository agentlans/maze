#ifndef _MAZE
#define _MAZE

#include <set>
#include <vector>

using namespace std;

typedef pair<int,int> Point;
typedef pair<Point,Point> Door;

class Maze
{
public:
	Maze(int rows, int cols); // Initializes maze with given number of rows and columns
	void occupy(Point p); // Adds point to maze
	void add_door(Point p1, Point p2); // Adds connection between two points
	set<Point> empty_neighbours(Point p); // Returns unoccupied neighbours of a point
	set<Point> inner_edge(); // Points inside the maze that have empty neighbour
	set<Door> get_doors(); // The connections between occupied points in maze
	bool full(); // true iff all points in maze are occupied
private:
	bool in_bounds(Point p);
	set<Point> occupied;

	set<Door> doors;
	int rows, cols;
	Point start;
};

#endif

