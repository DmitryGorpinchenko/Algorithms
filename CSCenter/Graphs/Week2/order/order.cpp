#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void dfs(const vector<vector<int> >& adj, vector<bool>& used, vector<int>* order, int x);     
void TopoSort(const vector<vector<int> >& adj, vector<int>* order);

int main() {
  ios_base::sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for(int i = 0; i < m; ++i) {
    int x, y;
    cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  vector<int> order;
  TopoSort(adj, &order);
  for(int v : order) {
    cout << v + 1 << " ";
  }
  cout << endl;
  return 0;
}

void TopoSort(const vector<vector<int> >& adj, vector<int>* order) {
  vector<bool> used(adj.size(), false);
  for(int i = 0; i < adj.size(); ++i) {
    if(!used[i]) {
  	   dfs(adj, used, order, i);
    }
  }
  reverse(order->begin(), order->end());
}

void dfs(const vector<vector<int> >& adj, vector<bool>& used, vector<int>* order, int x) {
  used[x] = true;
  for(int neigh : adj[x]) {
    if(!used[neigh]) {
  	 	dfs(adj, used, order, neigh);
  	 }
  }
  order->push_back(x);
}     
