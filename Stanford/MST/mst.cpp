#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Edge {
	Edge(int u, int v, int w) : u(u), v(v), w(w) {}
	
	int u;
	int v;
	int w;
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

long long MSTLen(vector<Edge >& edges, int n);

int main() {
	ios_base::sync_with_stdio(0);
	int n, m, u, v, w;
	cin >> n >> m;
	vector<Edge> edges;
	for(int i = 0; i < m; ++i) {
		cin >> u >> v >> w;
		edges.push_back(Edge(u - 1, v - 1, w));
	}
	cout << MSTLen(edges, n) << endl;
	return 0;	
}

long long MSTLen(vector<Edge >& edges, int n) {
	long long len = 0;
	sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2)->bool { return e1.w < e2.w; });
	UF uf(n);	
	for(auto& e : edges) {
		if(uf.cc_num() == 1) {
			break;
		}
		if(!uf.IsConnected(e.u, e.v)) {
			uf.Union(e.u, e.v);
			len += e.w;
		}
	}
	return len;	
}
