#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, m, r;
int c[100005];
int mx[100005];
int mc[100005];

void init() {
  scanf("%d%d%d", &n, &m, &r);

  for (int i = 1; i <= n; i ++) {
    scanf("%d", &c[i]);
    mx[i] = min(i, r);
    mc[i] = 0;
  }
  for (int i = 0; i < m; i ++) {
    int x, y;
    scanf("%d%d", &x, &y);
    mx[x] = min(mx[x], y);
    mx[y] = min(mx[y], x);
  }
  for (int i = 1; i <= n; i ++) if (i != r) {
    mc[mx[i]] ++;
  }
}

void solve() {
  c[1] --;
  ll ans = 0, cnt = 0;
  for (int i = 1; i <= n; i ++) ans = ans + c[i];
  for (int i = 1; i <= n; i ++) {
    cnt += c[i];
    ll ok = min(cnt, (ll)mc[i]);
    ans -= ok;
    cnt -= ok;
  }
  printf("%lld\n", ans);
}

int main(){
  int T; scanf("%d", &T);
  for (int tc = 1; tc <= T; tc ++) {
    init();
    printf("Case #%d: ", tc);
    solve();
  }
}
