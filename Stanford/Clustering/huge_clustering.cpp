#include <iostream>
#include <vector>
#include <unordered_map>

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

const int spacing = 3;

int Cluster(const vector<int>& node_labels, int label_len);
bool IsHammingGreaterThan2(int label_1, int label_2, int label_len);

int main() {
    ios_base::sync_with_stdio(0);
    int n, label_len;
    cin >> n >> label_len;
    vector<int> node_labels(n);
    for(int i = 0; i < n; ++i) {
        int label = 0, bit;
        for(int b = 0; b < label_len; ++b) {
            cin >> bit;
            label |= (bit << (label_len - b - 1));
        }
        node_labels[i] = label;
    }
    cout << "k = " << Cluster(node_labels, label_len) << endl;
    return 0;
}

int Cluster(const vector<int>& node_labels, int label_len) {
    int partition = label_len / spacing;
    int mask = (~0u) >> (32 - partition);
    unordered_map<int, vector<int> > closest_candidates;
    for(int id = 0; id < node_labels.size(); ++id) {
        int label = node_labels[id];
        for(int j = 0; j < spacing; ++j) {
            closest_candidates[label & (mask << (j * partition))].push_back(id);
        }
    }
    UF uf(node_labels.size());
    for(auto& kv : closest_candidates) {
        auto& ids = kv.second;
        for(int i = 0; i < ids.size(); ++i) {
            for(int j = i + 1; j < ids.size(); ++j) {
                if(!IsHammingGreaterThan2(node_labels[ids[i]], node_labels[ids[j]], label_len)) {
                    uf.Union(ids[i], ids[j]);
                }
            }
        }
    }
    return uf.cc_num();
}

bool IsHammingGreaterThan2(int label_1, int label_2, int label_len) {
    int dist = 0;
    for(int i = 0; i < label_len; ++i) {
        dist += (((label_1 >> i) & 1) ^ ((label_2 >> i) & 1));
        if(dist > 2) {
            return true;
        }
    }
    return false;
}