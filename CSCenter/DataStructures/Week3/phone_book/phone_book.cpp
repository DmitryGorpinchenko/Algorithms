#include <iostream>
#include <unordered_map>

using namespace std;

class PhoneBook {
public:
	void AddNum(int number, const string& name);
	void DelNum(int number);
	const string& Find(int number) const;
	
private:
	const static string NOT_FOUND;	
	unordered_map<int, string> names_;
};

const string PhoneBook::NOT_FOUND = "not found";

void PhoneBook::AddNum(int number, const string& name) {
	names_[number] = name;
}

void PhoneBook::DelNum(int number) {
	names_.erase(number);
}

const string& PhoneBook::Find(int number) const {
	auto itr = names_.find(number);
	return itr != names_.end() ? itr->second : NOT_FOUND;
}

void ProcessQueries();
	
int main() {
	ios::sync_with_stdio(false);
	ProcessQueries();
	return 0;	
}

void ProcessQueries() {
	int N, number;
	cin >> N;
	string query_type, name;
	PhoneBook book;
	for(int i = 0; i < N; ++i) {
		cin >> query_type >> number;
		if(query_type == "add") {
			cin >> name;
			book.AddNum(number, name);
		} else if(query_type == "del") {
			book.DelNum(number);
		} else if(query_type == "find") {
			cout << book.Find(number) << endl;
		}
	}
}
