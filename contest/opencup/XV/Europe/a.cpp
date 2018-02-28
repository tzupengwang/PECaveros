
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 666;
const int INF = 1e9;
int n, a[N], b[N], d[N];
int vis[N][N], ts;
int dp[N][N];
int DP(int l, int r) {
  if (l > r) return 0;
  if (vis[l][r] == ts) return dp[l][r];
  vis[l][r] = ts;
  int mxd = 0;
  for (int i = 1; i <= n; ++i) {
    if (l <= a[i] and b[i] <= r) mxd = max(mxd, d[i]);
  }
  if (mxd == 0) return dp[l][r] = 0;
  int tmp = INF;
  for (int i = l; i <= r; ++i) {
    tmp = min(tmp, DP(l, i-1) + DP(i+1, r));
  }
  dp[l][r] = mxd + tmp;
  return dp[l][r];
}
void main2() {
  scanf("%d", &n);
  vector<int> vs;
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d%d", a+i, b+i, d+i);
    vs.push_back(a[i]);
    vs.push_back(b[i]);
  }
  sort(vs.begin(), vs.end());
  vs.resize(unique(vs.begin(), vs.end()) - vs.begin());
  for (int i = 1; i <= n; ++i) {
    a[i] = lower_bound(vs.begin(), vs.end(), a[i]) - vs.begin();
    b[i] = lower_bound(vs.begin(), vs.end(), b[i]) - vs.begin();
  }
  ts++;
  int ans = DP(0, (int)vs.size() - 1);
  printf("%d\n", ans);
}
int main(){
  int tc;scanf("%d", &tc);while(tc--) main2();
}
