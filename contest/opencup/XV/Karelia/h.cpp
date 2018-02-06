
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;


const int N = 333;

struct MinCostMaxFlow{
typedef int Tcost;
  static const int MAXV = 20010;
  static const int INFf = 1000000;
  static const Tcost INFc  = 1e9;
  struct Edge{
    int v, cap;
    Tcost w;
    int rev;
    Edge(){}
    Edge(int t2, int t3, Tcost t4, int t5)
    : v(t2), cap(t3), w(t4), rev(t5) {}
  };
  int V, s, t;
  vector<Edge> g[MAXV];
  void init(int n){
    V = n+2;
    s = n+1, t = n+2;
    for(int i = 0; i <= V; i++) g[i].clear();
  }
  void addEdge(int a, int b, int cap, Tcost w){
    g[a].push_back(Edge(b, cap, w, (int)g[b].size()));
    g[b].push_back(Edge(a, 0, -w, (int)g[a].size()-1));
  }
  Tcost d[MAXV];
  int id[MAXV], mom[MAXV];
  bool inqu[MAXV];
  queue<int> q;
  Tcost solve(int n, int m, int cost[N], vector<int> work[N][N], int &T){
    int mxf = 0; Tcost mnc = 0;
    while(1){
      fill(d, d+1+V, INFc);
      fill(inqu, inqu+1+V, 0);
      fill(mom, mom+1+V, -1);
      mom[s] = s;
      d[s] = 0;
      q.push(s); inqu[s] = 1;
      while(q.size()){
        int u = q.front(); q.pop();
        inqu[u] = 0;
        for(int i = 0; i < (int) g[u].size(); i++){
          Edge &e = g[u][i];
          int v = e.v;
          if(e.cap > 0 && d[v] > d[u]+e.w){
            d[v] = d[u]+e.w;
            mom[v] = u;
            id[v] = i;
            if(!inqu[v]) q.push(v), inqu[v] = 1;
          }
        }
      }
      if(mom[t] == -1) break ;
      int df = INFf;
      for(int u = t; u != s; u = mom[u])
        df = min(df, g[mom[u]][id[u]].cap);
      for(int u = t; u != s; u = mom[u]){
        Edge &e = g[mom[u]][id[u]];
        e.cap             -= df;
        g[e.v][e.rev].cap += df;
      }
      mxf += df;
      mnc += df*d[t];
      //printf("f %d c %d\n", mxf, mnc);
      cost[mxf] = mnc;
      for (int i = 1; i <= m; ++i) {
        for (Edge& e: g[i]) if (e.cap == 0 and m+1 <= e.v and e.v <= m+n) {
          work[mxf][e.v-m].push_back(i);
        }
      }
    }
    T = mxf;
    return mnc;
  }
} flow;

int n, m;
char ip[N][N];
int kTk[N];
vector<int> k[N][N];

int main(){
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) scanf("%s", ip[i]+1);
  flow.init(n+m);
  for (int i = 1; i <= m; ++i) {
    flow.addEdge(flow.s, i, 1, 0);
  }
  for (int i = 1; i <= n; ++i) {
    for (int c = 1; c <= m; ++c) {
      flow.addEdge(m+i, flow.t, 1, c*c - (c-1)*(c-1));
    }
  }
  for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) if (ip[i][j] == '1') {
    flow.addEdge(j, m+i, 1, 0);
  }
  int mxT = 0;
  int cst = flow.solve(n, m, kTk, k, mxT);
  //printf("cst %d\n", cst);
  LL mn = 0; int id = mxT;
  for (int i = 1; i <= n; ++i) {
    printf("%d", (int)k[id][i].size());
    sort(k[id][i].begin(), k[id][i].end());
    for (int x: k[id][i]) printf(" %d", x);
    puts("");
  }
}
