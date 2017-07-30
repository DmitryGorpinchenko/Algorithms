#include <iostream>
#include <vector>

#define ALPHA_SIZE 5

using namespace std;

typedef const vector<int> V;

vector<int> BuildSuffixArray(const string& S);
vector<int> SortCharacters(const string& S);
vector<int> ComputeCharClasses(const string& S, V& order);
vector<int> SortDoubled(const string& S, int L, V& order, V& cl);
vector<int> UpdateClasses(V& order, V& cl, int L);
int ToDigit(char c);

int main() {
    string S;
    cin >> S;
    vector<int> suff_arr = BuildSuffixArray(S);
    for(auto pos : suff_arr) {
        cout << pos << " ";
    }
    cout << endl;
    return 0;    
}

vector<int> BuildSuffixArray(const string& S) {
    vector<int> order = SortCharacters(S);
    vector<int> cl = ComputeCharClasses(S, order);
    int L = 1;
    while(L < S.size()) {
        order = SortDoubled(S, L, order, cl);
        cl = UpdateClasses(order, cl, L);
        L *= 2;
    }
    return order;
}

vector<int> SortCharacters(const string& S) {
    vector<int> order(S.size());
    vector<int> count(ALPHA_SIZE, 0);
    for(int i = 0; i < S.size(); ++i) {
        ++count[ToDigit(S[i])];
    }
    for(int i = 1; i < ALPHA_SIZE; ++i) {
        count[i] += count[i - 1];
    }
    for(int i = S.size() - 1; i >= 0; --i) {
        order[--count[ToDigit(S[i])]] = i;
    }
    return order;
}

vector<int> ComputeCharClasses(const string& S, V& order) {
    vector<int> cl(S.size(), 0);
    for(int i = 1; i < S.size(); ++i) {
        cl[order[i]] = cl[order[i - 1]] + (S[order[i]] != S[order[i - 1]]);
    }
    return cl;
}

vector<int> SortDoubled(const string& S, int L, V& order, V& cl) {
    vector<int> count(S.size(), 0);
    vector<int> new_order(S.size());
    for(int i = 0; i < S.size(); ++i) {
        ++count[cl[i]];
    }
    for(int i = 1; i < S.size(); ++i) {
        count[i] += count[i - 1];
    }
    for(int i = S.size() - 1; i >= 0; --i) {
        int start = (order[i] - L + S.size()) % S.size();
        new_order[--count[cl[start]]] = start;
    }
    return new_order;
}

vector<int> UpdateClasses(V& order, V& cl, int L) {
    int cur, prev, mid, mid_prev;
    vector<int> new_cl(order.size(), 0);
    for(int i = 1; i < order.size(); ++i) {
        cur = order[i]; prev = order[i - 1];
        mid = (cur + L) % order.size(); mid_prev = (prev + L) % order.size();
        new_cl[cur] = new_cl[prev] + (cl[cur] != cl[prev] || cl[mid] != cl[mid_prev]); 
        
    }
    return new_cl;
}

int ToDigit(char c) {
    switch(c) {
        case '$' : return  0;
        case 'A' : return  1;
        case 'C' : return  2;
        case 'G' : return  3;
        case 'T' : return  4;
        default  : return -1;
    }
}
