#include <iostream>
#include <vector>
#include <memory>
#include <stdlib.h>
#include <time.h> 

#include "set.h"

using namespace std;

void ProcessQueries(vector<string>* log);
void PrintLog(const vector<string>& log);
void StressTest();

int main() {	
	StressTest();
	/*ios_base::sync_with_stdio(false);
	vector<string> log;
	ProcessQueries(&log);
	PrintLog(log);*/
	return 0;
}

void StressTest() {
	const int OP_NUM = 4;
	const int MAX_NUM = 1000000000;
	int count_find = 0;
	//for(int tt = 0; tt < 10; tt++) {
	for(int tt = 0; tt < 1; tt++) {
		srand(time(NULL));
		SplaySet sset;
		NaiveSet nset;
		vector<int> visited;
		for(int t = 0; t < 100000; t++) {
			int op = rand() % OP_NUM;
			int i = (rand() % 2 == 0 && visited.size() > 0) ? visited[rand() % visited.size()] : rand() % MAX_NUM;
			visited.push_back(i);
			if(op == 0) {
				sset.Add(i);
				nset.Add(i);
			} else if(op == 1) {
				sset.Del(i);
				nset.Del(i);
			} else if(op == 2) {
				int l = rand() % (MAX_NUM / 2);
				//ensure that r >= l
				int r = l + rand() % (MAX_NUM / 2);
				if(sset.Sum(l, r) != nset.Sum(l, r)) {
					cout << "NOT PASSED!!! Something went wrong!!!" << endl;
					return;
				}
			} else {
				++count_find;
				if(sset.Find(i) != nset.Find(i)) {
					cout << "NOT PASSED!!! Something went wrong!!!" << endl;
					return;
				}
			}
		}
	}
	cout << "PASSED in all " << count_find << " cases!!!" << endl;
}

void ProcessQueries(vector<string>* log) {
	int n, i, l, r;
	cin >> n;
	int M = 1000000001;
	char op;
	unique_ptr<Set> set(new SplaySet);
	for(int t = 0; t < n; t++) {
		cin >> op;
		switch(op) {
			case '+': {
				cin >> i;
				set->Add((i + set->last_sum()) % M);
				break;
			}
			case '-': {
				cin >> i;
				set->Del((i + set->last_sum()) % M);
				break;
			}
			case '?': {
				cin >> i;
				log->push_back(set->Find((i + set->last_sum()) % M) ? "Found" : "Not found");
				break;
			}
			case 's': {
				cin >> l >> r;
				l = (l + set->last_sum()) % M;
				r = (r + set->last_sum()) % M;
				log->push_back(to_string(set->Sum(l, r)));
				break;
			}
		}
	}
}

void PrintLog(const vector<string>& log) {
	for(auto& entry : log) {
		cout << entry << endl;
	}
}
