#define SOURCE 0
#define SINK 1
const unsigned int inf=4000000000u;
int n,m,deg[MAXN],adj[MAXN][MAXN];
unsigned int res[MAXN][MAXN],cap[MAXN][MAXN];
int nei[MAXN],gdeg[MAXN],gadj[MAXN][MAXN];
unsigned int gres[MAXN][MAXN];
unsigned int cut[MAXN][MAXN];
unsigned int cutarr[MAXN*MAXN];
int cutn,ql,qr,que[MAXN],pred[MAXN];
unsigned int aug[MAXN];
bool cutset[MAXN];
int visited[MAXN],visid=0;
inline void augment(int src,int sink) {
  int v=sink; unsigned a=aug[sink];
  while(v!=src) {
    res[pred[v]][v]-=a;
    res[v][pred[v]]+=a;
    v=pred[v];
  }
}
inline bool bfs(int src,int sink) {
  int i,v,u; ++visid;
  ql=qr=0; que[qr++]=src;
  visited[src]=visid; aug[src]=inf;
  while(ql<qr) {
    v=que[ql++];
    for(i=0;i<deg[v];i++) {
      u=adj[v][i];
      if(visited[u]==visid||res[v][u]==0) continue;
      visited[u]=visid; pred[u]=v;
      aug[u]=min(aug[v],res[v][u]);
      que[qr++]=u;
      if(u==sink) return 1;
    }
  }
  return 0;
}
void dfs_src(int v) {
  int i,u;
  visited[v]=visid;
  cutset[v]=SOURCE;
  for(i=0;i<deg[v];i++) {
    u=adj[v][i];
    if(visited[u]<visid&&res[v][u]) dfs_src(u);
  }
}
inline unsigned int maxflow(int src,int sink) {
  int i,j;
  unsigned int f=0;
  for(i=0;i<n;i++) {
    for(j=0;j<deg[i];j++) res[i][adj[i][j]]=cap[i][adj[i][j]];
    cutset[i]=SINK;
  }
  while(bfs(src,sink)) {
    augment(src,sink);
    f+=aug[sink];
  }
  ++visid;
  dfs_src(src);
  return f;
}
inline void gusfield() {
  int i,j;
  unsigned int f;
  for(i=0;i<n;i++) { nei[i]=0; gdeg[i]=0; }
  for(i=1;i<n;i++) {
    f=maxflow(i,nei[i]);
    gres[i][nei[i]]=gres[nei[i]][i]=f;
    gadj[i][gdeg[i]++]=nei[i];
    gadj[nei[i]][gdeg[nei[i]]++]=i;
    for(j=i+1;j<n;j++)
      if(nei[j]==nei[i]&&cutset[j]==SOURCE) nei[j]=i;
  }
}
void dfs(int v,int pred,int src,unsigned int cur) {
  int i,u;
  cut[src][v]=cur;
  for(i=0;i<gdeg[v];i++) {
    u=gadj[v][i];
    if(u==pred) continue;
    dfs(u,v,src,min(cur,gres[v][u]));
  }
}
inline void find_all_cuts() {
  int i;
  cutn=0; gusfield();
  for(i=0;i<n;i++) dfs(i,-1,i,inf);
}
