#include <iostream>
#include <vector>
#include <queue>
#include <sstream>

using namespace std;

void SPaths(const vector<vector<pair<int, int> > >& adj, int s, vector<int>* dist);

int main() {
	ios_base::sync_with_stdio(0);
	vector<vector<pair<int, int> > > adj;
	string line;
	while(getline(cin, line)) {
		int v, u, w;
		stringstream ss(line);
		ss >> v;
		adj.push_back(vector<pair<int, int> >());
		while(ss >> u >> w) {
			adj[v - 1].push_back(pair<int, int>(u - 1, w));
		}
	}
	vector<int> dist(adj.size(), 1000000);
	vector<int> targets = {7,37,59,82,99,115,133,165,188,197};
	SPaths(adj, 0, &dist);
	for(auto t : targets) {
		cout << dist[t - 1] << " ";
	}
	cout << endl;
}

void SPaths(const vector<vector<pair<int, int> > >& adj, int s, vector<int>* dist) {
	//'first' in pair is a distance and 'second' is the corresponding vertex
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
	pq.push(pair<int, int>(0, s));
	(*dist)[s] = 0;
	while(!pq.empty()) {
		auto curr = pq.top();
		pq.pop();
		for(auto& neigh : adj[curr.second]) {
			if((*dist)[neigh.first] > curr.first + neigh.second) {
				(*dist)[neigh.first] = curr.first + neigh.second;
				pq.push(pair<int, int>((*dist)[neigh.first], neigh.first));
			}
		}
	}
}
