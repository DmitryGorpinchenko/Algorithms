#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void SCCtop5(const vector<vector<int> >& adj, vector<int>* top5);
void DFS(const vector<vector<int> >& adj, vector<int>* post);
void Explore(const vector<vector<int> >& adj, int v, vector<bool>& visited, vector<int>* post, int* scc_size);

int main() {
	ios_base::sync_with_stdio(0);
	int x, y;
	const int n = 875714;
	vector<vector<int> > adj(n, vector<int>());
	while(cin >> x >> y) {
		adj[x - 1].push_back(y - 1);
	}
	vector<int> top5(5, 0);
	SCCtop5(adj, &top5);
	//enter numbers on Coursera in different format !!!!!!!
	for(int size : top5) {
		cout << size << " ";
	}
	cout << endl;
	return 0;
}

void SCCtop5(const vector<vector<int> >& adj, vector<int>* top5) {
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
			int scc_size = 0;
			Explore(adj, post[i], visited, nullptr, &scc_size);
			auto min_ptr = min_element(top5->begin(), top5->end());
			*min_ptr = max(*min_ptr, scc_size);
		}
	}
	sort(top5->begin(), top5->end(), greater<int>());
}

void DFS(const vector<vector<int> >& adj, vector<int>* post) {
	vector<bool> visited(adj.size(), false); 
	for(int i = 0; i < adj.size(); ++i) {
		if(!visited[i]) {
			Explore(adj, i, visited, post, nullptr);
		}
	}
}

void Explore(const vector<vector<int> >& adj, int v, vector<bool>& visited, vector<int>* post, int* scc_size) {
	visited[v] = true;
	if(scc_size != nullptr) {
		++(*scc_size);
	}
	for(int neigh : adj[v]) {
		if(!visited[neigh]) {
			Explore(adj, neigh, visited, post, scc_size);
		}
	}
	if(post != nullptr) {
		post->push_back(v);
	}
}
