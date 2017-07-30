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
#include <vector>
#include <cmath>
#include <cstring>

template <typename T>
using Matrix = std::vector<std::vector<T> >;

double MaxTeamEff(const Matrix<double>& eff);
double MaxTeamEff(const Matrix<double>& eff, int N, int M);

int main()
{
	int N = 3;
	//int N = 20;
	Matrix<double> eff(N, std::vector<double>(N));
	for(int i = 0; i < N; ++i) {
		for(int j = 0; j < N; ++j) {
			cin >> eff[i][j];	
			//eff[i][j] = 1;
		}
	}
	cout << std::setprecision(15);
	cout << MaxTeamEff(eff) << std::endl;
	return 0;
}

double MaxTeamEff(const Matrix<double>& eff) 
{
	return std::sqrt(MaxTeamEff(eff, eff.size(), 0));
}

double MaxTeamEff(const Matrix<double>& eff, int N, int M)
{
	using Cache = std::vector<std::vector<double> >;
	static Cache cache(1 << eff[0].size(), std::vector<double>(eff.size(), -1.0));	

	if(N == 0) {
		return 0;
	}
	double best_score = -1;
	for(int i = 0, n_roles = eff[0].size(); i < n_roles; ++i) {
		if((M >> i) & 0x1) {
			continue;
		}
		M |= (1 << i); // select i'th role
		if(cache[M][N - 1] < 0) {
			cache[M][N - 1] = MaxTeamEff(eff, N - 1, M);
		}
		double score = eff[N - 1][i] * eff[N - 1][i] + cache[M][N - 1]; 	
		if(score > best_score) {
			best_score = score;
		}
		M &= ~(1 << i); // deselect i'th role
	}
	return best_score;
}	
