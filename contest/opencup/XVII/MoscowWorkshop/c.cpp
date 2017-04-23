#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long LL;
#define N 202020
#define PB push_back
#define SZ(X) ((int)X.size())
struct DisjointSet{
  // save() is like recursive
  // undo() is like return
  int n, fa[ N ], sz[ N ];
  vector< pair<int*,int> > h;
  vector<int> sp;
  void init( int tn ){
    n=tn;
    for( int i = 1 ; i <= n ; i ++ ){
      fa[ i ]=i;
      sz[ i ]=1;
    }
    sp.clear(); h.clear();
  }
  void assign( int *k, int v ){
    h.PB( {k, *k} );
    *k = v;
  }
  void save(){ sp.PB(SZ(h)); }
  void undo(){
    assert(!sp.empty());
    int last=sp.back(); sp.pop_back();
    while( SZ(h)!=last ){
      auto x=h.back(); h.pop_back();
      *x.first = x.second;
    }
  }
  int f( int x ){
    while( fa[ x ] != x ) x = fa[ x ];
    return x;
  }
  void uni( int x , int y ){
    x = f( x ); y = f( y );
    if( x == y ) return;
    if( sz[ x ] < sz[ y ] ) swap( x, y );
    assign( &sz[ x ] , sz[ x ] + sz[ y ] );
    assign( &fa[ y ] , x);
  }
} djs;
struct BccEdge {
  static const int MXN = N;
  struct Edge { int v, eid; };
  int n,m,step,par[MXN],dfn[MXN],low[MXN];
  vector<Edge> E[MXN];
  void init(int _n) {
    n = _n; m = 0;
    for (int i=1; i<=n; i++) E[i].clear();
  }
  void add_edge(int u, int v) {
    E[u].PB({v, m});
    E[v].PB({u, m});
    m++;
  }
  void DFS(int u, int f, int f_eid) {
    par[u] = f;
    dfn[u] = low[u] = step++;
    for (auto it:E[u]) {
      if (it.eid == f_eid) continue;
      int v = it.v;
      if (dfn[v] == -1) {
        DFS(v, u, it.eid);
        low[u] = min(low[u], low[v]);
      } else {
        low[u] = min(low[u], dfn[v]);
      }
    }
  }
  void solve() {
    step = 0;
    memset(dfn, -1, sizeof(int)*(n+1));
    for (int i=1; i<=n; i++) {
      if (dfn[i] == -1) DFS(i, i, -1);
    }
    djs.init(n);
    for (int i=1; i<=n; i++) {
      if (low[i] < dfn[i]) djs.uni(i, par[i]);
    }
  }
} graph;
int n , m;
void init(){
#ifdef LOCAL
  n = 200000; m = n - 1;
  graph.init( n );
  for( int i = 1 ; i < n ; i ++ )
    graph.add_edge( i , i + 1 );
#else
  scanf( "%lld%lld" , &n , &m );
  graph.init( n );
  while( m -- ){
    int ai , bi; scanf( "%lld%lld" , &ai , &bi );
    graph.add_edge( ai , bi );
  }
#endif
}
vector< pair<int, pair<int,int> > > g[ N ];
bool vst[ N ] , ok[ N ];
LL clr[ N ] , cnt[ N ][ 2 ];
bool nok;
void go( int now , int tclr ){
  clr[ now ] = tclr;
  vst[ now ] = true;
  cnt[ djs.f( now ) ][ tclr ] ++;
  for( auto e : graph.E[ now ] ){
    if( djs.f( now ) != djs.f( e.v ) )
      continue;
    if( vst[ e.v ] ){
      if( tclr == clr[ e.v ] )
        nok = true;
      continue;
    }
    go( e.v , 1 - tclr );
  }
}
LL ans[ 2 ];
inline LL C2( LL a ){
  return a * ( a - 1 ) / 2;
}
LL dp[ N ][ 2 ];
bool vst2[ N ];
void DP( int now , int prt ){
  vst2[ now ] = true;
  dp[ now ][ 0 ] = cnt[ now ][ 0 ];
  dp[ now ][ 1 ] = cnt[ now ][ 1 ];
  for( auto e : g[ now ] ){
    int son = e.first;
    int fr = e.second.first;
    int to = e.second.second;
    if( son == prt ) continue;
    DP( son , now );
    for( int i = 0 ; i < 2 ; i ++ )
      for( int j = 0 ; j < 2 ; j ++ )
        ans[ ( i + j + 1 + clr[ fr ] + clr[ to ] ) & 1 ]
          += dp[ son ][ i ] * dp[ now ][ j ];
    for( int i = 0 ; i < 2 ; i ++ )
      dp[ now ][ ( i + clr[ fr ] + clr[ to ] + 1 ) & 1 ] += dp[ son ][ i ];
  }
}
vector<int> gg[ N ];
void solve(){
  graph.solve();
  for( int i = 1 ; i <= n ; i ++ )
    if( not vst[ i ] ){
      nok = false;
      go( i , 0 );
      ok[ djs.f( i ) ] = not nok;
    }
  for( int i = 1 ; i <= n ; i ++ )
    for( auto e : graph.E[ i ] ){
      if( djs.f( i ) == djs.f( e.v ) and not ok[ djs.f( i ) ] )
        continue;
      gg[ i ].push_back( e.v );
    }
  graph.init( n );
  for( int i = 1 ; i <= n ; i ++ )
    for( auto nxt : gg[ i ] )
      if( nxt > i )
        graph.add_edge( i , nxt );
  graph.solve();
  for( int i = 1 ; i <= n ; i ++ ){
    vst[ i ] = false;
    cnt[ i ][ 0 ] = cnt[ i ][ 1 ] = 0;
    g[ i ].clear();
    clr[ i ] = 0;
    gg[ i ].clear();
    vst2[ i ] = false;
    dp[ i ][ 0 ] = dp[ i ][ 1 ] = 0;
    ok[ i ] = false;
  }
  for( int i = 1 ; i <= n ; i ++ )
    for( auto e : graph.E[ i ] )
      if( djs.f( i ) != djs.f( e.v ) )
        g[ djs.f( i ) ].push_back( { djs.f( e.v ) , { i , e.v } } );
  ans[ 0 ] = ans[ 1 ] = 0;
  for( int i = 1 ; i <= n ; i ++ )
    if( not vst[ i ] ){
      nok = false;
      go( i , 0 );
      ok[ djs.f( i ) ] = not nok;
      assert( ok[ djs.f( i ) ] );
      ans[ 0 ] += C2( cnt[ djs.f( i ) ][ 0 ] ) +
                  C2( cnt[ djs.f( i ) ][ 1 ] );
      ans[ 1 ] += cnt[ djs.f( i ) ][ 0 ] *
                  cnt[ djs.f( i ) ][ 1 ];
    }
  for( int i = 1 ; i <= n ; i ++ )
    if( djs.f( i ) == i and not vst2[ i ] )
      DP( i , i );
  printf( "%lld %lld\n" , ans[ 0 ] , ans[ 1 ] );
}
int32_t main(){
  init();
  solve();
}
