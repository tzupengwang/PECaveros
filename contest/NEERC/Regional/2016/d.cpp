#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
struct MinCostMaxFlow{
typedef LL Tcost;
  static const int MAXV = 20010;
  static const int INFf = 1000000;
  static const Tcost INFc  = 10000000000000LL;
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
#define N 1021
int n , k , ms , me;
int s[ N ] , e[ N ] , ee[ N ];
LL ans;
void init(){
  scanf( "%d%d%d%d" , &n , &k , &ms , &me );
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%d" , &s[ i ] );
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%d" , &e[ i ] );
  for( int i = 1 ; i <= n ; i ++ ){
    ans += s[ i ];
    e[ i ] -= s[ i ];
  }
}
void solve(){
  if( k == 1 and ms == 1 ){
    printf( "%lld\n" , ans );
    for( int i = 1 ; i <= n ; i ++ )
      putchar( 'S' );
    puts( "" );
    exit(0);
  }
  if( k == 1 and me == 1 ){
    for( int i = 1 ; i <= n ; i ++ )
      ans += e[ i ];
    printf( "%lld\n" , ans );
    for( int i = 1 ; i <= n ; i ++ )
      putchar( 'E' );
    puts( "" );
    exit(0);
  }
  if( k == 1 and ms == 0 and me == 0 ){
    for( int i = 1 ; i <= n ; i ++ )
      if( e[ i ] > 0 ){
        ee[ i ] = 1;
        ans += e[ i ];
      }
    printf( "%lld\n" , ans );
    for( int i = 1 ; i <= n ; i ++ )
      putchar( "SE"[ ee[ i ] ] );
    puts( "" );
    exit(0);
  }
  int mn = me , mx = k - ms;
  flow.init( n + 2 );
  for( int i = 1 ; i <= k ; i ++ )
    flow.addEdge( flow.s , i , n , 0 );
  for( int i = 1 ; i <= n ; i ++ ){
    flow.addEdge( i , i + 1 , mx - mn , 0 );
    if( i + k <= n )
      flow.addEdge( i , i + k , 1 , -e[ i ] );
    else
      flow.addEdge( i , n + 2 , 1 , -e[ i ] );
  }
  flow.addEdge( n + 1 , n + 2 , mx - mn , 0 );
  flow.addEdge( n + 2 , flow.t , mx , 0 );
  ans -= flow.solve();
  for( int i = 1 ; i <= n ; i ++ )
    for( auto ed : flow.g[ i ] )
      if( ed.cap == 0 and ed.v == (i + k > n ? n + 2 : i + k) )
        ee[ i ] = 1;
  printf( "%lld\n" , ans );
  for( int i = 1 ; i <= n ; i ++ )
    putchar( "SE"[ ee[ i ] ] );
  puts( "" );
}
int main(){
#ifndef LOCAL
  freopen( "delight.in" , "r" , stdin );
  freopen( "delight.out" , "w" , stdout );
#endif
  init();
  solve();
}
