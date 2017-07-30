#ifdef JUDGE
#include <fstream>
std::ifstream cin("input.txt");
std::ofstream cout("output.txt");
#else
#include <iostream>
using std::cin;
using std::cout;
#endif

#include <cstdint>  
  
int64_t SqSum(int64_t a, int64_t b);
  
int main() 
{
	int64_t a, b;
	cin >> a >> b;
	cout << SqSum(a, b) << std::endl;
	return 0;
}

int64_t SqSum(int64_t a, int64_t b)
{
	return a + (b * b);
}
