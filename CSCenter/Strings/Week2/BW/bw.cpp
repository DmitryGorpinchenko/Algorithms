#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void BWT(const string& text, string* out);

int main() {
	string text;
	cin >> text;
	string bwt;
	BWT(text, &bwt);
	cout << bwt << endl;
	return 0;
}

void BWT(const string& text, string* out) {
	int size = text.size();
	vector<int> ptrs(size);
	for(int i = 0; i < size; ++i) {
		ptrs[i] = i;
	}
	sort(ptrs.begin(), ptrs.end(), [&](int p1, int p2)->bool {
		for(int i = 0; i < size; ++i) {
			if(text[(p1 + i) % size] != text[(p2 + i) % size]) {
				return text[(p1 + i) % size] < text[(p2 + i) % size];
			}
		}
		return false;
	});
	for(auto p : ptrs) {
		out->push_back(text[(p + size - 1) % size]);
	}	
}
