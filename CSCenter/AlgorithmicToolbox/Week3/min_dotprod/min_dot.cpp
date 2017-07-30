#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

long long min_dot_product(vector<int> a, vector<int> b) {
  sort(a.begin(), a.end(), [](int a1, int a2)->bool {return a2 < a1;});
  sort(b.begin(), b.end(), [](int a1, int a2)->bool {return a1 < a2;});
  //it is important for the parameters to be long long for both lambda operations
  return inner_product(a.begin(), a.end(), b.begin(), 0L, [](long long a, long long b) {return a + b;}, 
  																				[](long long a, long long b) {return a * b;});
}

int main() {
  size_t n;
  cin >> n;
  vector<int> a(n), b(n);
  for (size_t i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (size_t i = 0; i < n; i++) {
    cin >> b[i];
  }
  cout << min_dot_product(a, b) << endl;
}
