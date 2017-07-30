#include <iostream>
#include <vector>

using namespace std; 

void MatchPattern(const string& pattern, const string& text, vector<int>* matches);
void ComputePrefixFunction(const string& s, vector<int>* pref);

int main() {
    ios::sync_with_stdio(false);
    string pattern, text;
    cin >> pattern >> text;
    vector<int> matches;
    MatchPattern(pattern, text, &matches);
    for(auto pos : matches) {
        cout << pos << " ";
    }
    cout << endl;
    return 0;
}

void MatchPattern(const string& pattern, const string& text, vector<int>* matches) {
    int P = pattern.size(), size = P + 1 + text.size();
    vector<int> pref(size);
    ComputePrefixFunction(pattern + "$" + text, &pref);
    for(int i = P + 1; i < size; ++i) {
        if(pref[i] == P) {
            matches->push_back(i - 2*P);
        }
    }
}

void ComputePrefixFunction(const string& s, vector<int>* pref) {
    (*pref)[0] = 0;
    int border = 0;
    for(int i = 1; i < s.size(); ++i) {
        while(border > 0 && (s[i] != s[border]) && (border = (*pref)[border - 1]));
        (*pref)[i] = (s[i] == s[border]) ? ++border : (border = 0);
    }
}
