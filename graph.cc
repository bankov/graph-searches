#include <algorithm>
#include <iostream>
#include <list>
#include <queue>
#include <vector>

struct Vertex {
	int val;

	Vertex(int v = 0) : val(v) {};
	std::list<Vertex *> neighbours;
	void add_neighbour(Vertex *);
};

void Vertex::add_neighbour(Vertex *v) {
	if (std::find(neighbours.begin(), neighbours.end(), v) == neighbours.end())
		neighbours.push_back(v);
}

class Graph {
	std::vector<Vertex> vertices;
	bool dfs_helper(Vertex *, Vertex *, void (*f)(Vertex *), std::list<Vertex *> &);
	Vertex *root;
public:
	Graph() : root(NULL) {};
	Graph(int, int *, int*);	//Init the graph by a vector of values and an adjacency matrix
	Vertex *get_vertex(int);
	Vertex *get_root() { return root; }
	bool dfs(Vertex *, Vertex *, void (*f)(Vertex *));
	bool bfs(Vertex *, Vertex *, void (*f)(Vertex *));
};

Graph::Graph(int n, int *values, int *adjacency) {
	vertices = std::vector<Vertex>(n);
	for(int i = 0; i < n; i++) {
		vertices[i].val = values[i];
	}

	for(int i = 0; i < n; i++)
		for(int j = i; j < n; j++) {
			if(adjacency[i * n + j]) {
				vertices[i].add_neighbour(&vertices[j]);
				vertices[j].add_neighbour(&vertices[i]);
			}
		}

	root = &vertices[0];
}
Vertex *Graph::get_vertex(int n) {
	if(n > 0 && n < vertices.size())
		return &vertices[n];
	else
		return NULL;
}

void func(Vertex *v) {
	std::cout << "I'm in " << v->val << std::endl;
}

bool Graph::dfs(Vertex *start, Vertex *goal, void (*f)(Vertex *)) {
	std::list<Vertex *> visited;
	return dfs_helper(start, goal, f, visited);
}
bool Graph::dfs_helper(Vertex *v, Vertex *goal, void (*f)(Vertex *), std::list<Vertex *> &visits) {
	f(v);
	if(v == goal)
		return true;

	visits.push_back(v);

	for(auto it = v->neighbours.begin(); it != v->neighbours.end(); ++it) {
		Vertex *p = *it;
		if (std::find(visits.begin(), visits.end(), p) == visits.end())
			if(dfs_helper(p, goal, f, visits))
				return true;
	}
	return false;
}
bool Graph::bfs(Vertex *start, Vertex *goal, void (*f)(Vertex *)) {
	std::queue<Vertex *> buf;
	std::list<Vertex *> visited;
	buf.push(start);

	while(!buf.empty()) {
		Vertex *v = buf.front();
		buf.pop();
		f(v);
		if(v == goal)
			return true;
		visited.push_back(v);	
		for(auto it = v->neighbours.begin(); it != v->neighbours.end(); ++it) {
			Vertex *p = *it;
			if (std::find(visited.begin(), visited.end(), p) == visited.end())
				buf.push(p);
		}
	}
	return false;
}
int main() {
	int vals[] = {1, 2, 3, 4, 5, 6};
	int matrix[] = {
		1,1,1,0,0,0,
		1,0,0,1,1,0,
		1,0,0,0,0,1,
		0,1,0,0,0,0,
		0,1,0,0,0,0,
		0,0,1,0,0,0
	};
	Graph g(6, vals, matrix);

	Vertex *from = g.get_root();
	Vertex *to1 = g.get_vertex(4);
	Vertex tmp(10);
	Vertex *to2 = &tmp;
	std::cout << "DFS, searching for vertex: " << to1->val << "\n";
	if(g.dfs(from, to1, func))
		std::cout << "Found it\n";
	else
		std::cout << "Haven't found it\n";

	std::cout << "DFS, searching for vertex: " << to2->val << "\n";
	if(g.dfs(from, to2, func))
		std::cout << "Found it\n";
	else
		std::cout << "Haven't found it\n";

	std::cout << "BFS, searching for vertex: " << to1->val << "\n";
	if(g.bfs(from, to1, func))
		std::cout << "Found it\n";
	else
		std::cout << "Haven't found it\n";

	std::cout << "BFS, searching for vertex: " << to2->val << "\n";
	if(g.bfs(from, to2, func))
		std::cout << "Found it\n";
	else
		std::cout << "Haven't found it\n";

}
