#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = 1000000007;
struct Int{
  int vl;
  Int( int v = 0 ){ vl = v; }
};
Int operator+( const Int& a , const Int& b ){
  return Int( (a.vl + b.vl) % mod );
}
Int operator-( const Int& a , const Int& b ){
  return Int( (a.vl - b.vl + mod) % mod );
}
Int operator*( const Int& a , const Int& b ){
  return Int( ((LL)a.vl * b.vl) % mod );
}
Int operator^( Int a , LL b ){
  Int ret( 1 );
  while( b ){
    if( b & 1LL ) ret = ret * a;
    a = a * a;
    b >>= 1;
  }
  return ret;
}
Int c[205][205];
Int pw[205][50005];
Int dp[205][205];

int n, m, k;
Int s[205];

void solve() {
  dp[0][0] = Int(1);
  for (int i = 1; i <= k; i ++) {
    for (int j = 0; j <= k; j ++) {
      dp[i][j] = Int(0);
      Int K(0);

      for (int p = 0; p <= j; p ++) {
        dp[i][j] = dp[i][j] + dp[i - 1][j - p] * c[j][p] * (pw[i - 1][K.vl]);

        K = K + Int(n + m - (j - p) * 2);
      }
    }
  }

  Int fc(1);
  for (int i = 0; i <= min(n, m); i ++) {
    s[i] = c[n][i] * c[m][i] * fc * pw[k][(n - i) * (m - i)] * dp[k][i];
    fc = fc * Int(i + 1);
  }

  Int ans;
  for (int i = min(n, m); i >= 0; i --) {
    ans = ans + Int(i + 1) * s[i];

    if (i) {
      for (int j = i - 1; j >= 0; j --) {
        s[j] = s[j] - s[i] * c[i][j];
      }
    }
  }
  printf("%d\n", ans.vl);
}

int main(){
  for (int i = 0; i <= 200; i ++)
    c[i][0] = c[i][i] = Int(1);
  for (int i = 1; i <= 200; i ++)
    for (int j = 1; j < i; j ++)
      c[i][j] = c[i - 1][j] + c[i - 1][j - 1];

  for (int i = 0; i <= 200; i ++) {
    pw[i][0] = Int(1);
    for (int j = 1; j <= 200 * 200; j ++)
      pw[i][j] = pw[i][j - 1] * Int(i);
  }

  int t; scanf("%d", &t);

  for (int kk = 1; kk <= t; kk ++) {
    scanf("%d%d%d", &n, &m, &k);
    printf("Case #%d: ", kk);
    solve();
  }

}
