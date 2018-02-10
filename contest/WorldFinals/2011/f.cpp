
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 1e5+10;
const LL INF = 1e18;

typedef long double T;

struct Line {
  LL m, b;
  LL operator()(LL x) { return m*x+b; }
  T operator%(const Line& r) const {
    return 1. * (r.b - b) / (m - r.m);
  }
};

int n;
int ord[N], tord[N];
LL C, D[N], P[N], R[N], G[N];

LL dp[N];
Line stk[N];

void dq(int l, int r) {
  if (l == r) return;
  int mid = (l+r) / 2;
  dq(l, mid);

  for (int i = l; i <= mid; ++i) tord[i] = ord[i];
  sort(tord+l, tord+mid+1, [&](int i, int j) { return G[i] < G[j]; });
  int s, e; s = e = 0;
  for (int i = l; i <= mid; ++i) {
    int id = tord[i];
    if (dp[id] < 0) continue;
    Line ln{G[id], dp[id] + R[id] - G[id] * (D[id] + 1)};
    if (e-s > 0 and stk[e-1].m == ln.m) {
      if (stk[e-1].b > ln.b) continue;
      else e--;
    }
    while (e-s >= 2 and stk[e-2] % stk[e-1] > stk[e-2] % ln) e--;
    stk[e++] = ln;
  }

  for (int i = mid+1; i <= r; ++i) {
    int id = ord[i];
    while (e-s >= 2 and stk[s](D[id]) <= stk[s+1](D[id])) s++;
    if (e-s > 0) {
      dp[id] = max(dp[id], -P[id] + stk[s](D[id]));
      if (dp[id] < 0) dp[id] = -INF;
    }
  }
  

  dq(mid+1, r);
}
int _cs;
int main(){
  while (scanf("%d%lld", &n, &C) != EOF) {
    if (!n) break;
    scanf("%lld", D+n+1);
    D[n+1]++;
    P[n+1] = R[n+1] = G[n+1] = 0;
    for (int i = 1; i <= n; ++i)
      scanf("%lld%lld%lld%lld", D+i, P+i, R+i, G+i);
    for (int i = 0; i <= n+1; ++i) ord[i] = i;
    sort(ord, ord+n+1+1, [&](int i, int j) { return D[i] < D[j]; });
    dp[0] = C;
    for (int i = 1; i <= n+1; ++i) dp[i] = -INF;
    dq(0, n+1);
    printf("Case %d: %lld\n", ++ _cs , dp[n+1]);
  }
}
