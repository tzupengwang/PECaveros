#include <bits/stdc++.h>

using namespace std;

const int N = 111;
const int K = 55;

int n, k;
queue<int> prob[N];

inline bool alle() {
  for (int i = 1; i <= n; ++i)
    if (prob[i].size() > 0) return 0;
  return 1;
}

int main() {
#ifndef EDDY
  freopen("easy.in", "r", stdin);
  freopen("easy.out", "w", stdout);
#endif
  cin >> n >> k;
  for (int i = 1; i <= n; ++i) {
    int p;
    cin >> p;
    for (int j = 0; j < p; ++j) {
      int x;
      cin >> x;
      prob[i].push(x);
    }
  }
  int ans = 0, cnt = 0;
  int i = 1;
  while (cnt < k) {
    if (alle()) {
      ++cnt;
      ans += 50;
      continue;
    }
    if (prob[i].size() == 0) {
      if (50 >= ans) {
        ++cnt;
        ans += 50;
      }
    } else {
      if (prob[i].front() >= ans) {
        ans += prob[i].front();
        ++cnt;
      }
      prob[i].pop();
    }
    ++i;
    if (i > n) i = 1;
  }
  cout << ans << endl;
}
