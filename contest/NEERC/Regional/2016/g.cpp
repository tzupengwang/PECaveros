#include<bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef pair<ii, int> iii;

int n, m;
vector<int> v[100005];
vector<int> rev[100005];

int ans[100005][2]; // 1: W, 2: L, 3: D
bool tg[100005][2];
int deg[100005];
int dg[100005][2];

int main() {
#ifndef LOCAL
  freopen("game.in", "r", stdin);
  freopen("game.out", "w", stdout);
#endif
  scanf("%d%d", &n, &m);

  for (int i = 0; i < m; i ++) {
    int x, y;
    scanf("%d%d", &x, &y);

    v[x].push_back(y);
    rev[y].push_back(x);
  }

  {
    queue<ii> q;
    for (int i = 1; i <= n; i ++) {
      deg[i] = v[i].size();
      if (deg[i] == 0) {
        q.push(ii(i, 0));
        q.push(ii(i, 1));
      }
    }

    while (!q.empty()) {
      ii X = q.front(); q.pop();

      int now = X.first, who = X.second;

      if (tg[now][who]) continue;
      tg[now][who] = true;
      int twho = 1 - who;

      for (int x : rev[now]) if (!tg[x][twho]) {
        if (twho == 1) {
          q.push(ii(x, twho));
        } else {
          if (-- deg[x] == 0) q.push(ii(x, twho));
        }
      }
    }

    for (int i = 1; i <= n; i ++) {
      for (int j = 0; j < 2; j ++) {
        if (!tg[i][j]) ans[i][j] = 3;
      }
    }
  }

  {
    queue<iii> q;
    for (int i = 1; i <= n; i ++) {
      dg[i][0] = dg[i][1] = v[i].size();
      for (int j : v[i]) {
        if (ans[j][0]) dg[i][1] --;
        if (ans[j][1]) dg[i][0] --;
      }

      if (dg[i][0] == 0) {
        q.push(iii(ii(i, 0), 2));
      }
      if (dg[i][1] == 0) {
        q.push(iii(ii(i, 1), 2));
      }
    }

    while (!q.empty()) {
      iii X = q.front(); q.pop();

      int now = X.first.first, who = X.first.second, res = X.second;

      //printf("[%d][%d] = %d\n", now, who, res);
      if (ans[now][who]) continue;
      ans[now][who] = res;

      int twho = 1 - who;
      for (int x : rev[now]) if (!ans[x][twho]) {
        if (res == 2) {
          q.push(iii(ii(x, twho), 1));
        } else {
          if (-- dg[x][twho] == 0) {
            q.push(iii(ii(x, twho), 2));
          }
        }
      }
    }

    for (int i = 1; i <= n; i ++)
      for (int j = 0; j < 2; j ++)
        if (ans[i][j] == 0) ans[i][j] = j + 1;
  }

  // output amswer
  for (int i = 0; i < 2; i ++) {
    for (int j = 1; j <= n; j ++) {
      printf("%c", " WLD"[ans[j][i]]);
    }
    puts("");
  }
}
