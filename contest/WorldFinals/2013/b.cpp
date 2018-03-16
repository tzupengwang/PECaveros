#include<bits/stdc++.h>
using namespace std;

double x, p;

int main() {
  scanf("%lf%lf", &x, &p);
  x /= 100;
  x = 1 - x;
  p /= 100;

  double beta = p / (1 - p);
  // slope changes from 1 to x, each step scales by beta
  int M = (int)(log(x) / log(beta));

  double ans = 0;
  for (int hh = 1; hh < M; hh ++) {
    for (int lw = hh - M - 1; lw <= hh - M + 1; lw ++) {
      if (lw >= 0) continue;

      int blk = hh - lw;
      double tp = (1. - pow(beta, blk)) / (1 - beta);
      tp = (hh - lw * x) / tp;
      tp *= (1. - pow(beta, hh)) / (1 - beta);

      double tans = hh - tp;

      ans = max(ans, tans);
    }
  }
  printf("%.10f\n", ans);
}
