#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <cfloat>

using namespace std;

struct Edge {
	Edge(int u, int v, double w) : u(u), v(v), w(w) {}
	
	int u;
	int v;
	double w;
};

class UF {
public:
	explicit UF(int n);
	
	int Find(int i) const;
	void Union(int i, int j);
	bool IsConnected(int i, int j) const;
	
	int cc_num() const {
		return cc_num_; 
	}
	
private:
	int cc_num_;	
	int n_;
	vector<int> rank_;
	mutable vector<int> parent_;
};

UF::UF(int n) : n_(n), cc_num_(n), rank_(n), parent_(n) {
	for(int i = 0; i < n; ++i) {
		parent_[i] = i;
		rank_[i] = 0;
	}
}

int UF::Find(int i) const {
	if(parent_[i] != i) {
		parent_[i] = Find(parent_[i]);
	}
	return parent_[i];
}

void UF::Union(int i, int j) {
	int i_id = Find(i);
	int j_id = Find(j);
	if(i_id == j_id) {
		return;
	}
	--cc_num_;
	if(rank_[i_id] > rank_[j_id]) {
		parent_[j_id] = i_id;
	} else {
		parent_[i_id] = j_id;
		if(rank_[i_id] == rank_[j_id]) {
			++rank_[j_id];
		}
	}
}

bool UF::IsConnected(int i, int j) const {
	return Find(i) == Find(j);
}

double Cluster(const vector<pair<int, int> >& points, int k);
double dist(const pair<int, int>& p1, const pair<int, int>& p2);

int main() {
	ios_base::sync_with_stdio(0);
	int n, k;
	cin >> n;
	vector<pair<int, int> > points;
	for (int i = 0; i < n; ++i) {
		int x, y;
		cin >> x >> y;
		points.push_back(pair<int, int>(x, y));
	}
	cin >> k;
	cout << setprecision(10) << Cluster(points, k) << endl;
	return 0;	
}

double Cluster(const vector<pair<int, int> >& points, int k) {
	vector<Edge> edges;
	for(int i = 0; i < points.size(); ++i) {
		for(int j = i + 1; j < points.size(); ++j) {
			edges.push_back(Edge(i, j, dist(points[i], points[j])));
		}
	}
	sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2)->bool { return e1.w < e2.w; });
	UF uf(points.size());	
	for(auto& e : edges) {
		if(uf.cc_num() == k) {
			break;
		}
		uf.Union(e.u, e.v);
	}
	double d = DBL_MAX;
	for(auto& e : edges) {
		if(e.w < d && !uf.IsConnected(e.u, e.v)) {
			d = e.w;
		}
	}
	return d;	
}

double dist(const pair<int, int>& p1, const pair<int, int>& p2) {
	return sqrt((p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second));
}
