#ifdef JUDGE
#include <fstream>
std::ifstream cin("input.txt");
std::ofstream cout("output.txt");
#else
#include <iostream>
using std::cin;
using std::cout;
#endif

#include <iomanip>
 
double AvgTeammateDist(int a, int b, int c);

int main()
{
	int a, b, c;
	std::ios::sync_with_stdio(false);
	cin >> a >> b >> c;
	cout << std::setprecision(8);
	cout << AvgTeammateDist(a, b, c) << std::endl;
	return 0;
}

double AvgTeammateDist(int a, int b, int c)
{
	return (a + b + c) / 2.0 / 3;
}
