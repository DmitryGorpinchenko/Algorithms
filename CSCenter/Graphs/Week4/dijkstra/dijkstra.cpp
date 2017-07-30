#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

int distance(vector<vector<pair<int, int> > > &adj, int s, int t);

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
	int s, t;
	cin >> s >> t;
	--s, --t;
	cout << distance(adj, s, t) << endl;
}

int distance(vector<vector<pair<int, int> > > &adj, int s, int t) {
	//'first' in pair is a distance and 'second' is the corresponding vertex
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
	vector<int> dist(adj.size(), INT_MAX);
	pq.push(pair<int, int>(0, s));
	dist[s] = 0;
	while(!pq.empty()) {
		pair<int, int> curr = pq.top();
		pq.pop();
		if(curr.second == t) {
			return curr.first;
		}
		for(auto& neigh : adj[curr.second]) {
			if(dist[neigh.first] > curr.first + neigh.second) {
				dist[neigh.first] = curr.first + neigh.second;
				pq.push(pair<int, int>(dist[neigh.first], neigh.first));
			}
		}
	}
	return -1;
}
