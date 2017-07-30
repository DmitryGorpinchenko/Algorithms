#include <iostream>
#include <vector>

using namespace std;

int SCCNum(const vector<vector<int> >& adj);
void DFS(const vector<vector<int> >& adj, vector<int>* post);
void Explore(const vector<vector<int> >& adj, int v, vector<bool>& visited, vector<int>* post);

int main() {
	ios_base::sync_with_stdio(0);
	int n, m, x, y;
	cin >> n >> m;
	vector<vector<int> > adj(n, vector<int>());
	for (int i = 0; i < m; ++i) {
		cin >> x >> y;
		adj[x - 1].push_back(y - 1);
	}
	cout << SCCNum(adj) << endl;
	return 0;
}

int SCCNum(const vector<vector<int> >& adj) {
	int result = 0;
	//reverse the input graph
	vector<vector<int> > rev(adj.size(), vector<int>());
	for(int i = 0; i < adj.size(); ++i) {
		for(int neigh : adj[i]) {
			rev[neigh].push_back(i);
		}
	}
	//run dfs on the reverse graph
	vector<int> post;
	DFS(rev, &post);
	//compute the number of SCCs
	vector<bool> visited(adj.size(), false); 
	for(int i = adj.size() - 1; i >= 0; --i) {
		if(!visited[post[i]]) {
			Explore(adj, post[i], visited, nullptr);
			++result;
		}
	}
	return result;
}

void DFS(const vector<vector<int> >& adj, vector<int>* post) {
	vector<bool> visited(adj.size(), false); 
	for(int i = 0; i < adj.size(); ++i) {
		if(!visited[i]) {
			Explore(adj, i, visited, post);
		}
	}
}

void Explore(const vector<vector<int> >& adj, int v, vector<bool>& visited, vector<int>* post) {
	visited[v] = true;
	for(int neigh : adj[v]) {
		if(!visited[neigh]) {
			Explore(adj, neigh, visited, post);
		}
	}
	if(post != nullptr) {
		post->push_back(v);
	}
}
