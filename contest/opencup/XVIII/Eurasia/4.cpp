#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> PII;

const int N = 3e3 + 10;
const int M = 55;
const int K = 3e4+10;
const int T = 1e4+10;

int n, m, k, t;
int val[N];
vector<PII> g[N];
vector<PII> app[T];
bool vis[N];
double pr[T][M];
double sum[T][M];
double p[N];
struct XD {
  int u, v, d;
} apps[K];

int main(){
  scanf("%d%d%d%d", &n, &m, &k, &t);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", val+i);
  }
  for (int i = 1; i <= k; ++i) {
    int u, v, d;
    scanf("%d%d%d", &u, &v, &d);
    app[d].push_back({u, v});
    apps[i] = {u, v, d};
  }
  sort(apps+1, apps+1+k, [&](const XD& a, const XD& b) {return a.d < b.d;});
  for (int i = 1; i <= t; ++i) {
    for (int j = 1; j <= m-1; ++j) {
      scanf("%lf", &pr[i][j]);
      sum[i][j] = pr[i][j] + sum[i-1][j];
    }
  }

  int id = -1;
  double ans = 0;
  for (int i = 1; i <= t; ++i) {
    fill(p+1, p+1+n, 1);
    for (int j = 1; j <= k; ++j) {
      int u = apps[j].u;
      int v = apps[j].v;
      int d = apps[j].d;
      if (i < d) break;
      if (v == m) vis[u] = 1;
      else {
        p[u] *= 1 - (sum[i-1][v] - sum[d-1][v]);
      }
    }

    double tmp = 0;
    //printf("day %d\n", i);
    for (int j = 1; j <= n; ++j) {
      if (vis[j]) {
        //printf("  j %d %g\n", j, p[j]);
        tmp += p[j] * val[j];
      }
    }
    if (id == -1 or ans < tmp) {
      id = i;
      ans = tmp;
    }
  }
  printf("%.9f %d\n", ans, id);
}
