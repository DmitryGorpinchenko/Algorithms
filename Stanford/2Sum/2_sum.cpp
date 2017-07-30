#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>

using namespace std;

int TwoSum(const vector<long long>& nums, long long min, long long max);

int main() {
	ios_base::sync_with_stdio(0);
	long long num;
	vector<long long> nums;
	while(cin >> num) {
		nums.push_back(num);
	}
	cout << "Answer: " << TwoSum(nums, -10000, 10000) << endl;	
	return 0;
}

int TwoSum(const vector<long long>& nums, long long min, long long max) {
	unordered_set<long long> sums;
	set<long long> nums_set;
	for(auto n : nums) {
		nums_set.insert(n);
	}
	for(auto n : nums) {
		auto lo = nums_set.lower_bound(min - n);
		auto hi = nums_set.upper_bound(max - n);
		for(auto i = lo; i != hi; ++i) {
			if(n != *i) {
				sums.insert(*i + n);
			}
		}
	}
	return sums.size();
}
