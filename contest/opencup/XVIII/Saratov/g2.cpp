
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e3+10;
const int M = 2e3+10;
const int K = 70;
typedef double D;

int n, m;
bool fxd[N];
D o[N];
int a[M], b[M], d[M];

void init() {
  char buf[11];
  for (int i = 0; i < n; ++i) {
    scanf("%s", buf);
    if (*buf == '?') {
      fxd[i] = 0;
    } else {
      fxd[i] = 1;
      o[i] = atoi(buf);
    }
  }
  for (int i = 0; i < m; ++i) {
    scanf("%d%d%d", a+i, b+i, d+i);
    a[i]--, b[i]--;
  }
}

struct E {
  int u, v;
  D c;
} es[M+N];
D dis[N];

const D INF = 5e8;
const D eps = 1e-7;

inline bool chk(D T) {
  int tn = n+2;
  int S = tn-2;
  int SS = tn-1;
  fill(dis, dis+tn, INF);
  int ec = 0;
  for (int i = 0; i < m; ++i) {
    int aa = a[i], bb = b[i], dd = d[i];
    if (fxd[aa] && fxd[bb]) {
      if ((D)o[aa] + dd > (D)o[bb] + T + eps) return 0;
    }
    if (fxd[aa] && !fxd[bb]) {
      es[ec++] = {bb, S, 0. - (o[aa] + dd - T)};
    }
    if (!fxd[aa] && fxd[bb]) {
      es[ec++] = {S, aa, (o[bb] + T - dd)};
    }
    if (!fxd[aa] && !fxd[bb]) {
      es[ec++] = {bb, aa, T - dd};
    }
  }
  for (int i = 0; i < SS; ++i) es[ec++] = {SS, i, 0};
  dis[SS] = 0;
  for (int k = 0; k <= tn; ++k) {
    bool upd = 0;
    for (int i = 0; i < ec; ++i) {
      if (dis[es[i].v] > dis[es[i].u] + es[i].c + eps) {
        upd = 1;
        dis[es[i].v] = dis[es[i].u] + es[i].c;
      }
    }
    if (k == tn and upd) return 0;
  }
  for (int i = 0; i < n; ++i) if (!fxd[i]) o[i] = dis[i];
  return 1;
}

void solve() {
  D l = 0, r = 1e7+10;
  for (int i = 0; i < K; ++i) {
    D mid = (l+r) * 0.5;
    if (chk(mid)) r = mid;
    else l = mid;
  }
  chk(l);
  printf("%.9f\n", l);
  for (int i = 0; i < n; ++i) printf("%.9f%c", o[i], " \n"[i+1==n]);
}

int main(){
  while (scanf("%d%d", &n, &m) == 2) {
    init();
    solve();
  }
}
