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
 
int MaxAbility(const std::vector<int>& ps, const std::vector<int>& ts); 
 
int main() 
{
	int n;
	std::ios::sync_with_stdio(false);
	cin >> n;
	std::vector<int> ps(n);
	std::vector<int> ts(n);
	for(auto& p : ps) {
		cin >> p;
	}
	for(auto& t : ts) {
		cin >> t;
	}
	cout << MaxAbility(ps, ts) << std::endl;
	return 0;
}

int MaxAbility(const std::vector<int>& ps, const std::vector<int>& ts)
{
	int ability = 0;
	bool has_th_day = false, has_pr_day = false;
	std::vector<int> diff(ps.size());
	for(int i = 0, size = ps.size(); i < size; ++i) {
		if(ps[i] > ts[i]) {
			ability += ps[i];
			has_pr_day = true;
		} else {
			ability += ts[i];
			has_th_day = true;
		}
		diff[i] = ps[i] - ts[i];
	}
	if(! has_th_day) {
		ability -= *std::min_element(diff.begin(), diff.end());
	}
	if(! has_pr_day) {
		ability += *std::max_element(diff.begin(), diff.end());
	}
	return ability;
}
