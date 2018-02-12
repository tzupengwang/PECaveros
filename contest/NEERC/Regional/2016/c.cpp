
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 5e4+10;

struct OP {
  char c;
  int a, b, c1, c2;
};

vector<OP> ans;

inline void join(int u, int v) {
  ans.push_back(OP{'j', u, v, 0, 0});
}
inline void rec(int a, int c1, int c2) {
  ans.push_back(OP{'r', a, 0, c1, c2});
}
inline void con(int a, int c1, int c2) {
  ans.push_back(OP{'c', a, 0, c1, c2});
}

int n, m;
vector<int> g[N];

void input() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int l; scanf("%d", &l);
    int u = -1;
    for (int j = 0; j < l; ++j) {
      int v; scanf("%d", &v);
      if (u != -1) {
        g[u].push_back(v);
        g[v].push_back(u);
      }
      u = v;
    }
  }
}

int dep[N];
bool vis[N];
int jmp2[N], jmpfr[N];

void dfs(int u, int p) {
  vis[u] = 1;
  vector<int> ch;
  jmp2[u] = u, jmpfr[u] = u;
  for (int v: g[u]) if (!vis[v]) {
    dep[v] = dep[u]+1;
    dfs(v, u);
    if (dep[jmp2[v]] < dep[jmp2[u]]) {
      jmp2[u] = jmp2[v];
      jmpfr[u] = jmpfr[v];
    }
    ch.push_back(v);
  } else if (dep[v] < dep[u] and v != p) {
    if (dep[v] < dep[jmp2[u]]) {
      jmp2[u] = v;
      jmpfr[u] = u;
    }
  }
  for (int v: ch) {
    if (dep[jmp2[v]] >= dep[u]) {
      rec(v, 3, 2);
    }
  }
  rec(u, 1, 4);
  for (int v: ch) {
    join(u, v);
    if (v == jmpfr[u] and dep[jmp2[u]] < dep[u])
      con(u, 4, 3);
  }
  con(u, 4, 2);
  rec(u, 2, 1);
  if (jmpfr[u] == u) {
    rec(u, 4, 3);
  } else {
    rec(u, 4, 2);
  }
}

void solve() {
  dfs(1, -1);
  printf("%d\n", ans.size());
  for (OP op: ans) {
    if (op.c == 'j') {
      printf("j %d %d\n", op.a, op.b);
    }
    if (op.c == 'r') {
      printf("r %d %d %d\n", op.a, op.c1, op.c2);
    }
    if (op.c == 'c') {
      printf("c %d %d %d\n", op.a, op.c1, op.c2);
    }
  }
}

int main(){
#define FN "cactus"
#ifndef LOCAL
  freopen( FN ".in" , "r" , stdin );
  freopen( FN ".out" , "w" , stdout );
#endif
  input();
  solve();
}
