#include "graph.h"
#include "uf.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>

using namespace std;

int MinCut(const Graph& G);
int Cut(const Graph& G);

int main(int argc, char** argv) {
	ifstream infile(argv[1]);
	int n = atoi(argv[2]);
	Graph G(n);
	string line;
	int v, neigh;
	while(getline(infile, line)) {
		istringstream iss(line);
		iss >> v;
		while(iss >> neigh) {
			G.AddEdge(v - 1, neigh - 1);
		}
	}
	cout << MinCut(G) << endl;
}

int MinCut(const Graph& G) {
	int T = static_cast<int>(G.nodes_num() * G.nodes_num() * log(G.nodes_num()));
	int min = G.edges_num();
	for(int i = 0; i < T; i++) {
		int curr = Cut(G);
		if(min > curr) {
			min = curr;
		}
		G.reset();
	}
	return min;
}

int Cut(const Graph& G) {
	UF uf(G.nodes_num());
	while(uf.cc_num() > 2) {
		auto& edge = G.RemoveRandomEdge();
		uf.Union(edge.first, edge.second);
	}
	int cut_size = 0;
	for(auto& e : G.GetEdges()) {
		if(!uf.IsConnected(e.first, e.second)) {
			++cut_size;
		}
	}
	return cut_size;
}
