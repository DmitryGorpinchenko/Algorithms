#ifndef Graph_H
#define Graph_H

#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Graph {
public:
	explicit Graph(int n) : nodes_num_(n), edges_num_(0) {
		srand(time(NULL));
	}

	void AddEdge(int i, int j);
	const pair<int, int>& RemoveRandomEdge() const;
	
	const vector<pair<int, int> >& GetEdges() const {
		return edges_;
	}
	
	int edges_num() const {
		return edges_.size(); 
	}
	
	int nodes_num() const {
		return nodes_num_; 
	}
	
	void reset() const {
		edges_num_ = edges_.size();
	}
	
private:
	mutable vector<pair<int, int> > edges_;
	int nodes_num_;
	mutable int edges_num_;
};

#endif
