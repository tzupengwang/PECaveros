
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 1e5+10;

int n;
LL cntW, cntB;
LL wgt[2];

void main2() {
  cntW = cntB = 0;
  vector<pair<LL,int>> vs;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    LL x; char tp[2];
    scanf("%lld%s", &x, tp);
    if (*tp == 'W') {
      cntW += x;
      vs.push_back({x, 0});
    } else {
      cntB += x;
      vs.push_back({x, 1});
    }
  }
  if (cntW == 0 or cntB == 0) {
    printf("%lld\n", cntW + cntB);
    return;
  }
  LL g = __gcd(cntW, cntB);
  wgt[0] = -cntB / g;
  wgt[1] = cntW / g;
  LL cur = 0;
  int ans = 0;
  for (auto p: vs) {
    LL x = p.first;
    int tp = p.second;
    if ((-cur) % wgt[tp] == 0) {
      LL y = -cur / wgt[tp];
      if (0 < y and y <= x and cur + y*wgt[tp] == 0) ans++;
    }
    cur += x * wgt[tp];
  }
  printf("%d\n", ans);
}

int main(){
  int tc;scanf("%d", &tc);
  while (tc--) main2();
}
