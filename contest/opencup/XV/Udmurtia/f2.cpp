
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, Q;
int t[100005], c[100005];
vector<int> gp[105];

bool tagged[100005];
int psum[105][100005];
ll cnt[105];
int cnt2[105];

int main(){
  scanf("%d", &n);
  for (int i = 0; i < n; i ++) {
    scanf("%d%d", &c[i], &t[i]);
    gp[t[i]].push_back(i);

    psum[t[i]][c[i]] ++;
    cnt[t[i]] += c[i];
    cnt2[t[i]] ++;
  }
  for (int i = 1; i <= 100; i ++) {
    for (int j = 1; j <= 100000; j ++)
      psum[i][j] += psum[i][j - 1];
  }

  int ans1 = n, ans2 = n;

  scanf("%d", &Q);
  for (int q = 0; q < Q; q ++) {
    int m; scanf("%d", &m);

    for (int i = 0; i < m; i ++) {
      int x;
      scanf("%d", &x); x --;

      tagged[q - t[x]] = true;
      psum[t[x]][-- c[x]] ++;
      cnt[t[x]] --;

      if (c[x] == 0) ans1 --, cnt2[t[x]] --;
    }
    ll tsum = 0;
    int tsum2 = 0, ps = 0, bad = 0;

    for (int i = 99; i >= 1; i --) {
      if (q >= i && !tagged[q - i]) {
        ps ++;
      }
      tsum += cnt[i + 1];
      tsum2 += cnt2[i + 1];
      if (tsum <= ps) bad = tsum2;
      assert(tsum >= ps);
    }

    int tg = 0;
    ans2 = 0;
    for (int p = 1; p <= 100; p ++) {
      if (p > 1 && q - p + 1 >= 0) {
        if (tagged[q - p + 1]) tg ++;
      }
      int target = min(q, p - 1) - tg;

      ans2 -= psum[p][target];
    }
    ans2 += n;

    printf("%d %d\n", ans1 - bad, ans2);
  }

}
