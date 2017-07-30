#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool IsBipartite(const vector<vector<int> >& adj);
void BFS(const vector<vector<int> >& adj, int s, vector<short>& colors);

int main() {
	ios_base::sync_with_stdio(0);
	int n, m, x, y;
	cin >> n >> m;
	vector<vector<int> > adj(n, vector<int>());
	for(int i = 0; i < m; ++i) {
		cin >> x >> y;
		adj[x - 1].push_back(y - 1);
		adj[y - 1].push_back(x - 1);
	}
	cout << IsBipartite(adj) << endl;
	return 0;
}

bool IsBipartite(const vector<vector<int> >& adj) {
	//color all vertices
	vector<short> colors(adj.size(), -1);
	for(int i = 0; i < adj.size(); ++i) {
		if(colors[i] == -1) {
			BFS(adj, i, colors);
		}
	}
	//check for proper coloring
	for(int i = 0; i < adj.size(); ++i) {
		for(int neigh : adj[i]) {
			if(colors[i] == colors[neigh]) {
				return false;
			}
		}
	}
	return true;
}

void BFS(const vector<vector<int> >& adj, int s, vector<short>& colors) {
	queue<int> front;
	front.push(s);
	colors[s] = 0;
	while(!front.empty()) {
		int curr = front.front();
		front.pop();
		for(int neigh : adj[curr]) {
			if(colors[neigh] == -1) {
				front.push(neigh);
				colors[neigh] = !colors[curr];
			}
		}
	}
}
