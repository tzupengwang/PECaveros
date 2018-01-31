
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double D;
const int N = 1e5+10;
const int MOD = 1e9+9;
const D INF = 1e9;

inline int mul(LL a, int b) {
  a *= b;
  return a >= MOD? a%MOD: a;
}

inline int pw(int a, int b) {
  int res = 1;
  for (; b; b >>= 1) {
    if (b&1) res = mul(res, a);
    a = mul(a, a);
  }
  return res;
}

int n;
int m;
int ps[N];
bool notp[N];
D logp[N];

void predo() {
  for (int i = 2; i < N; ++i) if (!notp[i]) {
    if (i%2) {
      m++;
      ps[m] = i;
      logp[m] = log(i);
    }
    for (int j = i+i; j < N; j += i) notp[j] = 1;
  }
}

D dp[22][N];
int prv[22][N];

inline void upd(int i, int j, int e1) {
  D tmp = dp[i-1][j/e1] + (e1-1) * logp[i];
  if (tmp < dp[i][j]) {
    dp[i][j] = tmp;
    prv[i][j] = e1;
  }
}

int main(){
  predo();
  scanf("%d", &n);
  if (n == 1) return puts("1"), 0;
  fill(dp[0], dp[0]+n+1, INF);
  dp[0][1] = 0;
  for (int i = 1; i <= 16; ++i) {
    fill(dp[i], dp[i]+n+1, INF);
    for (int e1 = 1; e1 <= n; e1++) {
      for (int j = e1; j <= n; j += e1)
        upd(i, j, e1);
    }
  }
  int ans = 1;
  int cur = n;
  for (int i = 16; i >= 1; --i) {
    int e1 = prv[i][cur];
    ans = mul(ans, pw(ps[i], e1-1));
    cur /= e1;
  }
  cout << ans << endl;
}
