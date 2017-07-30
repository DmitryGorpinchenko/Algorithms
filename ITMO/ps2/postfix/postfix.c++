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

int Eval(const std::string& expr);

int main()
{
	std::string expr;
	std::getline(cin, expr); // read N (not used by this impl)
	std::getline(cin, expr);
	cout << Eval(expr) << std::endl;
	return 0;
}

int Eval(const std::string& expr)
{
	std::stack<int> stack;
	for(auto c : expr) {
		if(c == ' ') {
			continue;
		}
		if(std::isdigit(c)) {
			stack.push(c - '0');
		} else {
			int op1, op2;
			op1 = stack.top();
			stack.pop();
			op2 = stack.top();
			stack.pop();
			switch(c) {
			case '+':
				stack.push(op2 + op1);
				break;
			case '-':
				stack.push(op2 - op1);
				break;
			case '*':
				stack.push(op2 * op1);
				break;
			default:
				break;
			}
		}
	}
	return stack.top();
}
