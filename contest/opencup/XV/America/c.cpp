#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 2020;
int n, m, ip[N][N];

void upd(LL& a, LL b) {
  if (b != -1) {
    if (a == -1 or b < a) a = b;
  }
}
LL chk(int a[N][N]) {
  static int mx[N][N];
  LL res = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) {
      mx[i][j] = max(mx[i-1][j], mx[i][j-1]);
      if (ip[i][j] != 0) {
        if ((a[i][j]&1) != (ip[i][j]&1)) return -1;
        if (a[i][j] + mx[i][j] > ip[i][j]) return -1;
        mx[i][j] = ip[i][j] - a[i][j];
      }
      res += a[i][j] + mx[i][j];
    }
  return res;
}

int a[4][N][N];
int main(){
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", ip[i]+j);
      a[0][i][j] = 2*i-1 + j - 1;
      a[1][i][j] = 2*i+j-1;
      a[2][i][j] = i+2*(j-1);
      a[3][i][j] = i+1+2*(j-1);
    }
  }
  LL ans = -1;
  upd(ans, chk(a[0]));
  upd(ans, chk(a[1]));
  upd(ans, chk(a[2]));
  upd(ans, chk(a[3]));
  printf("%lld\n", ans);
}
