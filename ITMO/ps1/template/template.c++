#ifdef JUDGE
#include <fstream>
std::ifstream cin("input.txt");
std::ofstream cout("output.txt");
#else
#include <iostream>
using std::cin;
using std::cout;
#endif

#include <vector>
#include <algorithm>
#include <limits>

class Keyboard {
public:
	Keyboard(const std::string& keys, int W, int H);
	
	int CalcTimeToPrint(const std::string& text);
	
private:
	std::vector<std::pair<int, int> > coords;	
};

int main()
{
	int W, H;
	std::ios::sync_with_stdio(false);
	cin >> W >> H;
	std::string keys, tmp;
	for(int i = 0; i < H; ++i) {
		cin >> tmp;
		keys += tmp;	
	}
	Keyboard kb(keys, W, H);
	std::string lang, best_lang;
	int best_time = std::numeric_limits<int>::max(), time;
	while(cin >> lang) {
		cin >> tmp;
		std::string code;
		do {
			cin >> tmp;
			if(tmp == "%TEMPLATE-END%") {
				break;
			}
			code += tmp;
		} while(true);
		time = kb.CalcTimeToPrint(code);
		if(best_time > time) {
			best_time = time;
			best_lang = lang;
		}
	}
	cout << best_lang << std::endl;
	cout << best_time << std::endl;
	return 0;
}

static const int c_max_sym_code = 126;

Keyboard :: Keyboard(const std::string& keys, int W, int H) 
	: coords(c_max_sym_code + 1) 
{
	for(int i = 0; i < H; ++i) {
		for(int j = 0; j < W; ++j) {
			coords[keys[i * W + j]].first = j;
			coords[keys[i * W + j]].second = i;	
		}
	}		
}

int Keyboard :: CalcTimeToPrint(const std::string& text)
{
	int time = 0;
	for(int i = 0, size = text.size() - 1; i < size; ++i) {
		int x1 = coords[text[i]].first;
		int y1 = coords[text[i]].second;
		int x2 = coords[text[i + 1]].first;
		int y2 = coords[text[i + 1]].second;; 
		time += std::max(std::abs(x1 - x2), std::abs(y1 - y2));
	}
	return time;
}
