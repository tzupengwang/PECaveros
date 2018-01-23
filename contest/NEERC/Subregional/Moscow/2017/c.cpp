#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> v[100005];
int sz[100005];
int pr[100005];

void dfs1(int x) {
  sz[x] = 1;
  for (int y : v[x]) if (pr[x] != y) {
    pr[y] = x;
    dfs1(y);
    sz[x] += sz[y];
  }
}

typedef pair<int, int> ii;
ii ans[100005];

void dfs2(int x, int lvl, int pos) {
  ans[x] = ii(pos, lvl);
  int mx = 0, mid = -1;
  for (int i = 0; i < (int)v[x].size(); i ++) {
    int y = v[x][i];
    if (y == pr[x]) continue;

    if (sz[y] >= mx) {
      mx = sz[y];
      mid = y;
    }
  }

  int cum = pos;
  for (int i = 0; i < (int)v[x].size(); i ++) {
    int y = v[x][i];
    if (y == pr[x]) continue;

    if (y == mid) {
      dfs2(y, lvl, pos + sz[x] - sz[y]);
    } else {
      dfs2(y, lvl + 1, cum);
      cum += sz[y];
    }
  }
}

int main(){
  scanf("%d", &n);
  for (int i = 1; i < n; i ++) {
    int x, y;
    scanf("%d%d", &x, &y);
    v[x].push_back(y);
    v[y].push_back(x);
  }
  dfs1(1);

  dfs2(1, 1, 1);
  for (int i = 1; i <= n; i ++) {
    printf("%d %d\n", ans[i].first, ans[i].second);
  }
}
