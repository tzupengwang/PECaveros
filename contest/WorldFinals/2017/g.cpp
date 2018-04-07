
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int H = 333;

int w, h, a[H][H];
char ip[H][H];
int ans[H][H], ans_w, ans_h;

int cur_w, cur_h;
int b[H][H];

void inv(int &th, int &tw) {
  th = 0, tw = 0;
  int lh = H, lw = H;
  for (int i = 1; i <= cur_h + 5; ++i)
    for (int j = 1; j <= cur_w + 5; ++j) {
      b[i][j] = a[i][j];
      if (i > cur_h || j > cur_w) b[i][j] = 0;
      for (int di = 0; di <= 2; ++di) for (int dj = 0; dj <= 2; ++dj) {
        int ii = i - di;
        int jj = j - dj;
        if (ii == i && jj == j) continue;
        if (ii < 0 || jj < 0) continue;
        b[i][j] ^= b[ii][jj];
      }
      if (b[i][j]) {
        th = max(th, i);
        tw = max(tw, j);
        lh = min(lh, i);
        lw = min(lw, j);
      }
    }
  th = th - lh + 1;
  tw = tw - lw + 1;
  for (int i = 1; i <= th; ++i)
    for (int j = 1; j <= tw; ++j)
      b[i][j] = b[i+lh-1][j+lw-1];
}

bool reduce() {
  if (cur_w <= 2 || cur_h <= 2) return 0;
  int th = 0, tw = 0;
  inv(th, tw);
  if (th > cur_h-2 || tw > cur_w-2) {
    int cx = th+1, cy = tw+1;
    for (int i = 1; i <= th; ++i) {
      for (int j = 1; j <= tw; ++j) {
        if (b[i][j] && (i > cur_h-2 || j > cur_w-2)) {
          cx = min(cx, i);
          cy = min(cy, j);
        }
      }
    }
    a[cx][cy] ^= 1;
    inv(th, tw);
    if (th > cur_h-2 || tw > cur_w-2) return 0;
  }
  cur_h = th;
  cur_w = tw;
  for (int i = 1; i <= cur_h; ++i)
    copy(b[i]+1, b[i]+cur_w+1, a[i]+1);
  return 1;
}

int main(){
  scanf("%d%d", &w, &h);
  for (int i = 1; i <= h; ++i) {
    scanf("%s", ip[i]+1);
    for (int j = 1; j <= w; ++j)
      a[i][j] = (ip[i][j] == '#')? 1: 0;
  }
  for (int i = 1; i <= h; ++i)
    for (int j = 1; j <= w; ++j) ans[i][j] = a[i][j];
  ans_h = h;
  ans_w = w;

  cur_w = w, cur_h = h;

  for (int _ = 0; _ < 11111; ++_) {
    if (!reduce()) break;
    if (cur_w * cur_h < ans_w * ans_h) {
      for (int i = 1; i <= cur_h; ++i)
        for (int j = 1; j <= cur_w; ++j) ans[i][j] = a[i][j];
      ans_h = cur_h;
      ans_w = cur_w;
    }
  }

  for (int i = 1; i <= ans_h; ++i) {
    for (int j = 1; j <= ans_w; ++j) putchar(".#"[ans[i][j]]);
    putchar('\n');
  }
}
