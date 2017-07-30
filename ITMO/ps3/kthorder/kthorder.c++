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
#include <random>
#include <algorithm>

void GenInSeq(std::vector<int>& seq, int A, int B, int C);
void RangeOrder(std::vector<int>& a, int k1, int k2);

int main()
{
	int n, k1, k2, A, B, C;
	cin >> n >> k1 >> k2;
	cin >> A >> B >> C;
	std::vector<int> seq(n);
	cin >> seq[0];
	cin >> seq[1];
	GenInSeq(seq, A, B, C);
	RangeOrder(seq, k1, k2);
	for(int i = k1 - 1; i < k2; ++i) {
		cout << seq[i] << " ";
	}
	cout << std::endl;
	return 0;
}

void KthOrder(std::vector<int>& a, int l, int r, int k);

void RangeOrder(std::vector<int>& a, int k1, int k2)
{
	int l = 0, r = a.size() - 1;
	
	KthOrder(a, l, r, k2 - 1);
	KthOrder(a, l, k2 - 1, k1 - 1);
	
	std::sort(a.begin() + k1, a.begin() + k2);
}

void KthOrder(std::vector<int>& a, int l, int r, int k)
{ 	
  	if (l >= r) {
  		return;
  	}
  	
	static std::default_random_engine gen; 	
  	std::uniform_int_distribution<int> dist(l, r);
  	
  	int key = a[dist(gen)];
	int i = l, j = r;
	while (i <= j) {
		while (a[i] < key) {
			++i;
		}
		while (key < a[j]) {
			--j;
		}
		if (i <= j) {
			std::swap(a[i++], a[j--]);
		}
	}
	if (j >= k) {
		KthOrder(a, l, j, k);
	} else {
		KthOrder(a, i, r, k);
	}
}

void GenInSeq(std::vector<int>& seq, int A, int B, int C)
{
	for(int i = 2; i < seq.size(); ++i) {
		seq[i] = A * seq[i - 2] + B * seq[i - 1] + C;
	}
}
