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

using array = std::vector<int>;

void sort(array& arr);

int main()
{
	int N;
	cin >> N;
	array arr(N);
	for(auto& el : arr) {
		cin >> el;
	}
	sort(arr);
	for(auto& el : arr) {
		cout << el << " ";
	}
	cout << std::endl;
	return 0;	
}

void sort(array& arr, int lo, int hi, array& scratch);

void sort(array& arr)
{
	array scratch(arr.size());
	sort(arr, 0, arr.size(), scratch);
}

void sort(array& arr, int lo, int hi, array& scratch)
{
	if (hi <= lo + 1) {
		return;
	}
	
	int mid = lo + (hi - lo) / 2;
	
	sort(arr, lo, mid, scratch);
	sort(arr, mid, hi, scratch);
	
	int i = lo, j = mid;
	for (int k = lo; k < hi; ++k) {
		if (i >= mid) {
			scratch[k] = arr[j++];
			continue;
		}
		if (j >= hi) {
			scratch[k] = arr[i++];
			continue;
		}
		scratch[k] = arr[i] > arr[j] ? arr[j++] : arr[i++];
	}
	for (int k = lo; k < hi; ++k) {
		arr[k] = scratch[k];
	}
#ifdef JUDGE
	cout << lo + 1 << " " << hi << " ";
	cout << arr[lo] << " " << arr[hi - 1] << "\n";
#endif
}
