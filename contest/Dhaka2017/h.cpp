#include <bits/stdc++.h>

using namespace std;

const int N = 30010;

int _cx[N];
int _xpy[N];
int _xmy[N];
int *cx = _cx + 15000;
int *xmy = _xmy+15000;
int *xpy = _xpy+15000;

int n, x[N], y[N];

int main() {
  while (scanf("%d", &n) != EOF and n) {
    fill(cx-1000, cx+11000, 0);
    fill(xmy-1000, xmy+11000, 0);
    fill(xpy-1000, xpy+11000, 0);
    for (int i = 1; i <= n; ++i) {
      scanf("%d%d", x+i, y+i);
      cx[x[i]]++;
      xmy[x[i]-y[i]]++;
      xpy[x[i]+y[i]]++;
    }
    int ans = 0;
    for (int i = -1000; i < 11000; ++i) {
      xmy[i] += xmy[i-1];
      xpy[i] += xpy[i-1];
    }
    for (int i = -600; i < 10600; ++i) {
      int r1 = xpy[i-1];
      int r2 = n - xmy[i];
      int tmp = n - (r1 + r2);
      ans = max(ans, tmp);
    }
    printf("%d\n", ans);
  }
}
