#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;

int n, m;
int s1[105][105];
int s2[105][105];
ii st, ed;

bool ds(ii pt, int dir, int &ds) {
  ds = 0;
  int i = pt.first, j = pt.second;
  if (dir == 0) {
    if (j < m && s1[i][j]) ds = s1[i][j];
  } else if (dir == 1) {
    if (i < n && s2[i][j]) ds = s2[i][j];
  } else if (dir == 2) {
    if (j > 1 && s1[i][j - 1]) ds = s1[i][j - 1];
  } else if (dir == 3) {
    if (i > 1 && s2[i - 1][j]) ds = s2[i - 1][j];
  }
  if (ds > 0) return true;
  return false;
}

int dis[105][105][4][2];
struct S {
  ii p;
  int dir, pos;
  int ds;
  S() {}
  S(int x1, int x2, int x3, int x4) :
    p(x1, x2), dir(x3), pos(x4) {}
  S(int x1, int x2, int x3, int x4, int x5) :
    p(x1, x2), dir(x3), pos(x4), ds(x5) {}

  bool operator<(const S X) const {
    return ds > X.ds;
  }
};

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

void upd(int &x, int y) {
  if (y == -1) return;
  if (x == -1) x = y;
  else x = min(x, y);
}

void solve() {
  memset(dis, -1, sizeof dis);
  
  priority_queue<S> pq;

  for (int i = 0; i < 4; i ++) {
    int d;
    if (ds(st, i, d)) {
      pq.push(S(st.first + dx[i], st.second + dy[i], i, 1, d + d));
    }
  }
  while (!pq.empty()) {
    S now = pq.top(); pq.pop();
    int x = now.p.first;
    int y = now.p.second;
    int lstd = now.dir;
    int trn = now.pos;
    int dd = now.ds;
    if (dis[x][y][lstd][trn] != -1) continue;
    //printf("vis %d %d %d %d: %d\n", x, y, lstd, trn, dd);
    dis[x][y][lstd][trn] = dd;

    for (int i = 0; i < 4; i ++) {
      int d;
      if (ds(ii(x, y), i, d)) {
        if (i == lstd) {
          pq.push(S(x + dx[i], y + dy[i], i, 0, dd + d));
        } else {
          if (trn) {
            pq.push(S(x + dx[i], y + dy[i], i, 1, dd + d + d));
          } else {
            int td;
            ds(ii(x, y), (lstd + 2) % 4, td);

            pq.push(S(x + dx[i], y + dy[i], i, 1, dd + td + d + d));
          }
        }
      }
    }
  }

  int ans = -1;
  for (int i = 0; i < 4; i ++) {
    upd(ans, dis[ed.first][ed.second][i][1]);

    int td;
    if (ds(ed, (i + 2) % 4, td) && dis[ed.first][ed.second][i][0] != -1) {
      //printf("in %d\n", dis[ed.first][ed.second][i][0]);
      upd(ans, dis[ed.first][ed.second][i][0] + td);
    }
  }
  if (ans == -1) printf("Impossible\n");
  else printf("%d\n", ans);
}

int main(){
  int cs = 1;
  while (scanf("%d%d%d%d%d%d", &n, &m, &st.first, &st.second, &ed.first, &ed.second) == 6) {
    if (n == 0 && m == 0) break;

    for (int i = 1; i <= n; i ++) {
      for (int j = 1; j <= m - 1; j ++)
        scanf("%d", &s1[i][j]);
      if (i < n) {
        for (int j = 1; j <= m; j ++)
          scanf("%d", &s2[i][j]);
      }
    }

    printf("Case %d: ", cs ++);
    solve();
  }
}
