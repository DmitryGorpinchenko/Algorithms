#ifdef JUDGE
#include <fstream>
std::ifstream cin("input.txt");
std::ofstream cout("output.txt");
#else
#include <iostream>
using std::cin;
using std::cout;
#endif

#include <stack> 

int main()
{
	std::ios::sync_with_stdio(false);
	char command;
	int N, el;
	cin >> N;
	std::stack<int> stack;
	for(int i = 0; i < N; ++i) {
		cin >> command;
		switch(command) {
		case '+':
			cin >> el;
			stack.push(el);	
			break;
		case '-':
			cout << stack.top() << "\n";
			stack.pop();
			break;
		default:
			return -1;
		}
	}
	return 0;
}
