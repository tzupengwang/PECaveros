#include <bits/stdc++.h>

using namespace std;

struct MinCostMaxFlow{
  static const int MAXV = 20010;
  static const int INF  = 1000000000;
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
  pair<int, int> mncmxf(){
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
const int N = 333;
const int K = 333;

int n, k;
int ans[N];

int main() {
#ifdef ONLINE_JUDGE
  freopen("sat.in", "r", stdin);
  freopen("sat.out", "w", stdout);
#endif
  set<int> used;
  cin >> n >> k;
  flow.init(k+n+n+n+1);
  int D = k+n+n+n+1;
  for (int i = 1; i <= k; ++i) {
    flow.addEdge(i, flow.t, 1, 0);
    int sz;
    cin >> sz;
    for (int j = 0; j < sz; ++j) {
      int x; cin >> x;
      if (0 < x) {
        flow.addEdge(k+x, i, 1, 0);
        used.insert(k+x);
      }
      else {
        flow.addEdge(k+n+(-x), i, 1, 0);
        used.insert(k+n-x);
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (!used.count(k+i)) flow.addEdge(k+i, D, 1, 0);
    if (!used.count(k+n+i)) flow.addEdge(k+n+i, D, 1, 0);
    flow.addEdge(k+n+n+i, k+i, 1, 0);
    flow.addEdge(k+n+n+i, k+n+i, 1, 0);
    flow.addEdge(flow.s, k+n+n+i, 1, 0);
  }
  flow.addEdge(D, flow.t, N, 1);
  int mxf, mnc;
  tie(mnc, mxf) = flow.mncmxf();
  if (mnc != n-k) {
    puts("NO");
    return 0;
  }
  puts("YES");
  for (int i = 1; i <= n; ++i) {
    for (auto e: flow.g[k+n+n+i]) {
      //printf("%d -> %d %d\n", i, e.v, e.c);
      if (e.cap == 0 && e.v == k+i) {
        ans[i] = 1;
        break;
      }
    }
    printf("%d%c", ans[i], " \n"[i==n]);
  }
}
