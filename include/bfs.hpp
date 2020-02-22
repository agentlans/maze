#ifndef _BFS
#define _BFS

#include <memory>
#include <queue>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <functional>

using namespace std;

template <class T>
class BreadthFirstSearch
{
public:
	BreadthFirstSearch(T start_vertex, function<vector<T>(T)> neighbour_func);
	void next();
	T current();
	vector<T> path();
	bool empty();
private:
	T start;
	function<vector<T>(T)> neighbours;
	queue<T> q;
	map<T,T> parent;
	set<T> discovered;
};


// Constructor
template <class T>
BreadthFirstSearch<T>::BreadthFirstSearch(T start_vertex, 
		function<vector<T>(T)> neighbour_func) : 
	start(start_vertex), neighbours(neighbour_func)
{
	q.push(start_vertex);
	discovered.insert(start_vertex);
};

// Returns current vertex in the queue
template <class T>
T BreadthFirstSearch<T>::current()
{
	return q.front();
}

// Moves on to next vertex in the search
template <class T>
void BreadthFirstSearch<T>::next()
{
	if (q.empty()) {
		throw "Underflow.";
	}
	auto v = q.front();
	q.pop();
	for (const auto& w : neighbours(v)) {
		// Haven't been discovered
		if (discovered.find(w) == discovered.end()) {
			discovered.insert(w);
			parent[w] = v;
			q.push(w);
		}
	}
}

// Returns true iff there are no more elements left in queue
template <class T>
bool BreadthFirstSearch<T>::empty()
{
	return q.empty();
}

// Returns a path from start to the current vertex
template <class T>
vector<T> BreadthFirstSearch<T>::path()
{
	vector<T> p;
	auto v = q.front();
	p.push_back(v);
	// Backtrack through a vertex's parent
	while (parent.find(v) != parent.end()) {
		auto vp = parent[v];
		p.push_back(vp);
		v = vp;
	}
	reverse(p.begin(), p.end());
	return p;
}

#endif

