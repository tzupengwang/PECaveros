
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 2020;

typedef pair<LL, char> XD;
typedef pair<int,int> pii;

#define X first
#define Y second

int r, c, sx, sy;
LL step;
LL n;

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};
int jx[] = {2, -2, -2, 2};
int jy[] = {-2, -2, 2, 2};

XD ans[N][N];

inline void walk(int &x, int &y, int d, LL len=1) {
  x += (dx[d] * len) % (LL)r;
  if (x >= r) x -= r;
  if (x < 0) x += r;
  y += (dy[d] * len) % (LL)c;
  if (y >= c) y -= c;
  if (y < 0) y += c;
}

inline pii get_pos(LL m) { // after m steps
  LL rnd = m / 4;
  int rst = m & 3;
  int x = (sx + jx[0] * rnd) % (LL)r;
  if (x < 0) x += r;
  int y = (sy + jy[0] * rnd) % (LL)c;
  if (y < 0) y += c;
  for (int k = 0; k < rst; ++k) {
    walk(x, y, k, m - rst + k + 1);
  }
  return {x, y};
}

inline void upd(XD& a, LL ts, char ch) {
  if (a.first < ts) a = {ts, ch};
}

inline void go(pii p, LL len, LL cur) {
  int d = cur&3;
  int cx = p.X;
  int cy = p.Y;
  while (len--) {
    upd(ans[cx][cy], cur, 'A' + (cur % 26LL));
    walk(cx, cy, d);
    if (cx == p.X and cy == p.Y) break;
  }
}

int main(){
  scanf("%d%d%d%d%lld", &r, &c, &sx, &sy, &n);
  for (int i = 0; i < r; ++i)
    for (int j = 0; j < c; ++j)
      ans[i][j] = {-1, '.'};
  sx--, sy--;
  step = min(n, 4LL*max(r, c));
  LL cur = n;
  pii lst = get_pos(n);
  ans[lst.X][lst.Y] = {n, '@'};
  for (LL i = 1; i <= step; ++i) {
    pii p = get_pos(n-i);
    LL len = (n-i+1);
    go(p, len, n-i);
  }
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      printf("%c", ans[i][j].second);
    }
    puts("");
  }
}
