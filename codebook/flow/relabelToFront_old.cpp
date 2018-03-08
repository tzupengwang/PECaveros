/* Relabel-to-Front */
// tested with sgu-212 (more testing suggested)
int n,m,layer,src,sink,lvl[MAXN];
int deg[MAXN],adj[MAXN][MAXN];
int res[MAXN][MAXN]; // residual capacity
// graph (i.e. all things above) should be constructed beforehand
list<int> lst; // discharge list
int ef[MAXN],ht[MAXN];
// excess flow, height
int apt[MAXN]; // the next adj index to try push
inline void push(int v,int u) {
  int a=min(ef[v],res[v][u]);
  ef[v]-=a; ef[u]+=a;
  res[v][u]-=a; res[u][v]+=a;
}
inline void relabel(int v) {
  int i,u;
  ht[v]=2*n;
  for(i=0;i<deg[v];i++) {
    u=adj[v][i];
    if(res[v][u]) ht[v]=min(ht[u]+1,ht[v]);
  }
}
inline void initPreflow() {
  int i,u;
  lst.clear();
  for(i=0;i<n;i++) {
    ht[i]=ef[i]=0; apt[i]=0;
    if(i!=src&&i!=sink) lst.push_back(i);
  }
  ht[src]=n;
  for(i=0;i<deg[src];i++) {
    u=adj[src][i];
    ef[u]=res[src][u];
    ef[src]-=ef[u];
    res[u][src]=ef[u];
    res[src][u]=0;
  }
}
inline void discharge(int v) {
  int u;
  while(ef[v]) {
    if(apt[v]==deg[v]) {
      relabel(v);
      apt[v]=0;
      continue;
    }
    u=adj[v][apt[v]];
    if(res[v][u]&&ht[v]==ht[u]+1) push(v,u);
    else apt[v]++;
  }
}
inline void relabelToFront() {
  int oldh,v;
  list<int>::iterator it;
  initPreflow();
  for(it=lst.begin();it!=lst.end();it++) {
    v=*it; oldh=ht[v]; discharge(v);
    if(ht[v]>oldh) {
      lst.push_front(v);
      lst.erase(it);
      it=lst.begin();
    }
  }
}
