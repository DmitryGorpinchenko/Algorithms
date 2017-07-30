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
#include <numeric>
#include <cstdint>
#include <memory>

class Snowman {
public: 
	Snowman() 
		: 
		mass_(0)
	{}
	
	int mass() const
	{
		return mass_;
	}
	
	void grow(int m) 
	{
		head_ = std::shared_ptr<Snowman>(new Snowman(*this));
		mass_ += m;
	}
	
	void shrink() 
	{
		*this = *head_;
	}
	
private:
	std::shared_ptr<Snowman> head_;
	int mass_;
};

class SnowmanReplicator {
public:
	SnowmanReplicator() 
	{
		snowmen.push_back(Snowman());
	}
	
	int64_t mass() const
	{
		return std::accumulate(snowmen.begin(), snowmen.end(), static_cast<int64_t>(0), [](int64_t acc, const Snowman& s) {
			return acc + s.mass();
		});
	}
	
	void clone(int snowman_id, int mutation) 
	{
		auto new_snowman = snowmen[snowman_id];
		if(mutation == 0) {
			new_snowman.shrink();
		} else {
			new_snowman.grow(mutation);
		}
		snowmen.push_back(new_snowman);
	}

private:
	std::vector<Snowman> snowmen;
};

int main()
{
	int N, id;
	int mutation;
	cin >> N;
	SnowmanReplicator r;
	for(int i = 0; i < N; ++i) {
		cin >> id >> mutation;
		r.clone(id, mutation);
	}
	cout << r.mass() << "\n";
	return 0;
}
