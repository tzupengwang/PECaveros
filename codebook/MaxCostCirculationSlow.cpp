/* Tested with: (more tests encouraged)
 *
 * - World Final 2011, pD - Chip Challenge */
class Edge { public:
  int v,u,c;
  Edge() {}
  Edge(int vi,int ui,int ci):v(vi),u(ui),c(ci) {}
};
/* CONSTRUCT */
// res[][] of existing edge have to be correct
int vn,deg[MAXV],adj[MAXV][MAXV];
int res[MAXV][MAXV],cost[MAXV][MAXV];
// all edges should be added into array
int en;
Edge ed[MAXE];
// other contruction depends
/* MAX-COST CIRCULATION */
// be sure to check whether double is necessary
const int inf=100000000;
const double eps=1e-9;
int dist[MAXV][MAXV],pred[MAXV][MAXV];
int cl,carr[MAXV];
inline void bellman_ford() {
  int i,j;
  for(j=0;j<=vn;j++) dist[0][j]=0;
  for(i=0;i<vn;i++) {
    for(j=0;j<vn;j++) dist[i+1][j]=-inf;
    for(j=0;j<en;j++) {
      int v=ed[j].v,u=ed[j].u;
      if(!res[v][u]||dist[i][v]<=-inf) continue;
      if(dist[i][v]+ed[j].c>dist[i+1][u]) {
        dist[i+1][u]=dist[i][v]+ed[j].c;
        pred[i+1][u]=v;
      }
    }
  }
}
inline void trace_cycle(int end) {
  int v=end;
  ++visid;
  cl=0;
  for(int i=vn;;i--) {
    carr[cl++]=v;
    if(visited[v]==visid) break;
    visited[v]=visid;
    v=pred[i][v];
  }
  for(int i=cl-1;i>=0;i--) {
    int u=carr[i],w=carr[i-1];
    res[u][w]--; res[w][u]++;
    curcost+=cost[u][w];
    if(w==v) break;
  }
}
inline bool karp_mmc() {
  int i,k,end;
  double mmc=-inf,avg;
  bellman_ford();
  for(i=0;i<vn;i++) {
    if(dist[vn][i]<=-inf) continue;
    avg=inf;
    for(k=0;k<vn;k++)
      avg=min(avg,(double)(dist[vn][i]-dist[k][i])/(vn-k)
          );
    if(avg>mmc) { mmc=avg; end=i; }
  }
  if(mmc<=eps) return 0;
  trace_cycle(end);
  return 1;
}
inline void find_max_circulation() {
  while(karp_mmc());
}
/* SOLVE (SAMPLE USAGE) */
inline void solve() {
  construct(); // TODO
  find_max_circulation();
}
