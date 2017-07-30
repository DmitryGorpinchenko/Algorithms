#ifdef JUDGE
#include <fstream>
std::ifstream cin("input.txt");
std::ofstream cout("output.txt");
#else
#include <iostream>
using std::cin;
using std::cout;
#endif

#include <unordered_map>
#include <deque>

enum class Action : int {
	ADD,
	TAKE, 
	MUM
};

static Action GetAction(const std::string& act_str) 
{
	static std::unordered_map<std::string, Action> act_map 
	{
		{ "add" , Action::ADD  },
		{ "take", Action::TAKE },
		{ "mum!", Action::MUM  }
	}; 
	return act_map[act_str];
}

class Lightsabers {
public:
	Lightsabers() 
		: tail(1)
	{}	
	
	int size() const;
	void Add(int num);
	void Take(int *num);
	void Reorder();
	
	friend std::ostream& operator<< (std::ostream& stream, const Lightsabers& ls);
	
private:
	void BalanceHalves(Action act);

	std::deque<int> halves[2]; 
	int tail;
};

int main()
{
	int N, num;
	std::string act_str;
	cin >> N;
	Lightsabers ls;
	for(int i = 0; i < N; ++i) {
		cin >> act_str;
		switch(GetAction(act_str)) {
		case Action::ADD:
			cin >> num;
			ls.Add(num);
			break;
		case Action::TAKE:
			ls.Take(&num);
			break;
		case Action::MUM:
			ls.Reorder();
			break; 
		default:break;
		}	
	}
	cout << ls;
	return  0;
}

void Lightsabers :: Add(int num)
{
	halves[tail].push_back(num);
	BalanceHalves(Action::ADD);
}

void Lightsabers :: Take(int *num)
{
	*num = halves[tail].back();
	halves[tail].pop_back();
	BalanceHalves(Action::TAKE);
}

void Lightsabers :: Reorder()
{
	tail = (tail + 1) % 2;
	BalanceHalves(Action::MUM);
}

void Lightsabers :: BalanceHalves(Action act) 
{
	switch(act) {
	case Action::ADD:
		if(halves[tail].size() > halves[(tail + 1) % 2].size() + 1) {
			int tmp = halves[tail].front();
		 	halves[tail].pop_front();
			halves[(tail + 1) % 2].push_back(tmp);
		}
		break;
	case Action::TAKE:
	case Action::MUM: // fallthru
		if(halves[tail].size() < halves[(tail + 1) % 2].size()) {
			int tmp = halves[(tail + 1) % 2].back();
		 	halves[(tail + 1) % 2].pop_back();
			halves[tail].push_front(tmp);
		}
		break;
	default: break;
	}
}

int Lightsabers :: size() const
{
	return halves[0].size() + halves[1].size();
}	
		
std::ostream& operator<< (std::ostream& stream, const Lightsabers& ls)
{
	stream << ls.size() << std::endl;
	for(int i = 1; i >= 0; --i) { // from head to tail
		for(auto saber : ls.halves[(ls.tail + i) % 2]) {
			stream << saber << " ";
		}
	}
	stream << std::endl;
	return stream;
}
