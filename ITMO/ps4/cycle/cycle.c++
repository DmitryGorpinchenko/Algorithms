#ifdef JUDGE
#include <fstream>
std::ifstream cin("input.txt");
std::ofstream cout("output.txt");
#else
#include <iostream>
using std::cin;
using std::cout;
#endif

#include <vector>
#include <algorithm>
#include <assert.h>

using Graph = std::vector<std::vector<int> >;

bool FindCycle(const Graph& G, std::vector<int>* cycle);

int main()
{
	int N, M, s, t;
	cin >> N >> M;
	Graph G(N);
	for (int i = 0; i < M; ++i) {
		cin >> s >> t;
		G[s - 1].push_back(t - 1);
	}
	std::vector<int> cycle;
	if (FindCycle(G, &cycle)) {
		cout << "YES\n";
		for (auto v : cycle) {
			cout << (v + 1) << " ";
		}
	} else {
		cout << "NO";
	}
	cout << std::endl;
	return 0;
}

bool FindCycle(const Graph& G, int v, std::vector<int>* cycle);

bool FindCycle(const Graph& G, std::vector<int>* cycle)
{	
	for (int i = 0; i < G.size(); ++i) {
		if (FindCycle(G, i, cycle)) {
			return true;
		}
	}
	return false;
}

enum class State : int {
	NONE,
	ENTERED,
	EXITED
};

bool FindCycle(const Graph& G, int v, std::vector<int>* cycle) 
{
	static std::vector<State> states(G.size(), State::NONE);
	static std::vector<int> parent(G.size(), -1);
	
	if (states[v] == State::EXITED) {
		return false;
	}
	
	states[v] = State::ENTERED;
	
	for (auto adj : G[v]) {
		switch(states[adj]) {
		case State::ENTERED: {
			int start = adj, end = v; 
			for (int vtx = end; vtx != start; vtx = parent[vtx]) {
				cycle->push_back(vtx);
			}
			cycle->push_back(start);
			reverse(cycle->begin(), cycle->end());
			return true;
		}
		case State::NONE: {
			parent[adj] = v;
			if (FindCycle(G, adj, cycle)) {
				return true;
			}
		}
		case State::EXITED: // fallthru
		default: break;
		}	
	}
	
	states[v] = State::EXITED;
	return false;
}
