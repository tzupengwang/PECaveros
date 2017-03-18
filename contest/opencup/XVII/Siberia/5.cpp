#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL INF  = 1000000000000LL;
struct MinCostMaxFlow{
  static const int MAXV = 20010;
  struct Edge{
    LL v, cap, w, rev;
    Edge(){}
    Edge(LL t2, LL t3, LL t4, LL t5)
    : v(t2), cap(t3), w(t4), rev(t5) {}
  };
  LL V, s, t;
  vector<Edge> g[MAXV];
  void init(LL n){
    V = n+2;
    s = n+1, t = n+2;
    for(LL i = 1; i <= V; i++) g[i].clear();
  }
  void add_edge(LL a, LL b, LL cap, LL w){
    g[a].push_back(Edge(b, cap, w, (LL)g[b].size()));
    g[b].push_back(Edge(a, 0, -w, (LL)g[a].size()-1));
  }
  LL d[MAXV], id[MAXV], mom[MAXV];
  bool inqu[MAXV];
  LL qu[2000000], ql, qr;
  //the size of qu should be much large than MAXV
  LL solve(){
    LL mxf = 0, mnc = 0;
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
        LL u = qu[ql++];
        inqu[u] = 0;
        for(LL i = 0; i < (LL) g[u].size(); i++){
          Edge &e = g[u][i];
          LL v = e.v;
          if(e.cap > 0 && d[v] > d[u]+e.w){
            d[v] = d[u]+e.w;
            mom[v] = u;
            id[v] = i;
            if(!inqu[v]) qu[++qr] = v, inqu[v] = 1;
          }
        }
      }
      if(mom[t] == -1) break ;
      LL df = INF;
      for(LL u = t; u != s; u = mom[u])
        df = min(df, g[mom[u]][id[u]].cap);
      for(LL u = t; u != s; u = mom[u]){
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
int n , k , t;
#define N 1021
int c[ N ][ N ];
void init(){
  scanf( "%d%d%d" , &n , &k , &t );
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= k + 1 ; j ++ )
      scanf( "%d" , &c[ i ][ j ] );
}
void solve(){
  int bst = 0;
  LL cst = INF;
  for( int i = 1 ; i <= n ; i ++ ){
    flow.init( n + k + 2 );
    for( int j = 1 ; j <= n ; j ++ )
      flow.add_edge( flow.s , j , 1 , 0 );
    for( int j = 1 ; j <= n ; j ++ )
      for( int u = 1 ; u <= k + 1 ; u ++ )
        flow.add_edge( j , n + u , 1 , c[ j ][ u ] );
    flow.add_edge( n + t , flow.t , i , 0 );
    for( int u = 1 ; u <= k ; u ++ ){
      if( u == t ) continue;
      flow.add_edge( n + u , n + k + 2 , i - 1 , 0 );
    }
    flow.add_edge( n + k + 1 , n + k + 2 , n , 0 );
    flow.add_edge( n + k + 2 , flow.t , n - i , 0 );
    LL tcst = flow.solve();
    if( tcst < cst )
      cst = tcst , bst = i;
  }
  int i = bst;
  flow.init( n + k + 2 );
  for( int j = 1 ; j <= n ; j ++ )
    flow.add_edge( flow.s , j , 1 , 0 );
  for( int j = 1 ; j <= n ; j ++ )
    for( int u = 1 ; u <= k + 1 ; u ++ )
      flow.add_edge( j , n + u , 1 , c[ j ][ u ] );
  flow.add_edge( n + t , flow.t , i , 0 );
  for( int u = 1 ; u <= k ; u ++ ){
    if( u == t ) continue;
    flow.add_edge( n + u , n + k + 2 , i - 1 , 0 );
  }
  flow.add_edge( n + k + 1 , n + k + 2 , n , 0 );
  flow.add_edge( n + k + 2 , flow.t , n - i , 0 );
  LL tcst = flow.solve();
  printf( "%lld\n" , tcst );
  for( int j = 1 ; j <= n ; j ++ ){
    int to = 0;
    for( auto e : flow.g[ j ] ){
      if( e.cap == 0 and n + 1 <= e.v and e.v <= n + k + 1 ){
        to = e.v - n;
        break;
      }
    }
    printf( "%d%c" , to , " \n"[ j == n ] );
  }
}
int main(){
  init();
  solve();
}
