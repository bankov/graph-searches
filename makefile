all: graph

graph: graph.cc
	g++ -o graph -g -std=c++11 -O3 graph.cc
