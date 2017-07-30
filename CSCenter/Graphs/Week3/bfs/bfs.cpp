#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int distance(const vector<vector<int> >& adj, int s, int t);

int main() {
	ios_base::sync_with_stdio(0);
	int n, m, x, y;
	cin >> n >> m;
	vector<vector<int> > adj(n, vector<int>());
	for(int i = 0; i < m; i++) {
		cin >> x >> y;
		adj[x - 1].push_back(y - 1);
		adj[y - 1].push_back(x - 1);
	}
	int s, t;
	cin >> s >> t;
	--s, --t;
	cout << distance(adj, s, t) << endl;
	return 0;
}

int distance(const vector<vector<int> >& adj, int s, int t) {
  	vector<bool> visited(adj.size(), false); 
  	queue<pair<int, int> > front;
  	front.push(pair<int, int>(s, 0));
  	visited[s] = true;
  	while(!front.empty()) {
  		auto curr = front.front();
  		front.pop();
  		if(curr.first == t) {
  			return curr.second;
  		}
  		for(int neigh : adj[curr.first]) {
  			if(!visited[neigh]) {
  				front.push(pair<int, int>(neigh, curr.second + 1));
  				visited[neigh] = true;
  			}
  		}
  	}
	return -1;
}
