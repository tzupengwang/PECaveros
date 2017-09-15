#include <bits/stdc++.h>

using namespace  std;

const int N = 205;

int n, m;
int ans;
bitset<N> g[N];
bitset<N> r[N];

void build() {
  for (int i = n-1; i >= 0; --i) {
    r[i] = g[i];
    for (int j = i+1; j < n; ++j) if (g[i][j])
      r[i] |= r[j];
  }
  ans = 0;
  for (int i = 0; i < n; ++i)
    ans += r[i].count();
}

int main() {
#ifdef ONLINE_JUDGE
  freopen("settling.in", "r", stdin);
  freopen("settling.out", "w", stdout);
#endif
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    g[u][v] = 1;
  }
  build();
  printf("%d\n", ans);
  int q;
  scanf("%d", &q);
  while (q--) {
    char tp[2];
    int u, v;
    scanf("%s%d%d", tp, &u, &v);
    --u, --v;
    if (tp[0] == '+') {
      g[u][v] = 1;
      build();
      printf("%d\n", ans);
    }
    if (tp[0] == '-') {
      g[u][v] = 0;
      build();
      printf("%d\n", ans);
    }
    if (tp[0] == '?') {
      puts(r[u][v]? "YES": "NO");
    }
  }
}
