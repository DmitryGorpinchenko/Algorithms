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

bool VerifyBrackets(const std::string& expr);

int main() 
{
	int N;
	cin >> N;
	std::string expr;
	for(int i = 0; i < N; ++i) {
		cin >> expr;
		cout << (VerifyBrackets(expr) ? "YES" : "NO");
		cout << std::endl;
	}
	return  0;
}

bool VerifyBrackets(const std::string& expr)
{
	static const auto& is_open = [](char c) {
		switch(c) {
		case '(': // fallthru
		case '[': return true;
		default : break;
		}
		return false;
	};
	static const auto& get_open = [](char c) {
		switch(c) {
		case ')': return '(';
		case ']': return '[';
		default : break;
		}
		return '\0';
	};
	std::stack<char> stack;
	for(auto c : expr) {
		if(is_open(c)) {
			stack.push(c);
		} else if(stack.empty()) {
			return false;
		} else if(stack.top() != get_open(c)) {
			return false;
		} else {
			stack.pop();
		}
	}
	return stack.empty();
}
