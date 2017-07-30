#include <iostream>
#include <stack>
#include <string>

class Bracket {
public:
	Bracket(int type, int position):
		type_(type),
		position_(position)
	{}

	bool Match(const Bracket& other) {
		if (type_ == '[' && other.type_ == ']')
			return true;
		if (type_ == '{' && other.type_ == '}')
			return true;
		if (type_ == '(' && other.type_ == ')')
			return true;
		return false;
	}

	bool IsOpen() {
		return type_ == '[' || type_ == '(' || type_ == '{';
	}

	int position() {
		return position_;
	}	

	static bool isBracket(char c) {
		return c == '[' || c == '(' || c == '{' || c == '}' || c == ')' || c == ']';
	}	

private: 
    char type_;
    int  position_;
};

int CheckBrackets(const std::string& text);

int main() {
	std::ios::sync_with_stdio(false);
	std::string text;
	getline(std::cin, text);

	int pos = CheckBrackets(text);
	if(pos == -1) {
		std::cout << "Success" << std::endl;
	} else {
		std::cout << pos << std::endl;
	}

	return 0;
}

int CheckBrackets(const std::string& text) {
	std::stack<Bracket> stack;
	for (int id = 0; id < text.length(); ++id) {
		if(Bracket::isBracket(text[id])) {
			Bracket b(text[id], id + 1);
			if(b.IsOpen()) {
				stack.push(b);
			} else {
				if(stack.empty() || !stack.top().Match(b)) {
					return b.position();
				}
				stack.pop();
			}
		}
	}
	return stack.empty() ? -1 : stack.top().position();
}
