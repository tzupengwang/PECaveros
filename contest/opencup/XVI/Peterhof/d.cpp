#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
int n;
vector< vector<int> > v;
int main(){
  cin >> n;
  puts("Yes");
  for (int i = 0; i < n/2; ++i) {
    vector<int> vec{0, i+1};
    for (int d = 1; d <= n-2; ++d) {
      int td = d;
      if (d&1) td = n-1 - d;
      int prv = vec.back() - 1;
      int now = ( prv + td ) % (n-1);
      vec.push_back(now + 1);
    }
    set<int> st(vec.begin(), vec.end());
    assert((int)st.size() == n);
    for (int j = 0; j < n; ++j) {
      printf("%d%c", vec[j] + 1, " \n"[j+1 == n]);
    }
  }
}
