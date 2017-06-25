#include <bits/stdc++.h>

using namespace std;

struct MinCostMaxFlow{
  static const int MAXV = 2e4+10;
  static const int INF  = 1e9;
  struct Edge{
    int v, cap, w, rev;
    Edge(){}
    Edge(int t2, int t3, int t4, int t5)
    : v(t2), cap(t3), w(t4), rev(t5) {}
  };
  int V, s, t;
  vector<Edge> g[MAXV];
  void init(int n){
    V = n+2;
    s = n+1, t = n+2;
    for(int i = 1; i <= V; i++) g[i].clear();
  }
  void addEdge(int a, int b, int cap, int w){
    g[a].push_back(Edge(b, cap, w, (int)g[b].size()));
    g[b].push_back(Edge(a, 0, -w, (int)g[a].size()-1));
  }
  int d[MAXV], id[MAXV], mom[MAXV];
  bool inqu[MAXV];
  int qu[2000000], ql, qr;
  //the size of qu should be much large than MAXV
  pair<int,int> mncmxf(){
    int mxf = 0, mnc = 0;
    while(1){
      fill(d+1, d+1+V, INF);
      fill(inqu+1, inqu+1+V, 0);
      fill(mom+1, mom+1+V, -1);
      mom[s] = s;
      d[s] = 0;
      ql = 1, qr = 0;
      qu[++qr] = s;
      inqu[s] = 1;
      while(ql <= qr){
        int u = qu[ql++];
        inqu[u] = 0;
        for(int i = 0; i < (int) g[u].size(); i++){
          Edge &e = g[u][i];
          int v = e.v;
          if(e.cap > 0 && d[v] > d[u]+e.w){
            d[v] = d[u]+e.w;
            mom[v] = u;
            id[v] = i;
            if(!inqu[v]) qu[++qr] = v, inqu[v] = 1;
          }
        }
      }
      if(mom[t] == -1) break ;
      int df = INF;
      for(int u = t; u != s; u = mom[u])
        df = min(df, g[mom[u]][id[u]].cap);
      for(int u = t; u != s; u = mom[u]){
        Edge &e = g[mom[u]][id[u]];
        e.cap             -= df;
        g[e.v][e.rev].cap += df;
      }
      mxf += df;
      mnc += df*d[t];
    }
    return make_pair(mnc, mxf);
  }
} flow;

const int N = 22;
const int K = 22;
const int M = 333;
const int Q = 333;

int n, k, c, m, q;
struct XD {int a, b, c;};
XD e[M];
int a[Q][K];

inline long long calc(int l, int r) {
  static int need[K];
  fill(need, need+k+1, 0);
  for (int i = l; i <= r; i++)
    for (int j = 1; j <= k; j++)
      need[j] += a[i][j];
  flow.init(n+k);
  int task = 0;
  for (int i = 1; i <= k; i++) if (need[i]) {
    flow.addEdge(flow.s, i, 1, 0);
    task++;
  }
  for (int i = 1; i <= n; i++)
    flow.addEdge(k+i, flow.t, 1, 0);
  for (int i = 0; i < m; i++) {
    flow.addEdge(e[i].b, e[i].a+k, 1, e[i].c*need[e[i].b]);
  }
  auto p = flow.mncmxf();
  if (p.second == task) return p.first;
  return 1e12;
}

long long dp[Q];

int main() {
  cin >> n >> k >> c >> m;
  for ( int i = 0 ; i < m ; i++ ) {
    cin >> e[i].a >> e[i].b >> e[i].c;
  }
  cin >> q;
  for (int i = 1; i <= q; i++)
    for (int j = 1; j <= k; j++)
      cin >> a[i][j];
  dp[0] = 0;
  for (int i = 1; i <= q; i++) {
    dp[i] = c+calc(1,i);
    for (int j = 2; j <= i; j++) {
      int tmp = calc(j, i);
      dp[i] = min(dp[i], dp[j-1]+c+tmp);
    }
  }
  cout << dp[q] << endl;
}
