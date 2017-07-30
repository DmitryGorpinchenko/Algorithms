#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Item {
    int v, w;
};

class Knapsack {
public:
    explicit Knapsack(int W) : W_(W), V_(0) {}
    
    void FillDP(const vector<Item>& items);
    void FillMemoization(const vector<Item>& items);
    
    long long V() const {
        return V_;
    }
    
private:
    typedef unordered_map<int, unordered_map<int, long long> > vals_map;
    
    long long FillMemoization(const vector<Item>& items, vals_map& vals, int i, int w);
    
    int W_;
    long long V_;
};

void Knapsack::FillDP(const vector<Item>& items) {
    vector<vector<long long> > vals(items.size() + 1, vector<long long>(W_ + 1));
    for(int i = 1; i <= items.size(); ++i) {
        int w = items[i - 1].w, v = items[i - 1].v;
        for(int j = 1; j <= W_; ++j) {
            vals[i][j] = j < w ? vals[i - 1][j] : max(vals[i - 1][j], vals[i - 1][j - w] + v);
        }
    }
    V_ = vals[items.size()][W_];
}

void Knapsack::FillMemoization(const vector<Item>& items) {
    vals_map vals;
    V_ = FillMemoization(items, vals, items.size(), W_);
}

long long Knapsack::FillMemoization(const vector<Item>& items, vals_map& vals, int i, int w) {
    if(i == 0) {
        return 0;
    }
    int w_i = items[i - 1].w, v_i = items[i - 1].v;
    vals[i - 1][w] = vals[i - 1][w] ? vals[i - 1][w] : FillMemoization(items, vals, i - 1, w);
    if(w < w_i) {
        return vals[i - 1][w];
    }
    vals[i - 1][w - w_i] = vals[i - 1][w - w_i] ? vals[i - 1][w - w_i] : FillMemoization(items, vals, i - 1, w - w_i);
    return max(vals[i - 1][w], vals[i - 1][w - w_i] + v_i);
}

int main() {
    int W, n;
    cin >> W >> n;
    vector<Item> items(n);
    for(int i = 0; i < n; ++i) {
        cin >> items[i].v >> items[i].w;
    }
    Knapsack knapsack(W);
    //knapsack.FillDP(items);
    knapsack.FillMemoization(items);
    cout << knapsack.V() << endl;
    return 0;
}
