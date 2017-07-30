#include <iostream>
#include <vector>
#include <algorithm>

#define ALPHA_SIZE 5

using namespace std;

void InvBWT(const string& bwt, string* text);
int ToDigit(char c);

int main() {
	string bwt;
	cin >> bwt;
	string text;
	InvBWT(bwt, &text);
	cout << text << endl;
	return 0;
}

void InvBWT(const string& bwt, string* text) {
	vector<int> tmp(ALPHA_SIZE + 1, 0);
	for(auto c : bwt) {
		++tmp[ToDigit(c) + 1];
	}
	for(int i = 1; i < ALPHA_SIZE; ++i) {
		tmp[i + 1] += tmp[i];
	}
	vector<int> map(bwt.size());
	for(int i = 0; i < bwt.size(); ++i) {
		map[i] = tmp[ToDigit(bwt[i])]++;
	}
	int ptr = 0; text->push_back('$');
	while(bwt[ptr] != '$') {
		text->push_back(bwt[ptr]);
		ptr = map[ptr];
	} 
	reverse(text->begin(), text->end());	
}

int ToDigit(char c) {
	switch(c) {
		case '$': return  0;
		case 'A': return  1;
		case 'C': return  2;
		case 'G': return  3;
		case 'T': return  4;
		default : return -1;
	}
}
