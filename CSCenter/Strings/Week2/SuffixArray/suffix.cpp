#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void SuffixArray(const string& text, vector<int>* suff_arr);

int main() {
	string text;
	cin >> text;
	vector<int> suff_arr(text.size());
	SuffixArray(text, &suff_arr);
	for(auto s : suff_arr) {
		cout << s << " ";
	}	
	cout << endl;
	return 0;
}

void SuffixArray(const string& text, vector<int>* suff_arr) {
	int size = text.size();
	for(int i = 0; i < size; ++i) {
		(*suff_arr)[i] = i;
	}
	sort(suff_arr->begin(), suff_arr->end(), [&](int p1, int p2)->bool {
		for(int i = 0; i < size; ++i) {
			char c1 = text[(p1 + i) % size], c2 = text[(p2 + i) % size];
			if(c1 != c2) {
				return c1 < c2;
			}
		}
		return false;
	});
}
