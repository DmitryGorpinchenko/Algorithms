#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cfloat>

using namespace std;

void OptExch(vector<vector<pair<int, double> > > &adj, int s, vector<double>* dist);
void PrintDist(const vector<double>& dist);

int main() {
	ios_base::sync_with_stdio(0);
	int n, m, s;
	cin >> n >> m;
	vector<vector<pair<int, double> > > adj(n, vector<pair<int, double> >());
	for (int i = 0; i < m; i++) {
		int x, y;
		double w;
		cin >> x >> y >> w;
		adj[x - 1].push_back(pair<int, double>(y - 1, w));
	}
	cin >> s;
	--s;
	vector<double> dist;
	OptExch(adj, s, &dist);
	PrintDist(dist);
}

void OptExch(vector<vector<pair<int, double> > > &adj, int s, vector<double>* dist) {
	dist->resize(adj.size(), DBL_MAX);
	(*dist)[s] = 0;
	for(int i = 0; i < adj.size() - 1; ++i) {
		for(int j = 0; j < adj.size(); ++j) {
			for(auto& e : adj[j]) {
				if((*dist)[e.first] > (*dist)[j] + e.second) {
					(*dist)[e.first] = (*dist)[j] + e.second;
				}
			}
		}
	}
	queue<int> relaxed;
	vector<bool> visited(adj.size(), false);
	for(int j = 0; j < adj.size(); ++j) {
		for(auto& e : adj[j]) {
			if((*dist)[e.first] > (*dist)[j] + e.second) {
				relaxed.push(e.first);
				visited[e.first] = true;
			}
		}
	}
	while(!relaxed.empty()) {
		int curr = relaxed.front();
		relaxed.pop();
		for(auto& e : adj[curr]) {
			if(!visited[e.first]) {
				relaxed.push(e.first);
				visited[e.first] = true;
			}
		}
	}
	for(int i = 0; i < adj.size(); ++i) {
		if(visited[i]) {
			(*dist)[i] = DBL_MIN;
		}
	}
}

void PrintDist(const vector<double>& dist) {
	for(auto d : dist) {
		if(d == DBL_MAX) {
			cout << '*' << endl;
		} else if(d == DBL_MIN) {
			cout << '-' << endl;
		} else {
			cout << static_cast<long long>(d) << endl;
		}
	}
}
