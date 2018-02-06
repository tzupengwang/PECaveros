#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
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
  Tcost solve(){
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
    }
    return mnc;
  }
} flow;
#define N 55
int n , m , lr[ N ][ N ] , ud[ N ][ N ] , iid;
char c[ N ][ N ];
int Id( int cn , int cm ){
  return (cn - 1) * m + cm - 1;
}
int ID_lr( int i , int j ){
  if( lr[ i ][ j ] ) return lr[ i ][ j ];
  flow.addEdge( iid , flow.t , 1 , 0 );
  return lr[ i ][ j ] = iid ++;
}
int ID_ud( int i , int j ){
  if( ud[ i ][ j ] ) return ud[ i ][ j ];
  flow.addEdge( iid , flow.t , 1 , 0 );
  return ud[ i ][ j ] = iid ++;
}
int main(){
  scanf( "%d%d" , &n , &m );
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%s" , c[ i ] + 1 );
  flow.init( n * m * 4 );
  iid = n * m;
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= m ; j ++ ){
      int lcst = 0 , rcst = 0;
      int ucst = 0 , dcst = 0;
      if( c[ i ][ j ] == '<' ){
        rcst = 2;
        ucst = dcst = 1;
      }
      if( c[ i ][ j ] == '>' ){
        lcst = 2;
        ucst = dcst = 1;
      }
      if( c[ i ][ j ] == '^' ){
        dcst = 2;
        lcst = rcst = 1;
      }
      if( c[ i ][ j ] == 'v' ){
        ucst = 2;
        lcst = rcst = 1;
      }
      flow.addEdge( flow.s , Id( i , j ) , 1 , 0 );
      flow.addEdge( Id( i , j ) , ID_lr( i , j - 1 ) , 1 , lcst );
      flow.addEdge( Id( i , j ) , ID_lr( i , j     ) , 1 , rcst );
      flow.addEdge( Id( i , j ) , ID_ud( i - 1 , j ) , 1 , ucst );
      flow.addEdge( Id( i , j ) , ID_ud( i     , j ) , 1 , dcst );
    }
  printf( "%d\n" , flow.solve() );
}
