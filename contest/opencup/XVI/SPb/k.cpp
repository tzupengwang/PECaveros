#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 1e5+10;
const int LG = 20;

int n, m;
vector<int> g[N];
int dep[N];
int mom[LG][N];
LL w[N], mxw[N];
LL dp[N];

inline int lca(int u, int v) {
  if (dep[u] > dep[v]) swap(u, v);
  int jmp = dep[v]-dep[u];
  for (int k = 0; k < LG; ++k) if ( (jmp>>k)&1 )
    v = mom[k][v];
  if (u == v) return u;
  for (int k = LG-1; k >= 0; --k) if(mom[k][u] != mom[k][v]) {
    u = mom[k][u];
    v = mom[k][v];
  }
  return mom[0][u];
}

void dfs1(int u, int p) {
  mom[0][u] = p;
  dep[u] = 1+dep[p];
  for (int v: g[u]) if (v != p) {
    dfs1(v, u);
  }
}

void dfs2(int u, int p) {
  dp[u] = 0;
  mxw[u] = 0;
  for (int v: g[u]) if (v != p) {
    dfs2(v, u);
    w[u] += w[v];

    dp[u] += dp[v] + w[v];

    mxw[u] = max(mxw[u], w[v]);
  }
  dp[u] -= mxw[u];
}

LL ans;

void dfs3(int u, int p, LL pdp) {

//  printf("%d %lld %lld w %d dp %lld\n", u, pdp, tmp, w[u], dp[u]);

  LL sumdp = 0;
  for (int v: g[u]) if (v != p)
    sumdp += dp[v];

  LL sumw = w[u];
  for (int v: g[u]) if (v != p)
    sumw += w[v];

  if (u != 1) {
    LL tmp = pdp + sumdp + sumw - max(w[u], mxw[u]);
    ans = min(ans, tmp);
  }

  multiset<LL> ws;
  for (int v: g[u]) if (v != p)
    ws.insert(w[v]);
  ws.insert(w[u]);

  for (int v: g[u]) if (v != p) {
    LL tpdp = pdp + sumdp - dp[v] + sumw - w[v];
    ws.erase(ws.find(w[v]));
    tpdp -= *ws.rbegin();
    ws.insert(w[v]);

    dfs3(v, u, tpdp);
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n-1; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs1(1, 0);
  for (int j = 0; j < LG-1; ++j)
    for (int i = 1; i <= n; ++i)
      mom[j+1][i] = mom[j][mom[j][i]];

  for (int i = 0; i < m; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    int anc = lca(a, b);
    w[anc] -= 2;
    w[a]   += 1;
    w[b]   += 1;
  }

  dfs2(1, 0);

  ans = dp[1];
  dfs3(1, 0, 0);
  cout << ans << endl;
}
