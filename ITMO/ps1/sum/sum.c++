#ifdef JUDGE
#include <fstream>
std::ifstream cin("input.txt");
std::ofstream cout("output.txt");
#else
#include <iostream>
using std::cin;
using std::cout;
#endif
  
int Sum(int a, int b);
  
int main() 
{
	int a, b;
	cin >> a >> b;
	cout << Sum(a, b) << std::endl;
	return 0;
}

int Sum(int a, int b)
{
	return a + b;
}
