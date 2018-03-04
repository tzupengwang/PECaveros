#include<bits/stdc++.h>
using namespace std;

typedef long double ld;

int W, H, n;

bool ok(ld x1, ld c) {
  ld lst = 0, now = x1;
  for (int i = 2; i <= n + 1; i ++) {
    ld nxt = now / c - lst;
    lst = now;
    now = nxt;
  }
  return now <= W;
}

int main() {
  scanf("%d%d%d", &W, &H, &n);

  ld c = (W * W - H * H) / (2. * W * W);

  ld lw = 0, hg = W;
  for (int k = 0; k < 40; k ++) {
    ld md = (lw + hg) / 2;

    if (ok(md, c)) lw = md;
    else hg = md;
  }
  //printf("%.6f\n", (double)lw);

  ld now = lw, lst = 0;

  vector<ld> xs;
  xs.push_back(now);
  for (int i = 2; i <= n; i ++) {
    ld nxt = now / c - lst;
    xs.push_back(nxt);

    lst = now; now = nxt;
  }

  ld ans = (double)(W + H) * (W + H) / 4;
  for (ld x: xs) ans += x * x / 2;
  for (int i = 0; i < n - 1; i ++)
    ans -= c * xs[i] * xs[i + 1];
  ans -= c * xs[n - 1] * W;
  printf("%.6f\n", (double)ans);
  for (int i = 0; i < min(10, n); i ++)
    printf("%.7f\n", (double)xs[i]);
}
