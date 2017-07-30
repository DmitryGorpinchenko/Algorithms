#include <iostream>
#include <vector>
#include <cfloat>
#include <algorithm>

using namespace std;

struct Edge {
	Edge(int u, int v, int w) : u(u), v(v), w(w) {}
	int u, v, w;
};

bool APSP(const vector<Edge>& edges, int n, double* ssp_len);

int main() {
	int n, m, u, v, w;
	cin >> n >> m;
	vector<Edge> edges;
	for(int i = 0; i < m; ++i) {
		cin >> u >> v >> w;
		edges.push_back(Edge(u - 1, v - 1, w)); 
	}
	double ssp_len;
	if(APSP(edges, n, &ssp_len)) {
		cout << ssp_len << endl;
	} else {
		cout << "NULL" << endl;
	}
	return 0;
}

bool APSP(const vector<Edge>& edges, int n, double* ssp_len) {
	double* curr = new double[n * n];
	fill_n(curr, n * n, DBL_MAX);
	for(int i = 0; i < n; ++i) {
		curr[i * n + i] = 0;
	}
	for(auto& e : edges) {
		curr[e.u * n + e.v] = e.w;
	}
	double* next = new double[n * n];
	for(int k = 0; k < n; ++k) {
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j) {
				next[i * n + j] = min(curr[i * n + j], curr[i * n + k] + curr[k * n + j]);
			}
		}
		swap(curr, next);
	}
	for(int i = 0; i < n; ++i) {
		if(curr[i * n + i] < 0) {
			return false;
		}
	}
	*ssp_len = *min_element(curr, curr + n * n);
	delete [] curr;
	delete [] next; 
	return true;
}
