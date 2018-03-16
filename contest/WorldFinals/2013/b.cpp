#include<bits/stdc++.h>
using namespace std;

double x, p;
double pos[100005];
bool vlp[100005];
double pp[100005];
double neg[100005];
bool vln[100005];
double pn[100005];

int main() {
  scanf("%lf%lf", &x, &p);
  x /= 100;
  x = 1 - x;
  p /= 100;

  for (int i = 0; i < 100000; i ++) {
    pos[i] = i;
    neg[i] = -(double)i * x;
  }

  double alpha = (1 - p) / p;
  double beta = p / (1 - p);
  int M = (int)(-log(x) / log(alpha));

  int lw = 1, hh = M;
  while (lw + 1 < hh) {
    int md = (lw + hh) / 2;
    double tp = (1. - pow(beta, M)) / (1 - beta);
    double tg = x * (M - md) + md;

    if (tp > tg) lw = md;
    else hh = md;
  }
  //printf("lw = %d\n", lw);

  double vl = lw - (1. - pow(beta, lw)) / (1 - beta);

  int m1 = 0, m2 = 0;
  neg[0] = pos[0] = vl;
  for (int t = 0; t < 10000; t ++) {
    if (vlp[1] && vln[1]) {
      double lst = pos[0];
      double tmp = max(pos[0], p * pos[1] + (1 - p) * neg[1]);
      double k = (tmp - lst) * 2 / (1 - p * (1 - p)) - (tmp - lst);
      neg[0] = pos[0] = lst + k;
    } else {
      double tmp = max(pos[0], p * pos[1] + (1 - p) * neg[1]);
      neg[0] = pos[0] = tmp;
    }
    //printf("%.5f\n", pos[0]);

    for (int i = 1; ; i ++) {
      if (vln[i]) {
        neg[i] = p * neg[i - 1] + (1 - p) * pn[i];
        neg[i] += (neg[i + 1] - pn[i]) * (1 - p) / (1 - p * (1 - p));
        pn[i] = neg[i + 1];
      } else if (neg[i] < p * neg[i - 1] + (1 - p) * neg[i + 1]) {
        neg[i] = p * neg[i - 1] + (1 - p) * neg[i + 1];
        m1 = max(m1, i);
        vln[i] = true;
        pn[i] = neg[i + 1];
      } else break;
    }
    for (int i = 1; ; i ++) {
      if (vlp[i]) {
        pos[i] = p * pp[i] + (1 - p) * pos[i - 1];
        pos[i] += (pos[i + 1] - pp[i]) * p / (1 - p * (1 - p));
        pp[i] = pos[i + 1];
      } else if (pos[i] < p * pos[i + 1] + (1 - p) * pos[i - 1]) {
        pos[i] = p * pos[i + 1] + (1 - p) * pos[i - 1];
        m2 = max(m2, i);
        vlp[i] = true;
        pp[i] = pos[i + 1];
      } else break;
    }
  }
  //printf("%d %d %d\n", m1, m2, M);
  //printf("%.10f\n", vl);
  printf("%.10f\n", pos[0]);
}
