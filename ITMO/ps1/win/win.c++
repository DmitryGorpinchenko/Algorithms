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
 
int MaxProblemsNum(std::vector<int> ts, int time_limit);

int main() 
{
	int n;
	std::ios::sync_with_stdio(false);
	cin >> n;
	std::vector<int> ts(n);
	for(auto& t : ts) {
		cin >> t;
	}
	cout << MaxProblemsNum(ts, 300 * 60) << std::endl;
	return 0;
}

int MaxProblemsNum(std::vector<int> ts, int time_limit)
{
	int time = 0, count = 0;
	std::sort(ts.begin(), ts.end());
	for(auto t : ts) {
		time += t;
		if(time > time_limit) {
			break;
		}
		++count;
	}
	return count;
}
