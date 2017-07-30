#include "graph.h"
#include <cstdlib>

using namespace std;

void Graph::AddEdge(int i, int j) {
	if(i < j) {
		edges_.push_back(pair<int, int>(i, j));
		++edges_num_;
	}
}

const pair<int, int>& Graph::RemoveRandomEdge() const {
	int victim = rand() % edges_num_;
	auto tmp = edges_[victim];
	edges_[victim] = edges_[edges_num_ - 1];
	edges_[edges_num_ - 1] = tmp;
	return edges_[(edges_num_--) - 1];
}
