
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 555;

int a, b, m, n;

int mn[N][N];
int d[N][N];

int dep[N];
int ll[N], rr[N];

inline LL calc(LL wid) {
  {
    vector<int> stk;
    for (int i = 1; i <= m; ++i) {
      while (stk.size() && dep[stk.back()] >= dep[i]) stk.pop_back();
      if (stk.size()) ll[i] = stk.back() + 1;
      else ll[i] = 1;
      stk.push_back(i);
    }
  }
  {
    vector<int> stk;
    for (int i = m; i >= 1; --i) {
      while (stk.size() && dep[stk.back()] >= dep[i]) stk.pop_back();
      if (stk.size()) rr[i] = stk.back() - 1;
      else rr[i] = m;
      stk.push_back(i);
    }
  }
  LL res = 0;
  for (int i = 1; i <= m; ++i) {
    LL x = min(a, rr[i] - ll[i] + 1);
    if (x*wid == m*n) continue;
    LL h = dep[i] + (LL)(dep[i] * x * wid - 1) / (m*n - x * wid);
    //printf("%d %d %d %d %lld %lld\n", i, ll[i], rr[i], dep[i], h, h * x * wid);
    res = max(res, (LL)h * x * wid);
  }
  return res;
}

LL solve() {
  LL res = 0;
  for (int l = 1; l <= n; ++l) {
    for (int i = 1; i <= m; ++i) {
      mn[i][l] = d[i][l];
      for (int j = l+1; j <= n; ++j)
        mn[i][j] = min(d[i][j], mn[i][j-1]);
    }
    for (int r = l; r <= min(l+b-1, n); ++r) {
      for (int i = 1; i <= m; ++i) dep[i] = mn[i][r];
      //printf("[%d, %d]\n", l, r);
      res = max(res, calc(r-l+1));
    }
  }
  return res;
}

int main(){
  scanf("%d%d%d%d", &a, &b, &m, &n);
  for (int i = 1; i <= m; ++i)
    for (int j = 1; j <= n; ++j)
      scanf("%d", d[i]+j);
  LL ans = 0;
  ans = solve();
  swap(a, b);
  ans = max(ans, solve());
  cout << ans << endl;
}
