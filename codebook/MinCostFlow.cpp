/*
  A template for Min Cost Max Flow
  tested with TIOJ 1724
*/

#include <bits/stdc++.h>

using namespace std;

struct MinCostMaxFlow
{
  static const int MAXV = 20010;
  static const int INF  = 1000000000;
  struct Edge
  {
    int v, cap, w, rev;
    Edge(){}
    Edge(int t2, int t3, int t4, int t5) 
    : v(t2), cap(t3), w(t4), rev(t5) {}
  };
  int V, s, t;
  vector<Edge> g[MAXV];
  void init(int n)
  {
    V = n+2;
    s = n+1, t = n+2;
    for(int i = 1; i <= V; i++) g[i].clear();
  }
  void addEdge(int a, int b, int cap, int w)
  {
    //printf("addEdge %d %d %d %d\n", a, b, cap, w);
    g[a].push_back(Edge(b, cap, w, (int) g[b].size()));
    g[b].push_back(Edge(a, 0, -w, ((int) g[a].size()) - 1));
  }
  int d[MAXV], id[MAXV], mom[MAXV];
  bool inqu[MAXV];
  int qu[2000000], ql, qr;//the size of qu should be much large than MAXV
  int mncmxf()
  {
    int mxf = 0, mnc = 0;
    while(1)
    {
      fill(d+1, d+1+V, -INF);
      fill(inqu+1, inqu+1+V, 0);
      fill(mom+1, mom+1+V, -1);
      mom[s] = s;
      d[s] = 0;
      ql = 1, qr = 0;
      qu[++qr] = s;
      inqu[s] = 1;
      while(ql <= qr)
      {
        int u = qu[ql++];
        inqu[u] = 0;
        for(int i = 0; i < (int) g[u].size(); i++)
        {
          Edge &e = g[u][i];
          int v = e.v;
          if(e.cap > 0 && d[v] < d[u]+e.w)// for min cost : d[v] > d[u]+e.w
          {
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
      for(int u = t; u != s; u = mom[u])
      {
        Edge &e = g[mom[u]][id[u]];
        e.cap             -= df;
        g[e.v][e.rev].cap += df;
      }
      //printf("mxf %d mnc %d\n", mxf, mnc);
      mxf += df;
      mnc += df*d[t];
      //printf("mxf %d mnc %d\n", mxf, mnc);
    }
    return mnc;
  }
} flow;

const int MAXN = 110;
const int MAXM = 10010;

struct Edge
{
  int v, c, id;
  Edge(){}
  Edge(int t1, int t2, int t3) : v(t1), c(t2), id(t3) {}
};

int n, m;
vector<Edge> g[MAXN];
int mom[MAXN], in[MAXN], out[MAXN], stamp;
Edge toMom[MAXN];

void dfs(int u, int p)
{
  mom[u] = p;
  in[u] = ++stamp;
  for(Edge& e:g[u]) if(e.v != p)
  {
    toMom[e.v] = e;
    dfs(e.v, u);
  }
  out[u] = ++stamp;
}

int main()
{
  scanf("%d%d", &n, &m);
  flow.init(m+5);
  for(int i = 1; i <= n-1; i++)
  {
    flow.addEdge(flow.s, i, 1, 0);
    flow.addEdge(i, m+1, 1, 0);
    int u, v, c;
    scanf("%d%d%d", &u, &v, &c);
    g[u].push_back(Edge(v, c, i));
    g[v].push_back(Edge(u, c, i));
  }
  flow.addEdge(m+1, flow.t, n-1, 0);
  dfs(1, -1);
  for(int i = n; i <= m; i++)
  {
    flow.addEdge(i, flow.t, 1, 0);
    int u, v, c;
    scanf("%d%d%d", &u, &v, &c);
    while(!(in[u] <= in[v] && out[v] <= out[u]))
    {
      Edge &e = toMom[u];
      if(c < e.c)
        flow.addEdge(e.id, i, 1, e.c-c);
      u = mom[u];
    }
    while(v != u)
    {
      Edge &e = toMom[v];
      if(c < e.c)
        flow.addEdge(e.id, i, 1, e.c-c);
      v = mom[v];
    }
  }
  //printf("JIZZ\n");
  printf("%d\n", flow.mncmxf());
}