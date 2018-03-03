#include<bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
const int inf = 100000000;
vector<ii> v[105];
int n;

int dp[105][12005];
int st[12005];
int pr[105];

void reset(int *s, int m) {
  for (int i = 0; i <= m + m; i ++) s[i] = inf;
}

void dfs(int x, int m) {
  bool chd = false;
  for (ii e: v[x]) if (pr[x] != e.first) {
    int y = e.first, t = e.second % 60;
    pr[y] = x;
    dfs(y, m);

    if (t) {
      int t1 = t, t2 = 60 - t;
      reset(st, m);
      for (int i = 0; i <= m + m; i ++) {
        if (i >= t1) st[i] = min(st[i], dp[y][i - t1] - t1);
        if (i + t2 <= m + m) st[i] = min(st[i], dp[y][i + t2] + t2);
      }

      for (int i = 0; i <= m + m; i ++) {
        if (st[i] > m) st[i] = inf;
        if (i) st[i] = min(st[i], st[i - 1]);

        dp[y][i] = st[i];
      }
    }

    if (!chd) {
      chd = true;
      for (int i = 0; i <= m + m; i ++) dp[x][i] = dp[y][i];
    } else {
      reset(st, m);
      for (int ti = 0; ti <= m + m; ti ++) {
        int i = ti - m;
        int j = min(i, m - i);
        int tj = j + m;
        if (dp[x][ti] + dp[y][tj] <= m)
          st[ti] = min(st[ti], max(dp[x][ti], dp[y][tj]));
        if (dp[y][ti] + dp[x][tj] <= m)
          st[ti] = min(st[ti], max(dp[y][ti], dp[x][tj]));
      }

      for (int i = 0; i <= m + m; i ++) {
        if (st[i] > m) st[i] = inf;
        if (i) st[i] = min(st[i], st[i - 1]);

        dp[x][i] = st[i];
      }
    }
  }
  if (!chd) {
    for (int i = m; i <= m + m; i ++) dp[x][i] = 0;
  } else {
    for (int i = 0; i < m; i ++) dp[x][i] = inf;
    for (int i = m; i <= m + m; i ++) dp[x][i] = max(0, dp[x][i]);
  }
}

bool ok(int m) {
  for (int i = 1; i <= n; i ++)
    reset(dp[i], m);

  pr[1] = 1;
  dfs(1, m);

  for (int i = 0; i <= m + m; i ++)
    if (dp[1][i] <= m) return true;
  return false;
}

int main() {
  int cs = 1;
  while (scanf("%d", &n) && n) {
    for (int i = 1; i <= n; i ++) v[i].clear();
    for (int i = 1; i < n; i ++) {
      int x, y, z;
      scanf("%d%d%d", &x, &y, &z);
      v[x].push_back(ii(y, z));
      v[y].push_back(ii(x, z));
    }
    int l = 0, r = 6000;
    while (l < r) {
      int m = (l + r) / 2;
      if (ok(m)) r = m;
      else l = m + 1;
    }
    printf("Case %d: %d\n", cs ++, l);
  }
}
