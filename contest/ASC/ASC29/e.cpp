#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll dp[35][35][2][2];
ll ans[35];

int main(){
#ifdef ONLINE_JUDGE
  freopen( "permutominoes.in" , "r" , stdin );
  freopen( "permutominoes.out" , "w" , stdout );
#endif
  memset(dp, 0, sizeof dp);
  dp[1][1][0][0] = 1;

  for (int i = 1; i <= 29; i ++) {
    ll tmp = 0;
    for (int j = 1; j <= i; j ++) {
      for (int lf = 0; lf <= 1; lf ++) {
        for (int rf = 0; rf <= 1; rf ++) if (dp[i][j][lf][rf]) {
          tmp += dp[i][j][lf][rf];
          for (int k = 1; k <= j; k ++) {
            dp[i + 1][k][1][rf] += dp[i][j][lf][rf];
          }
          if (lf == 0) {
            dp[i + 1][j + 1][0][rf] += dp[i][j][lf][rf];
          }
          for (int k = 1; k <= j; k ++) {
            dp[i + 1][k][lf][1] += dp[i][j][lf][rf];
          }
          if (rf == 0) {
            dp[i + 1][j + 1][lf][0] += dp[i][j][lf][rf];
          }
        }
      }
    }
    ans[i] = tmp;
  }
  int n;
  scanf("%d", &n);
  printf("%lld\n", ans[n - 1]);
}
