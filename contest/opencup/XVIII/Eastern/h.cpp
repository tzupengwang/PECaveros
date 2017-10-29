#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 110;
const int M = 1e5+10;

int n, m, q;
ll d[N][N][N];
ll s[N][N][N];

inline void upd(int x, int y, int z, int a) {
  for (int i = y; i < y+a; ++i) {
    int x1 = i-y+x;
    int x2 = x+a-1;
    int z1 = z;
    int z2 = i-y+z;
    d[i][x1][z1]++;
    d[i][x1][z2+1]--;
    d[i][x2+1][z1]--;
    d[i][x2+1][z2+1]++;
  }
}
inline ll qry(int x, int y, int z, int a) {
  ll ans = 0;
  for (int i = y; i < y+a; ++i) {
    int x1 = i-y+x;
    int x2 = x+a-1;
    int z1 = z;
    int z2 = i-y+z;
    ans +=
    s[i][x2][z2]-
    s[i][x2][z1-1]-
    s[i][x1-1][z2]+
    s[i][x1-1][z1-1];
  }
  return ans;
}

ll a[N][N][N];
void build() {
  for (int y = 1; y <= n; ++y) {
    for (int x = y; x <= n; ++x)
      for (int z = 1; z <= y; ++z) {
        a[y][x][z] = d[y][x][z] + a[y][x-1][z] + a[y][x][z-1] - a[y][x-1][z-1];
      }
  }
  for (int y = 1; y <= n; ++y) {
    for (int x = y; x <= n; ++x)
      for (int z = 1; z <= y; ++z) {
        s[y][x][z] = a[y][x][z] + s[y][x-1][z] + s[y][x][z-1] - s[y][x-1][z-1];
      }
  }
}


int main() {
  scanf("%d%d%d", &n, &m, &q);
  for (int i = 1; i <= m; ++i) {
    int x, y, z, A;
    scanf("%d%d%d%d", &x, &y, &z, &A);
    upd(x, y, z, A);
  }
  build();
  for (int i = 1; i <= q; ++i) {
    int x, y, z, A;
    scanf("%d%d%d%d", &x, &y, &z, &A);
    ll ans = qry(x, y, z, A);
    printf("%lld\n", ans);
  }
}
