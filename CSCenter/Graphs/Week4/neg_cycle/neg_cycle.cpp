#include <iostream>
#include <vector>
#include <climits>

using namespace std;

bool HasNegCycle(vector<vector<pair<int, int> > > &adj);

int main() {
	ios_base::sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	vector<vector<pair<int, int> > > adj(n, vector<pair<int, int> >());
	for (int i = 0; i < m; i++) {
		int x, y, w;
		cin >> x >> y >> w;
		adj[x - 1].push_back(pair<int, int>(y - 1, w));
	}
	cout << HasNegCycle(adj) << endl;
}

bool HasNegCycle(vector<vector<pair<int, int> > > &adj) {
	vector<long long> dist(adj.size(), LLONG_MAX);
	dist[0] = 0; //assume 0 as a starting vertex
	for(int i = 0; i < adj.size() - 1; ++i) {
		for(int j = 0; j < adj.size(); ++j) {
			for(auto& e : adj[j]) {
				if(dist[e.first] > dist[j] + e.second) {
					dist[e.first] = dist[j] + e.second;
				}
			}
		}
	}
	//last iteration to detect a negative cycle if any
	for(int j = 0; j < adj.size(); ++j) {
		for(auto& e : adj[j]) {
			if(dist[e.first] > dist[j] + e.second) {
				return true;
			}
		}
	}
	return false;
}
