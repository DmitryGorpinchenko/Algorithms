#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

class Heapifier {
public:
	void Heapify(vector<int>& data) {
		swaps_.clear();
		for(int i = data.size()/2 - 1; i >= 0; i--) {
			SiftDown(data, i);	
		}	
	}

	int GetSwapsNum() const {
		return swaps_.size();
	}

	void WriteSwaps() const {
		cout << swaps_.size() << "\n";
		for (auto& sw : swaps_) {
			cout << sw.first << " " << sw.second << "\n";
		}
	}
	
private:
	void SiftDown(vector<int>& data, int i) {
		int min_id = i, l = 2*i + 1, r = 2*i + 2;
		min_id = ((l < data.size()) && data[l] < data[min_id]) ? l : min_id;
		min_id = ((r < data.size()) && data[r] < data[min_id]) ? r : min_id;
		if(min_id != i) {
			swap(data[i], data[min_id]);
			swaps_.push_back(make_pair(i, min_id));
			SiftDown(data, min_id);
		}
	}

	vector<pair<int, int> > swaps_;
};

bool IsHeap(const vector<int>& data);
void FillRandomVector(vector<int> *data);
void ReadData(vector<int> *data);
void test();

int main() {
	//test();
	ios::sync_with_stdio(false);
	Heapifier heapifier;
	vector<int> data;
	ReadData(&data);
	heapifier.Heapify(data);
	heapifier.WriteSwaps();
	return 0;
}

void test() {
	const int MAX_SIZE = 100000;
	bool passed = true;
	for(int n = 1; n <= MAX_SIZE; n++) {
		vector<int> data(n);
		FillRandomVector(&data);
		Heapifier heapifier;
		heapifier.Heapify(data);
		passed = passed && (heapifier.GetSwapsNum() <= 4*n) && IsHeap(data);
		if(!passed) {
			break;
		}
		if(n % 1000 == 0) {
			cout << "iterations: " << n << "/" << MAX_SIZE << endl;
		}
	}
	cout << (passed ? "ALL TESTS: PASSED" : "SOME TESTS: FAILED") << endl;
}

bool IsHeap(const vector<int>& data) {
	int size = data.size(), l , r;
	for(int i = 0; i < size/2; i++) {
		l = 2*i + 1;
		r = 2*i + 2;
		//NOTE: in this implementation only the right child might not exist
		if(data[i] > data[l] || ((r < size) && data[i] > data[r])) {
			return false;
		}
	}
	return true;
}

void FillRandomVector(vector<int> *data) {
	srand(time(NULL));	
	const int MAX_VALUE = 1000000000;
	for(auto& el : *data) {
		el = rand() % MAX_VALUE;
	}
}

void ReadData(vector<int> *data) {
	int n;
	cin >> n;
	data->resize(n);
	for(auto& el : *data) {
		cin >> el;
	}
}
