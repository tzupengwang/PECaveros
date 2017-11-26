#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int OF = 2510;
const int X  = 5050;

int d1[X][X], d2[X][X];
int n;

inline void add(int d[X][X], int lx, int ly, int rx, int ry) {
//  printf("%d %d %d %d\n", lx, ly, rx, ry);
  lx += OF;
  ly += OF;
  rx += OF;
  ry += OF;
  d[lx][ly]++;
  d[rx+1][ry+1]++;

  d[lx][ry+1]--;
  d[rx+1][ly]--;
}

inline void build(int d[X][X]) {
  for (int i = 1; i < X; ++i)
    for (int j = 1; j < X; ++j) {
      d[i][j] = d[i][j] + d[i-1][j] + d[i][j-1] - d[i-1][j-1];
    }
}

inline int qry(int d[X][X], int x, int y) {
  if ( x+OF < 0 || x+OF >= X ) return 0;
  if ( y+OF < 0 || y+OF >= X ) return 0;
  return d[x+OF][y+OF];
}

inline int calc(int x, int y) {
  if (qry(d1, x, y) > 0) return 4;
  int tx = x+y;
  int ty = x-y;
  int res = 0;
  if (qry(d2, tx, ty)) res++;
  if (qry(d2, tx, ty+1)) res++;
  if (qry(d2, tx-1, ty+1)) res++;
  if (qry(d2, tx-1, ty)) res++;
  return res;
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    char tp[2];
    int x, y, r;
    scanf("%s%d%d%d", tp, &x, &y, &r);
    r /= 2;
    if (*tp == 'A') {
      add(d1, x-r+1, y-r+1, x+r, y+r);
    } else {
      int tx = x+y;
      int ty = x-y;
      add(d2, tx-r+1, ty-r+1, tx+r, ty+r);
    }
  }
  build(d1);
  build(d2);
  LL ans = 0;
  for (int x = -1510; x <= 1510; ++x)
    for (int y = -1510; y <= 1510; ++y) {
      ans += calc(x, y);
    }
  printf( "%lld.%02lld\n" , ans / 4 , (ans % 4) * 25 );
}
