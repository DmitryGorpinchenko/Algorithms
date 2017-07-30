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
#include <cstdint>

using array = std::vector<int>;

int64_t inv(const array& arr);

int main()
{
	int N;
	cin >> N;
	array arr(N);
	for (auto& el : arr) {
		cin >> el;
	}
	cout << inv(arr) << std::endl;
	return 0;	
}

void inv(array& arr, int lo, int hi, array& scratch, int64_t& inv_count);

int64_t inv(const array& arr)
{
	int64_t inv_count = 0;
	array copy = arr;
	array scratch(arr.size());
	inv(copy, 0, arr.size(), scratch, inv_count);
	return inv_count;
}

void inv(array& arr, int lo, int hi, array& scratch, int64_t& inv_count)
{
	if (hi <= lo + 1) {
		return;
	}
	
	int mid = lo + (hi - lo) / 2;
	
	inv(arr, lo, mid, scratch, inv_count);
	inv(arr, mid, hi, scratch, inv_count);
	
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
		if (arr[i] > arr[j]) {
			inv_count += (mid - i);
			scratch[k] = arr[j++];
		} else {
			scratch[k] = arr[i++];
		}
	}
	for (int k = lo; k < hi; ++k) {
		arr[k] = scratch[k];
	}
}
