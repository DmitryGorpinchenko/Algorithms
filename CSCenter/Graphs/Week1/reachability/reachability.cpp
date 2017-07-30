#include <iostream>
#include <vector>
#include <stack>

using namespace std;

bool IsReachable(const vector<vector<int> >& adj, int goal, int src);

int main() {
	ios_base::sync_with_stdio(0);
	int n, m, u, v;
	cin >> n >> m;
	vector<vector<int> > adj(n, vector<int>());
	for (int i = 0; i < m; ++i) {
		cin >> u >> v;
		adj[u - 1].push_back(v - 1);
		adj[v - 1].push_back(u - 1);
	}
	cin >> u >> v;
	cout << IsReachable(adj, v - 1, u - 1) << endl;
	return 0;
}

bool IsReachable(const vector<vector<int> >& adj, int goal, int src) {
	vector<bool> visited(adj.size(), false);
	stack<int> front;
	front.push(src);
	visited[src] = true;
	while(!front.empty()) {
		int curr = front.top();
		front.pop();
		if(curr == goal) {
			return true;
		}
		for(int neigh : adj[curr]) {
			if(!visited[neigh]) {
				front.push(neigh);
				visited[neigh] = true;
			}
		}
	}
	return false;
}
