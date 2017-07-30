#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int Multiple(int a);

int main() {
	int n;
	cin >> n;
	vector<int> nums(n);
	for(auto& num : nums) {
		cin >> num;
	}
	sort(nums.begin(), nums.end(), [](int a, int b)->bool {
		return a * Multiple(b) + b > b * Multiple(a) + a;
	});
	for(auto num : nums) {
		cout << num;
	}
	cout << endl;
	return 0;
}

int Multiple(int a) {
	int res = 10;
	while((a /= 10) && (res *= 10)); 
	return res;
}
