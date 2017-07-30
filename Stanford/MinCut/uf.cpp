#include "uf.h"
#include <vector>

using namespace std;

UF::UF(int n) : n_(n), cc_num_(n), rank_(n), parent_(n) {
	for(int i = 0; i < n; ++i) {
		parent_[i] = i;
		rank_[i] = 0;
	}
}

int UF::Find(int i) const {
	if(parent_[i] != i) {
		parent_[i] = Find(parent_[i]);
	}
	return parent_[i];
}

void UF::Union(int i, int j) {
	int i_id = Find(i);
	int j_id = Find(j);
	if(i_id == j_id) {
		return;
	}
	--cc_num_;
	if(rank_[i_id] > rank_[j_id]) {
		parent_[j_id] = i_id;
	} else {
		parent_[i_id] = j_id;
		if(rank_[i_id] == rank_[j_id]) {
			++rank_[j_id];
		}
	}
}

bool UF::IsConnected(int i, int j) const {
	return Find(i) == Find(j);
}
