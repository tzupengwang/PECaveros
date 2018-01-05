#include <bits/stdc++.h>

using namespace std;

#define double long double

typedef double D;
typedef long long ll;
typedef pair<int, int> pii;

const int N = 1010;
const int M = 1e5+10;
const double inf = 1e18;
const double eps = 1e-6;

#define PB push_back
#define ALL(c) (c).begin(), (c).end()
#define SZ(c) ((int)(c).size())
#define FZ(c) memset((c), 0, sizeof (c))
/* minimum mean cycle O(VE) */
struct MMC{
#define MAXE 101010
#define MAXN 1021
  struct Edge {
    int v,u;
    double c;
  };
  int n, m, prv[MAXN][MAXN], prve[MAXN][MAXN], vst[MAXN];
  Edge e[MAXE];
  vector<int> edgeID, cycle, rho;
  double d[MAXN][MAXN];
  void init( int _n ){
    n = _n; m = 0;
  }
  void add_edge( int vi , int ui , double ci ){
    e[ m ++ ] = { vi , ui , (double)ci }; 
  }
  void bellman_ford() {
    for(int i=0; i<n; i++) d[0][i]=0;
    for(int i=0; i<n; i++) {
      fill(d[i+1], d[i+1]+n, inf);
      for(int j=0; j<m; j++) {
        int v = e[j].v, u = e[j].u;
        if(d[i][v]<inf && d[i+1][u]>d[i][v]+e[j].c) {
          d[i+1][u] = d[i][v]+e[j].c;
          prv[i+1][u] = v;
          prve[i+1][u] = j;
        }
      }
    }
  }
  double solve(){
    // returns inf if no cycle, mmc otherwise
    double mmc=inf;
    int st = -1;
    bellman_ford();
    for(int i=0; i<n; i++) {
      double avg=-inf;
      for(int k=0; k<n; k++) {
        if(d[n][i]<inf-eps)	avg=max(avg,(d[n][i]-d[k][i])/(n-k));
        else avg=max(avg,inf);
      }
      if (avg < mmc) tie(mmc, st) = tie(avg, i);
    }
    FZ(vst); edgeID.clear(); cycle.clear(); rho.clear();
    for (int i=n; !vst[st]; st=prv[i--][st]) {
      vst[st]++;
      edgeID.PB(prve[i][st]);
      rho.PB(st);
    }
    while (vst[st] != 2) {
      int v = rho.back(); rho.pop_back();
      cycle.PB(v);
      vst[v]++;
    }
    reverse(ALL(edgeID));
    edgeID.resize(SZ(cycle));
    return mmc;
  }
} mmc;

int n, m;
vector<pii> g[N];
D d[N];

bool nocyc;
int vis[N];

void dfs(int u) {
  vis[u] = 1;
  for (auto e: g[u]) {
    int v = e.first;
    if (vis[v] == 1) {
      nocyc = 0;
      return;
    }
    if (vis[v] == 0) dfs(v);
  }
  vis[u] = 2;
}

bool iii() {
  nocyc = 1;
  for (int i = 1; i <= n; ++i) if (!vis[i]) dfs(i);
  return nocyc;
}

int main() {
  scanf("%d%d", &n, &m);
  mmc.init(n);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    g[u].push_back({v, w});
    mmc.add_edge(u-1, v-1, w);
  }
  if (iii()) {
    puts("+inf");
    return 0;
  }
  double ans = mmc.solve();
  mmc.init(n);
  for (int i = 1; i <= n; ++i) {
    for (auto e: g[i]) {
      mmc.add_edge(i-1, e.first-1, (double)e.second - ans);
    }
  }
  mmc.bellman_ford();
  double minw = inf;
  for (int k = 0; k <= n; ++k) {
    for (int i = 1; i <= n; ++i)
      d[i] = min(d[i], mmc.d[k][i-1]);
  }
  for (int i = 1; i <= n; ++i)
    for (auto e: g[i]) {
      minw = min(minw, d[i] + e.second - d[e.first]);
    }
  assert(fabs(minw - ans) < eps);
  printf("%.18LF\n", minw);
  for (int i = 1; i <= n; ++i) printf("%.18LF%c", d[i], " \n"[i==n]);
}
