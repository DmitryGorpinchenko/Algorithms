#ifdef JUDGE
#include <fstream>
std::ifstream cin("input.txt");
std::ofstream cout("output.txt");
#else
#include <iostream>
using std::cin;
using std::cout;
#endif

int MaxTestsNum(int K);

int main()
{
	int K;
	cin >> K;
	cout << MaxTestsNum(K) << std::endl;
	return 0;
}

#include <vector>

static const std::vector<int> hcn 
{
	1, 
	2,       
	4,       
	6,       
	12,      
	24,      
	36,      
	48,      
	60,      
	120,     
	180,     
	240,    
	360,     
	720,     
	840,     
	1260,    
	1680,    
	2520,    
	5040,   
	7560,    
	10080,   
	15120,   
	20160,  
	25200,   
	27720,   
	45360,   
	50400,   
	55440,  
	83160,   
	110880,  
	166320,  
	221760, 
	277200,  
	332640,  
	498960,  
	554400,  
	665280,  
	720720,  
	1081080, 
	1441440, 
	2162160, 
	2882880, 
	3603600, 
	4324320, 
	6486480, 
	7207200, 
	8648640, 
	10810800
};

int MaxTestsNum(int K)
{
	for(int i = hcn.size() - 1; i >= 0; --i) {
		if(hcn[i] <= K) {
			return K - hcn[i] + 1;	
		}
	}
	return -1;	
}	
