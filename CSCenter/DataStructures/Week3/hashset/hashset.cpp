#include <iostream>
#include <vector>
#include <forward_list>
#include <algorithm>

using namespace std;

class Entry {
public:
	explicit Entry(const string& s) : s_(s), hash_(PolyHash(s)) {}
	
	long long hash() const {
		return hash_;
	}
	
	const string& ToString() const {
		return s_;
	}
	
	bool operator== (const Entry& other) const {
		return s_ == other.s_;
	}	
	
private:
	static long long PolyHash(const string& s) {
		long long code = 0;
		int p = 1000000007;
		int x = 263;
		for(int i = static_cast<int>(s.size() - 1); i >= 0; --i) {
			code = (code * x + s[i]) % p;
		}
		return code;
	}
	
	string s_;
	long long hash_;
};

template <typename T> 
class HashSet {
public:
	HashSet(int m) : buckets_(m) {}
	
	void Add(const T& el);
	bool Contains(const T& el) const;
	void Del(const T& el);
	void CheckBucket(int i, string* resp) const;
	
private:
	vector<forward_list<T>> buckets_;
};

template <typename T> 
void HashSet<T>::Add(const T& el) {
	auto& chain = buckets_[el.hash() % buckets_.size()];
	if(find(chain.begin(), chain.end(), el) == chain.end()) {
		chain.push_front(el);
	}
}

template <typename T> 
bool HashSet<T>::Contains(const T& el) const {
	auto& chain = buckets_[el.hash() % buckets_.size()];
	return find(chain.begin(), chain.end(), el) != chain.end();
}

template <typename T> 
void HashSet<T>::Del(const T& el) {
	auto& chain = buckets_[el.hash() % buckets_.size()];
	chain.remove(el);
}

template <typename T> 
void HashSet<T>::CheckBucket(int i, string* resp) const {
	for(auto& el : buckets_[i]) {
		*resp += el.ToString() + " ";
	}
	*resp += "\n";
}	

void ProcessQueries(vector<string>* log);

int main() {	
	ios::sync_with_stdio(false);
	vector<string> log;
	ProcessQueries(&log);
	for(auto& resp : log) {
		cout << resp;
	}
	return 0;
}

void ProcessQueries(vector<string>* log) {
	int m, N;
	cin >> m >> N;
	HashSet<Entry> set(m);
	string query, elem;
	int bucket;
	for(int i = 0; i < N; i++) {
		cin >> query;
		if(query == "check") {
			cin >> bucket;
			string resp;
			set.CheckBucket(bucket, &resp);
			log->push_back(resp);
		} else {
			cin >> elem;
			if(query == "add") {
				set.Add(Entry(elem));
			} else if(query == "del") {
				set.Del(Entry(elem));
			} else if(query == "find") {
				log->push_back(set.Contains(Entry(elem)) ? "yes\n" : "no\n");
			} 
		}
	}
}
