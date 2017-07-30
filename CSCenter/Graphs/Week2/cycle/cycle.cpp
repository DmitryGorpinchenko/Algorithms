#include <iostream>
#include <vector>

using namespace std;

bool HasCycle(const vector<vector<int> >& adj);
void Explore(const vector<vector<int> >& adj, int v, int& clock, vector<bool>& visited, vector<int>& post);

int main() {
  ios_base::sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; ++i) {
    int x, y;
    cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  cout << HasCycle(adj) << endl;
  return 0;
}

bool HasCycle(const vector<vector<int> >& adj) {
	vector<bool> visited(adj.size(), false);
	vector<int> post(adj.size(), 0);
	int clock = 0;
	for(int i = 0; i < adj.size(); ++i) {
		if(!visited[i]) {
			Explore(adj, i, clock, visited, post);
		}
	}
	for(int i = 0; i < adj.size(); ++i) {
		for(int neigh : adj[i]) {
			if(post[i] < post[neigh]) {
				return true;
			}
		}
	}
	return false;
}

void Explore(const vector<vector<int> >& adj, int v, int& clock, vector<bool>& visited, vector<int>& post) {
	visited[v] = true;
	for(int neigh : adj[v]) {
		if(!visited[neigh]) {
			Explore(adj, neigh, clock, visited, post);
		}
	}
	post[v] = clock++;
}
