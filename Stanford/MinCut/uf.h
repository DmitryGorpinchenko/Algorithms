#ifndef UF_H
#define UF_H

#include <vector>

using namespace std;

class UF {
public:
	explicit UF(int n);
	
	int Find(int i) const;
	void Union(int i, int j);
	bool IsConnected(int i, int j) const;
	
	int cc_num() const {
		return cc_num_; 
	}
	
private:
	int cc_num_;	
	int n_;
	vector<int> rank_;
	mutable vector<int> parent_;
};

#endif
