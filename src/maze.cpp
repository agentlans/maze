#include "maze.hpp"

// Initializes a maze with given number of rows and columns
Maze::Maze(int rows, int cols) : rows(rows), cols(cols) {};

// Adds the point to the occupied set in the maze
void Maze::occupy(Point p)
{
	occupied.insert(p);
}

// Adds a connection between two points
void Maze::add_door(Point p1, Point p2)
{
	doors.insert(Door(p1, p2));
	occupied.insert(p1);
	occupied.insert(p2);
}

// Returns pairwise connections between points in the maze
set<Door> Maze::get_doors()
{
	return doors;
}

// Returns true iff a point is in the maze
bool Maze::in_bounds(Point p)
{
	return (0 <= p.first) && (p.first < rows) && (0 <= p.second) && (p.second < cols);
}

// Returns unoccupied points beside the given point
set<Point> Maze::empty_neighbours(Point p)
{
	set<Point> empty_points;
	auto new_point_if_empty = [&](int delta_x, int delta_y) {
		Point new_pt { p.first + delta_x, p.second + delta_y };
		if (in_bounds(new_pt) && (occupied.find(new_pt) == occupied.end())) {
			empty_points.insert(new_pt);
		}
	};
	for (int delta_x : {-1, 1}) {
		new_point_if_empty(delta_x, 0);
	}
	for (int delta_y : {-1, 1}) {
		new_point_if_empty(0, delta_y);
	}
	return empty_points;
}

// Returns occupied points in maze that have unoccupied neighbour
set<Point> Maze::inner_edge()
{
	set<Point> edge;
	for (const auto& p : occupied) {
		if (empty_neighbours(p).size() > 0) {
			edge.insert(p);
		}
	}
	return edge;
}

// True iff there are no more empty points in the maze
bool Maze::full()
{
	return inner_edge().size() == 0;
}

