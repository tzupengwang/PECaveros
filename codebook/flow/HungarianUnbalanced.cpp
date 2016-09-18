const int nil = -1;
const int inf = 1000000000;
int xn,yn,matched;
int cost[MAXN][MAXN];
bool sets[MAXN]; // whether x is in set S
bool sett[MAXN]; // whether y is in set T
int xlabel[MAXN],ylabel[MAXN];
int xy[MAXN],yx[MAXN]; // matched with whom
int slack[MAXN]; // given y: min{xlabel[x]+ylabel[y]-cost[x][y]} | x not in S
int prev[MAXN]; // for augmenting matching
inline void relabel() {
  int i,delta=inf;
  for(i=0;i<yn;i++) if(!sett[i]) delta=min(slack[i],delta);
  for(i=0;i<xn;i++) if(sets[i]) xlabel[i]-=delta;
  for(i=0;i<yn;i++) {
    if(sett[i]) ylabel[i]+=delta;
    else slack[i]-=delta;
  }
}
inline void add_sets(int x) {
  int i;
  sets[x]=1;
  for(i=0;i<yn;i++) {
    if(xlabel[x]+ylabel[i]-cost[x][i]<slack[i]) {
      slack[i]=xlabel[x]+ylabel[i]-cost[x][i];
      prev[i]=x;
    }
  }
}
inline void augment(int final) {
  int x=prev[final],y=final,tmp;
  matched++;
  while(1) {
    tmp=xy[x]; xy[x]=y; yx[y]=x; y=tmp;
    if(y==nil) return;
    x=prev[y];
  }
}
inline void phase() {
  int i,y,root;
  for(i=0;i<xn;i++) sets[i]=0;
  for(i=0;i<yn;i++) { sett[i]=0; slack[i]=inf; }
  for(root=0;root<xn&&xy[root]!=nil;root++);
  add_sets(root);
  while(1) {
    relabel();
    for(y=0;y<yn;y++) if(!sett[y]&&slack[y]==0) break;
    if(yx[y]==nil) { augment(y); return; }
    else { add_sets(yx[y]); sett[y]=1; }
  }
}
inline int hungarian() {
  int i,j,c=0;
  matched=0;
  // we must have "xn<yn"
  bool swapxy=0;
  if(xn>yn) {
    swapxy=1;
    int mn=max(xn,yn);
    swap(xn,yn);
    for(int i=0;i<mn;i++)
      for(int j=0;j<i;j++)
        swap(cost[i][j],cost[j][i]);
  }
  for(i=0;i<xn;i++) {
    xy[i]=nil;
    xlabel[i]=0;
    for(j=0;j<yn;j++) xlabel[i]=max(cost[i][j],xlabel[i]);
  }
  for(i=0;i<yn;i++) {
    yx[i]=nil;
    ylabel[i]=0;
  }
  for(i=0;i<xn;i++) phase();
  for(i=0;i<xn;i++) c+=cost[i][xy[i]];
  // recover cost matrix (if necessary)
  if(swapxy) {
    int mn=max(xn,yn);
    swap(xn,yn);
    for(int i=0;i<mn;i++)
      for(int j=0;j<i;j++)
        swap(cost[i][j],cost[j][i]);
  }
  // need special recovery if we want more info than matching value
  return c;
}
