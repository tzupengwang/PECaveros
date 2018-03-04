#include<bits/stdc++.h>
using namespace std;

typedef long double ld;
typedef long long ll;
typedef pair<ld, ll> ii;

int n;
ld p1, p2, p3, p4;

ld getd() {
  double x;
  scanf("%lf", &x);
  return (ld)x;
}

ll c[25][25];

int main() {
  scanf("%d", &n);
  p1 = getd();
  p2 = getd();
  p3 = getd();
  p4 = getd();

  for (int i = 0; i <= 20; i ++) {
    c[i][0] = c[i][i] = 1;
  }
  for (int i = 0; i <= 20; i ++) {
    for (int j = 1; j < i; j ++)
      c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
  }

  priority_queue<ii, vector<ii>, greater<ii> > pq;

  for (int i = 0; i <= n; i ++) {
    for (int j = 0; j <= n - i; j ++) {
      for (int k = 0; k <= n - i - j; k ++) {
        int l = n - i - j - k;
        ll ws = c[n][i] * c[n - i][j] * c[n - i - j][k];
        ld pos = 1;
        for (int p = 0; p < i; p ++) pos *= p1;
        for (int p = 0; p < j; p ++) pos *= p2;
        for (int p = 0; p < k; p ++) pos *= p3;
        for (int p = 0; p < l; p ++) pos *= p4;
        pq.push(ii(pos, ws));
      }
    }
  }
  //printf("%d\n", pq.size());

  ld ans = 0;
  while (!pq.empty()) {
    ii x = pq.top(); pq.pop();
    if (x.second == 1) {
      if (pq.empty()) break;
      ii y = pq.top(); pq.pop();

      pq.push(ii(x.first + y.first, 1));
      ans += (x.first + y.first);

      y.second --;
      if (y.second) pq.push(y);
    } else {
      pq.push(ii(x.first * 2, x.second / 2));
      ans += (x.first * 2) * (x.second / 2);
      if (x.second & 1)
        pq.push(ii(x.first, 1));
    }
  }
  printf("%.6f\n", (double)ans);
}
