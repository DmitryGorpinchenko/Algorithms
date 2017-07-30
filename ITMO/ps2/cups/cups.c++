#ifdef JUDGE
#include <fstream>
std::ifstream cin("input.txt");
std::ofstream cout("output.txt");
#else
#include <iostream>
using std::cin;
using std::cout;
#endif

#include <queue>
#include <limits>
#include <algorithm>

int main()
{
	int N, a, min, max = 0;
	cin >> N;
	std::priority_queue<int, std::vector<int>, std::greater<int> > pq;
	for(int i = 0; i < N; ++i) {
		cin >> a;
		min = 1;
		if(a == 0 && !pq.empty()) {
			min += pq.top();
			pq.pop();
		}
		pq.push(min);
		max = std::max(max, min);
	}
	cout << max << std::endl;
	return  0;
}

