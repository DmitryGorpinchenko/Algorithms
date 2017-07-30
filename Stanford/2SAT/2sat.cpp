#include <iostream>
#include <vector>

using namespace std;

struct Clause {
	int var1;
	int var2;
	
	Clause(int var1, int var2) : var1(var1), var2(var2) {} 
};

bool Is2SAT(const vector<Clause>& clauses, int n);
void ConstructGraph(const vector<Clause>& clauses, int n, vector<vector<int> >* adj);
bool SCC(const vector<vector<int> >& adj, int n);
void DFS(const vector<vector<int> >& adj, vector<int>* post);
void Explore(const vector<vector<int> >& adj, int v, vector<int>& labels, vector<int>* post, int label);

int main() {
	ios_base::sync_with_stdio(0);
	int n, v1, v2;
	cin >> n;
	vector<Clause> clauses;
	while(cin >> v1 >> v2) {
		clauses.push_back(Clause(v1, v2));
	}
	cout << Is2SAT(clauses, n) << endl;
	return 0;
}

bool Is2SAT(const vector<Clause>& clauses, int n) {
	vector<vector<int> > adj(2*n, vector<int>());
	ConstructGraph(clauses, n, &adj);
	return SCC(adj, n);
}

void ConstructGraph(const vector<Clause>& clauses, int n, vector<vector<int> >* adj) {
	for(auto& clause : clauses) {
		int u = clause.var1 > 0 ? clause.var1 - 1 : -clause.var1 - 1 + n;
		int v = clause.var2 > 0 ? clause.var2 - 1 : -clause.var2 - 1 + n;
		int not_u = u < n ? u + n : u - n;
		int not_v = v < n ? v + n : v - n;
		(*adj)[not_u].push_back(v);
		(*adj)[not_v].push_back(u);
	}
}

bool SCC(const vector<vector<int> >& adj, int n) {
	vector<vector<int> > rev(adj.size(), vector<int>());
	for(int i = 0; i < adj.size(); ++i) {
		for(int neigh : adj[i]) {
			rev[neigh].push_back(i);
		}
	}
	vector<int> post;
	DFS(rev, &post);
	int scc_num = 1;
	vector<int> components(adj.size(), 0); 
	for(int i = adj.size() - 1; i >= 0; --i) {
		if(!components[post[i]]) {
			Explore(adj, post[i], components, nullptr, scc_num);
			scc_num++;
		}
	}
	for(int i = 0; i < n; ++i) {
		if(components[i] == components[i + n]) {
			return false;	
		}
	}
	return true;
}

void DFS(const vector<vector<int> >& adj, vector<int>* post) {
	vector<int> visited(adj.size(), 0); 
	for(int i = 0; i < adj.size(); ++i) {
		if(!visited[i]) {
			Explore(adj, i, visited, post, 1);
		}
	}
}

void Explore(const vector<vector<int> >& adj, int v, vector<int>& labels, vector<int>* post, int label) {
	labels[v] = label;
	for(int neigh : adj[v]) {
		if(!labels[neigh]) {
			Explore(adj, neigh, labels, post, label);
		}
	}
	if(post != nullptr) {
		post->push_back(v);
	}
}
