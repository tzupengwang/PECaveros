#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2020;
int n, m, ip[N][N];
ll pr[N][N];
ll s[N][N];

void upd(ll& a) {
  ll tot = 0;
  for (int i = 1; i <= n; i ++) {
    for (int j = 1; j <= m; j ++) {
      if (ip[i][j] == 0) {
        ll c = max(s[i - 1][j], s[i][j - 1]) + 1;
        if (c % 2 != pr[i][j]) c ++;
        s[i][j] = c;
        tot += c;
      } else {
        if (ip[i][j] % 2 != pr[i][j]) return;
        if (ip[i][j] <= s[i - 1][j] || ip[i][j] <= s[i][j - 1]) return;
        s[i][j] = ip[i][j];
        tot += s[i][j];
      }
    }
  }
  if (a == -1) a = tot;
  else a = min(a, tot);
  return;
}

int main(){
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", ip[i]+j);
    }
  }
  if (n == 1) {
    ll tot = 0;
    for (int i = 1; i <= m; i ++) {
      ll c = ip[1][i - 1] + 1;
      if (ip[1][i] == 0) {
        ip[1][i] = c;
      } else {
        if (ip[1][i] < c) {
          puts("-1");
          return 0;
        }
      }
      tot += ip[1][i];
    }
    printf("%lld\n", tot);
    return 0;
  } else if (m == 1) {
    ll tot = 0;
    for (int i = 1; i <= n; i ++) {
      ll c = ip[i - 1][1] + 1;
      if (ip[i][1] == 0) {
        ip[i][1] = c;
      } else {
        if (ip[i][1] < c) {
          puts("-1");
          return 0;
        }
      }
      tot += ip[i][1];
    }
    printf("%lld\n", tot);
    return 0;
  }

  ll ans = -1;
  for (int i = 1; i <= n; i ++)
    for (int j = 1; j <= m; j ++)
      pr[i][j] = i % 2;
  upd(ans);
  for (int i = 1; i <= n; i ++)
    for (int j = 1; j <= m; j ++)
      pr[i][j] = 1 - (i % 2);
  upd(ans);
  for (int i = 1; i <= n; i ++)
    for (int j = 1; j <= m; j ++)
      pr[i][j] = j % 2;
  upd(ans);
  for (int i = 1; i <= n; i ++)
    for (int j = 1; j <= m; j ++)
      pr[i][j] = 1 - (j % 2);
  upd(ans);
  printf("%lld\n", ans);
}
