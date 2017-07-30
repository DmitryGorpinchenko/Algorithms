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
#include <algorithm>

struct Matroshka {
	int id;
	int size;
	
	Matroshka(int id, int size) 
		: id(id)
		, size(size)
	{}
	
	bool operator< (const Matroshka& other) const
	{
		return size < other.size;
	}
};

bool Scarecrow(std::vector<Matroshka> ms, int k);

int main()
{
	int n, k, size;
	cin >> n >> k;
	std::vector<Matroshka> ms;
	for (int i = 0; i < n; ++i) {
		cin >> size;
		ms.push_back(Matroshka(i, size));
	}
	cout << (Scarecrow(ms, k) ? "YES" : "NO") << std::endl;
	return 0;
}

bool Scarecrow(std::vector<Matroshka> ms, int k)
{
	std::sort(ms.begin(), ms.end());
	for (int i = 0; i < ms.size(); ++i) {
		int j = i;
		int a = ms[i].size;		
		
		for (; j > 0 && ms[j - 1].size == a; --j);
		
		while (true) {
			if (j >= ms.size() 
				|| ms[j].size != a) {
				
				return false;
			}
			if (abs(ms[j++].id - i) % k == 0) {
				break;
			}
		}
	}
	return true;
}

