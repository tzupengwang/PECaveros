/* Highest-Label Preflow Push Algorithm */
// tested with sgu-212 (more testing suggested)
int n,m,src,sink;
int deg[MAXN],adj[MAXN][MAXN],res[MAXN][MAXN]; // residual capacity
// graph (i.e. all things above) should be constructed beforehand
int ef[MAXN],ht[MAXN]; // excess flow, height
int apt[MAXN]; // the next adj index to try push
int htodo; // highest label to check with
int hcnt[MAXN*2]; // number of nodes with height h
queue<int> ovque[MAXN*2]; // used to implement highest-label selection
bool inque[MAXN];
inline void push(int v,int u) {
  int a=min(ef[v],res[v][u]);
  ef[v]-=a; ef[u]+=a;
  res[v][u]-=a; res[u][v]+=a;
  if(!inque[u]) {
    inque[u]=1;
    ovque[ht[u]].push(u);
  }
}
inline void relabel(int v) {
  int i,u,oldh;
  oldh=ht[v]; ht[v]=2*n;
  for(i=0;i<deg[v];i++) {
    u=adj[v][i];
    if(res[v][u]) ht[v]=min(ht[u]+1,ht[v]);
  }
  // gap speedup
  hcnt[oldh]--; hcnt[ht[v]]++;
  if(0<oldh&&oldh<n&&hcnt[oldh]==0) {
    for(i=0;i<n;i++) {
      if(ht[i]>oldh&&ht[i]<n) {
        hcnt[ht[i]]--;
        hcnt[n]++;
        ht[i]=n;
      }
    }
  }
  // update queue
  htodo=ht[v]; ovque[ht[v]].push(v); inque[v]=1;
}
inline void initPreflow() {
  int i,u;
  for(i=0;i<n;i++) {
    ht[i]=ef[i]=0; apt[i]=0; inque[i]=0;
  }
  ht[src]=n;
  for(i=0;i<deg[src];i++) {
    u=adj[src][i];
    ef[u]=res[src][u];
    ef[src]-=ef[u];
    res[u][src]=ef[u];
    res[src][u]=0;
  }
  htodo=n-1;
  for(i=0;i<2*n;i++) {
    hcnt[i]=0;
    while(!ovque[i].empty()) ovque[i].pop();
  }
  for(i=0;i<n;i++) {
    if(i==src||i==sink) continue;
    if(ef[i]) {
      inque[i]=1; ovque[ht[i]].push(i);
    }
    hcnt[ht[i]]++;
  }
  // to ensure src & sink is never added to queue
  inque[src]=inque[sink]=1;
}
inline void discharge(int v) {
  int u;
  while(ef[v]) {
    if(apt[v]==deg[v]) {
      relabel(v);
      apt[v]=0; continue;
    }
    u=adj[v][apt[v]];
    if(res[v][u]&&ht[v]==ht[u]+1) push(v,u);
    else apt[v]++;
  }
}
inline void hlppa() {
  int v;
  list<int>::iterator it;
  initPreflow();
  while(htodo>=0) {
    if(!ovque[htodo].size()) {
      htodo--; continue;
    }
    v=ovque[htodo].front();
    ovque[htodo].pop();
    inque[v]=0;
    discharge(v);
  }
}
