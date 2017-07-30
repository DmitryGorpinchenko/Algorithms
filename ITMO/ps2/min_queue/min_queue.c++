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
#include <limits>

class MinQueue {
public:
	MinQueue();
	
	void push(int n);
	int pop();
	int min();
	
private:
	std::stack<int>	in;
	std::stack<int>	min_in;
	std::stack<int>	out;
	std::stack<int>	min_out;
};

MinQueue :: MinQueue()
{
	min_in.push(std::numeric_limits<int>::max());
	min_out.push(std::numeric_limits<int>::max());
}

void MinQueue :: push(int n) 
{
	in.push(n);
	min_in.push(std::min(n, min_in.top()));
}

int MinQueue :: pop() 
{
	if(out.empty()) {
		while(! in.empty()) {
			int el = in.top();
			in.pop();
			min_in.pop();
			out.push(el);
			min_out.push(std::min(el, min_out.top()));
		}
	}
	int res = out.top();
	out.pop();
	min_out.pop();
	return res;
}

int MinQueue :: min() 
{
	return std::min(min_in.top(), min_out.top());
}

int main() 
{
	MinQueue q;
	int N, tmp;
	char c;
	cin >> N;
	for(int i = 0; i < N; ++i) {
		cin >> c;
		switch(c) {
		case '+':
			cin >> tmp;
			q.push(tmp);
			break;
		case '-':
			q.pop();
			break;
		case '?':
			cout << q.min() << "\n";
			break;
		default:
			return  -1;
		}
	}
	return  0;
}

