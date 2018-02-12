
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int V = 3e6+10;

struct SCC {
  int n;
  vector<int> g[V], rg[V], vs;
  bool vis[V];
  int mk[V], m;
  void init(int _n) { n = _n; }
  void adde(int u, int v) {
    //printf("adde %d %d\n", u, v);
    g[u].push_back(v);
    rg[v].push_back(u);
  }
  void dfs(int u) {
    vis[u] = 1;
    for (int v: g[u]) if (!vis[v]) dfs(v);
    vs.push_back(u);
  }
  void rdfs(int u, int c) {
    vis[u] = 1;
    mk[u] = c;
    for (int v: rg[u]) if (!vis[v]) rdfs(v, c);
  }
  void solve() {
    m = 0;
    for (int i = 1; i <= n; ++i) if (!vis[i]) dfs(i);
    fill(vis+1, vis+1+n, 0);
    reverse(vs.begin(), vs.end());
    for (int i: vs) if (!vis[i]) rdfs(i, ++m);
  }
} scc;

const int N = 5e5+10;

typedef pair<int,int> pii;

int nxt[N*2][2], root, tot;
vector<int> at[N*2];
int n;
int pos[N], len[N];
char ip[N*2];

int ins(int u, char *s, int i, int choose=-1) {
  if (!u) u = ++tot;
  if (*s == 0) {
    if (choose == -1) {
      at[u].push_back(2*i - 0);
      at[u].push_back(2*i - 1);
    } else {
      at[u].push_back(2*i - choose);
    }
    return u;
  }
  if (*s == '?') {
    nxt[u][0] = ins(nxt[u][0], s+1, i, 0);
    nxt[u][1] = ins(nxt[u][1], s+1, i, 1);
  } else {
    int c = *s - '0';
    nxt[u][c] = ins(nxt[u][c], s+1, i, choose);
  }
  return u;
}

int tsz;

vector<pii> es;

inline int S(int u) {return u + n+n;}
inline int nS(int u) {return u + n+n+n+n;}

void dfs(int rt, int prv) {
  if (!rt) return;
  int pv = prv;
  //printf("  prv %d: ", prv);
  for (int u: at[rt]) {
    //printf(" %d", u);
    scc.adde(u, S(u));
    scc.adde(nS(u), u%2 == 0? u-1: u+1);
    if (pv) {
      scc.adde(S(u), S(pv));
      scc.adde(nS(pv), nS(u));
      scc.adde(pv, nS(u));
      scc.adde(S(u), pv%2 == 0? pv-1: pv+1);
    }
    pv = u;
  }
  //puts("");
  dfs(nxt[rt][0], pv);
  dfs(nxt[rt][1], pv);
}

int chose[N];

int main(){
#define FN "binary"
#ifndef LOCAL
  freopen( FN ".in" , "r" , stdin );
  freopen( FN ".out" , "w" , stdout );
#endif
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    char *cur = ip + pos[i-1] + len[i-1] + 1;
    pos[i] = cur-ip;
    scanf("%s", cur);
    len[i] = strlen(cur);
    root = ins(root, cur, i);
  }
  scc.init((n+n) * 3);
  dfs(root, 0);
  scc.solve();
  for (int i = 1; i <= n; ++i) {
    //printf("%c%c%c\n", "01"[scc.mk[i*2-1] > scc.mk[i*2]],
                       //"01"[scc.mk[S(i*2-1)] > scc.mk[nS(i*2-1)]],
                       //"01"[scc.mk[S(i*2)] > scc.mk[nS(i*2)]]
                     //);
    if (scc.mk[i*2-1] == scc.mk[i*2] or
        scc.mk[S(i*2-1)] == scc.mk[nS(i*2-1)] or
        scc.mk[S(i*2)] == scc.mk[nS(i*2)]
        ) {
      puts("NO");
      return 0;
    }
    chose[i] = scc.mk[i*2-1] > scc.mk[i*2];
  }
  puts("YES");
  for (int i = 1; i <= n; ++i) {
    char *cur = ip+pos[i];
    for (int j = 0; j < len[i]; ++j) if (cur[j] == '?') {
      cur[j] = '0' + chose[i];
    }
    printf("%s\n", cur);
  }
}
