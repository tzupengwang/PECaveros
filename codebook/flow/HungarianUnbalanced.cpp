const int nil = -1;
const int inf = 1000000000;
int xN,yN,matched;
int cost[MAXN][MAXN];
bool sets[MAXN]; // whether x is in set S
bool sett[MAXN]; // whether y is in set T
int xlabel[MAXN],ylabel[MAXN];
int xy[MAXN],yx[MAXN]; // matched with whom
int slack[MAXN]; // given y: min{xlabel[x]+ylabel[y]-cost[x][y]} | x not in S
int preV[MAXN]; // for augmenting matching
inline void relabel() {
  int i,delta=inf;
  for(i=0;i<yN;i++) if(!sett[i]) delta=min(slack[i],delta);
  for(i=0;i<xN;i++) if(sets[i]) xlabel[i]-=delta;
  for(i=0;i<yN;i++) {
    if(sett[i]) ylabel[i]+=delta;
    else slack[i]-=delta;
  }
}
inline void add_sets(int x) {
  int i;
  sets[x]=1;
  for(i=0;i<yN;i++) {
    if(xlabel[x]+ylabel[i]-cost[x][i]<slack[i]) {
      slack[i]=xlabel[x]+ylabel[i]-cost[x][i];
      preV[i]=x;
    }
  }
}
inline void augment(int final) {
  int x=preV[final],y=final,tmp;
  matched++;
  while(1) {
    tmp=xy[x]; xy[x]=y; yx[y]=x; y=tmp;
    if(y==nil) return;
    x=preV[y];
  }
}
inline void phase() {
  int i,y,root;
  for(i=0;i<xN;i++) sets[i]=0;
  for(i=0;i<yN;i++) { sett[i]=0; slack[i]=inf; }
  for(root=0;root<xN&&xy[root]!=nil;root++);
  add_sets(root);
  while(1) {
    relabel();
    for(y=0;y<yN;y++) if(!sett[y]&&slack[y]==0) break;
    if(yx[y]==nil) { augment(y); return; }
    else { add_sets(yx[y]); sett[y]=1; }
  }
}
inline int hungarian() {
  int i,j,c=0;
  matched=0;
  // we must have "xN<yN"
  bool swapxy=0;
  if(xN>yN) {
    swapxy=1;
    int mn=max(xN,yN);
    swap(xN,yN);
    for(i=0;i<mn;i++)
      for(j=0;j<i;j++)
        swap(cost[i][j],cost[j][i]);
  }
  for(i=0;i<xN;i++) {
    xy[i]=nil;
    xlabel[i]=0;
    for(j=0;j<yN;j++) xlabel[i]=max(cost[i][j],xlabel[i]);
  }
  for(i=0;i<yN;i++) {
    yx[i]=nil;
    ylabel[i]=0;
  }
  for(i=0;i<xN;i++) phase();
  for(i=0;i<xN;i++) c+=cost[i][xy[i]];
  // recover cost matrix (if necessary)
  if(swapxy) {
    int mn=max(xN,yN);
    swap(xN,yN);
    for(i=0;i<mn;i++)
      for(j=0;j<i;j++)
        swap(cost[i][j],cost[j][i]);
    for(i = 0 ; i < mn ; i ++)
      swap( xlabel[ i ] , ylabel[ i ] );
  }
  // need special recovery if we want more info than matching value
  return c;
}
