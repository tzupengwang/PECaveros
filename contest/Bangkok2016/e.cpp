#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> PII;

const int N = 5e4+10;
const int X = 1e5;
const int LOG = 20;

int n;
vector<PII> g[N];

void input() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    g[i].clear();
  }
  for (int i = 0; i < n-1; ++i) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    g[u].push_back({v, w});
    g[v].push_back({u, w});
  }
}

int mom[LOG][N];
int dep[N];

int tot, root[N], cnt[N*LOG], lc[N*LOG], rc[N*LOG];

int ins(int t, int l, int r, int x) {
  int res = ++tot;
  cnt[res] = cnt[t];
  lc[res] = lc[t];
  rc[res] = rc[t];
  cnt[res]++;
  if (l == r) return res;
  int mid = (l+r) / 2;
  if (x <= mid) lc[res] = ins(lc[t], l, mid, x);
  else rc[res] = ins(rc[t], mid+1, r, x);
  return res;
}

int kth(int t1, int t2, int st, int l, int r, int k) {
  if (l == r) return l;
  int lcnt = cnt[lc[t1]] + cnt[lc[t2]] - 2*cnt[lc[st]];
  int mid = (l+r) / 2;
  if (k - lcnt < 0) return kth(lc[t1], lc[t2], lc[st], l, mid, k);
  else return kth(rc[t1], rc[t2], rc[st], mid+1, r, k - lcnt);
}

void dfs(int u, int p, int d) {
  mom[0][u] = p;
  dep[u] = d;
  for (auto e: g[u]) {
    int v = e.first, w = e.second;
    if (v == p) continue;
    root[v] = ins(root[u], 1, X, w);
    dfs(v, u, d+1);
  }
}

void predo() {
  tot = 0;
  fill(root, root+n+1, 0);
  dfs(1, 0, 0);
  for (int j = 0; j < LOG-1; ++j) {
    for (int i = 1; i <= n; ++i) {
      mom[j+1][i] = mom[j][mom[j][i]];
    }
  }
}

inline int lca(int u, int v) {
  if (dep[u] > dep[v]) swap(u, v);
  int jmp = dep[v] - dep[u];
  for (int k = 0; k < LOG; ++k) if ((jmp>>k)&1)
    v = mom[k][v];
  if (u == v) return u;
  for (int k = LOG-1; k >= 0; --k) if (mom[k][u] != mom[k][v]) {
    u = mom[k][u];
    v = mom[k][v];
  }
  return mom[0][u];
}

inline int dis(int u, int v) {
  int a = lca(u, v);
  return dep[u] - dep[a] + dep[v] - dep[a];
}

inline int kth(int u, int v, int ord) {
  int a = lca(u, v);
  int res;
  res = kth(root[u], root[v], root[a], 1, X, ord);
  return res;
}

void solve() {
  int q;
  scanf("%d", &q);
  while (q--) {
    int a, b;
    scanf("%d%d", &a, &b);
    int len = dis(a, b);
    int ans;
    if (len & 1) {
      ans = kth(a, b, len / 2) * 2;
    }
    else {
      int r1 = kth(a, b, len / 2 - 1);
      int r2 = kth(a, b, len / 2);
      ans = (r1 + r2);
    }
    printf("%d.%d\n", ans / 2, (ans&1) ? 5 : 0);
  }
}

void main2() {
  input();
  predo();
  solve();
}

int main() {
  int t;scanf("%d", &t); while(t--) {
    main2();
  }
}
