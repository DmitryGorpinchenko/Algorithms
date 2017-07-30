#include <iostream>
#include <vector>

using namespace std;

int CCNum(const vector<vector<int> >& adj);
void Explore(const vector<vector<int> >& adj, int v, vector<bool>& visited);

int main() {
	ios_base::sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	vector<vector<int> > adj(n, vector<int>());
	for (int i = 0; i < m; ++i) {
		int x, y;
		cin >> x >> y;
		adj[x - 1].push_back(y - 1);
		adj[y - 1].push_back(x - 1);
	}
	cout << CCNum(adj) << endl;
	return 0;
}

int CCNum(const vector<vector<int> >& adj) {
	int res = 0;
	vector<bool> visited(adj.size(), false);
	for(int i = 0; i < adj.size(); ++i) {
		if(!visited[i]) {
			Explore(adj, i, visited);
			++res;
		}
	}
	return res;
}

void Explore(const vector<vector<int> >& adj, int v, vector<bool>& visited) {
	visited[v] = true;
	for(int neigh : adj[v]) {
		if(!visited[neigh]) {
			Explore(adj, neigh, visited);
		}	
	}
}
