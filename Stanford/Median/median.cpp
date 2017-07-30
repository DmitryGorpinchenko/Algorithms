#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>

using namespace std;

int median(const vector<int>& stream);

int main() {
	int n;
	vector<int> stream;
	while(cin >> n) {
		stream.push_back(n);
	}
	cout << median(stream) << endl;	
	return 0;
}

int median(const vector<int>& stream) {
	priority_queue<int> lo;
	priority_queue<int, vector<int>, greater<int>> hi;
	int sum = 0;
	for(auto n : stream) {
		if(lo.empty() || n < lo.top()) {
			if(lo.size() > hi.size()) {
				hi.push(lo.top());
				lo.pop();
			}
			lo.push(n);
		} else if(hi.empty() || n > hi.top()) {
			if(lo.size() <= hi.size()) {
				lo.push(hi.top());
				hi.pop();
			}
			hi.push(n);
		} else {
			if(lo.size() > hi.size()) {
				hi.push(n);
			} else {
				lo.push(n);
			}
		}
		sum = (sum + lo.top()) % 10000;
	}
	return sum;
}
