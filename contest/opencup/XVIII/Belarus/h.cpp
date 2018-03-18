
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MOD = 1e9+7;
const int N = 1e5+10;

inline int add(int a, int b) { a+=b;return a>=MOD?a-MOD:a; }
inline int mul(LL a, int b) { a*=b;return a>=MOD?a%MOD:a; }
inline int pw(int a,int b) {
  int res = 1;
  for (;b; b>>=1) {
    if (b&1) res = mul(res, a);
    a = mul(a, a);
  }
  return res;
}

int n;
vector<int> g[N];
int dp[N], ans1, ans2;

void dfs1(int u, int p) {
  int res = 1;
  for (int v: g[u]) if (v != p) {
    dfs1(v, u);
    res = mul(res, add(dp[v], 1));
  }
  dp[u] = res;
  ans1 = add(ans1, dp[u]);
}

void dfs2(int u, int p, int pv) {
  int res = mul(dp[u], pv);
  for (int v: g[u]) if (v != p) {
    int tmp = mul(res, pw(add(dp[v], 1), MOD-2));
    tmp = add(tmp, 1);
    dfs2(v, u, tmp);
  }
  ans2 = add(ans2, res);
}

int main(){
  scanf("%d", &n);
  for (int i = 0; i < n-1; ++i) {
    int u, v;scanf("%d%d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs1(1, -1);
  dfs2(1, -1, 1);
  cout << ans1 << ' ' << ans2 << endl;
}
