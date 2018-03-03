
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 110;
const int M = 555;

int n, m;
vector<int> g[N*2], rg[N*2], vs;
bool vis[N*2];
int mk[N*2];
vector<int> vars[M];

inline int neg(int x) {
  return x > n ? x-n: x+n;
}

inline void adde(int u, int v) {
  g[u].push_back(v);
  rg[v].push_back(u);
}

void dfs(int u) {
  vis[u] = 1;
  for (int v: g[u]) if (!vis[v]) dfs(v);
  vs.push_back(u);
}

void rdfs(int u, int t) {
  vis[u] = 1;
  mk[u] = t;
  for (int v: rg[u]) if (!vis[v]) rdfs(v, t);
}

inline bool chk(int X) {
  vs.clear();
  for (int i = 1; i <= n+n; ++i) {
    g[i].clear();
    rg[i].clear();
  }
  adde(neg(X), X);
  for (int i = 1; i <= m; ++i) {
    if (vars[i].size() < 3) {
      for (int y: vars[i]) adde(neg(y), y);
    } else {
      for (int x: vars[i]) for (int y: vars[i]) if (x != y) {
        adde(neg(x), y);
      }
    }
  }

  fill(vis, vis+n+n+1, 0);
  vs.clear();
  for (int i = 1; i <= n+n; ++i) if (!vis[i]) dfs(i);
  fill(vis, vis+n+n+1, 0);
  reverse(vs.begin(), vs.end());
  int t = 0;
  for (int u: vs) if (!vis[u]) rdfs(u, ++t);
  for (int i = 1; i <= n; ++i) if (mk[i] == mk[neg(i)]) return 0;
  return 1;
}

int _cs;
char anss[N];

void main2() {
  for (int i = 1; i <= m; ++i) {
    vars[i].clear();
  }

  for (int i = 1; i <= m; ++i) {
    int k; scanf("%d", &k);
    for (int j = 0; j < k; ++j) {
      int x; char tp[2];
      scanf("%d%s", &x, tp);
      if (tp[0] == 'y') vars[i].push_back(x);
      else vars[i].push_back(neg(x));
    }
  }
  bool flag = 1;
  for (int i = 1; i <= n; ++i) {
    anss[i] = '?';
    bool pi = chk(i);
    bool ni = chk(neg(i));
    if (pi and ni) anss[i] = '?';
    else if (pi) anss[i] = 'y';
    else if (ni) anss[i] = 'n';
    else flag = 0;
  }
  anss[n+1] = 0;
  if (!flag) printf("Case %d: impossible\n", ++_cs);
  else printf("Case %d: %s\n", ++_cs, anss+1);
}

int main(){
  while (scanf("%d%d", &n, &m) && n) {
    main2();
  }
}
