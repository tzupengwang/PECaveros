#include <bits/stdc++.h>
using namespace std;
#define SZ(c) ((int)(c).size())
static const int INF  = 1000000;
struct Edge {
  int v, c, r;
  Edge(int _v, int _c, int _r):
    v(_v), c(_c), r(_r) {}
};
struct Maxflow {
  static const int MAXV = 20010;
  int s, t;
  vector<Edge> G[MAXV*2];
  int iter[MAXV*2], d[MAXV*2], gap[MAXV*2], tot;
  void init(int x) {
    tot = x+2;
    s = x+1, t = x+2;
    for(int i = 0; i <= tot; i++) {
      G[i].clear();
      iter[i] = d[i] = gap[i] = 0;
    }
  }
  void reset(){
    for(int i = 0; i <= tot; i++) 
      iter[i] = d[i] = gap[i] = 0;
  }
  void addEdge(int u, int v, int c) {
    G[u].push_back(Edge(v, c, SZ(G[v]) ));
    G[v].push_back(Edge(u, 0, SZ(G[u]) - 1));
  }
  int dfs(int p, int flow) {
    if(p == t) return flow;
    for(int &i = iter[p]; i < SZ(G[p]); i++) {
      Edge &e = G[p][i];
      if(e.c > 0 && d[p] == d[e.v]+1) {
        int f = dfs(e.v, min(flow, e.c));
        if(f) {
          e.c -= f;
          G[e.v][e.r].c += f;
          return f;
        }
      }
    }
    if( (--gap[d[p]]) == 0) d[s] = tot;
    else {
      d[p]++;
      iter[p] = 0;
      ++gap[d[p]];
    }
    return 0;
  }
  int solve() {
    int res = 0;
    gap[0] = tot;
    for(res = 0; d[s] < tot; res += dfs(s, INF));
    return res;
  }
} flow;
// Max flow with lower/upper bound on edges
// source = 1 , sink = n
#define N 222
#define M (N * N)
int in[ N ] , out[ N ];
int l[ M ] , r[ M ] , a[ M ] , b[ M ];
int n , m;
int ans[ N ][ N ] , ansr[ N ] , ansc[ N ];
int al[ N ][ N ] , rsl[ N ] , csl[ N ];
int ar[ N ][ N ] , rsr[ N ] , csr[ N ];
int R , C;
void solve(){
  flow.init( n );
  for( int i = 0 ; i <= n ; i ++ )
    in[ i ] = out[ i ] = 0;
  for( int i = 0 ; i < m ; i ++ ){
    in[ r[ i ] ] += a[ i ];
    out[ l[ i ] ] += a[ i ];
    flow.addEdge( l[ i ] , r[ i ] , b[ i ] - a[ i ] );
    // flow on edge from l[ i ] to r[ i ] should
    // be in [a[ i ], b[ i ]].
  }
  int nd = 0;
  for( int i = 1 ; i <= n ; i ++ ){
    if( in[ i ] < out[ i ] ){
      flow.addEdge( i , flow.t , out[ i ] - in[ i ] );
      nd += out[ i ] - in[ i ];
    }
    if( out[ i ] < in[ i ] )
      flow.addEdge( flow.s , i , in[ i ] - out[ i ] );
  }
  // original sink to source
  flow.addEdge( n , 1 , INF );
  if( flow.solve() != nd ){
    assert( false );
    // no solution
    return;
  }
  //flow.G[ 1 ].back().c; // source to sink
  flow.G[ 1 ].back().c = flow.G[ n ].back().c = 0;
  // take out super source and super sink
  for( size_t i = 0 ; i < flow.G[ flow.s ].size() ; i ++ ){
    flow.G[ flow.s ][ i ].c = 0;
    Edge &e = flow.G[ flow.s ][ i ];
    flow.G[ e.v ][ e.r ].c = 0;
  }
  for( size_t i = 0 ; i < flow.G[ flow.t ].size() ; i ++ ){
    flow.G[ flow.t ][ i ].c = 0;
    Edge &e = flow.G[ flow.t ][ i ];
    flow.G[ e.v ][ e.r ].c = 0;
  }
  flow.addEdge( flow.s , 1 , INF );
  flow.addEdge( n , flow.t , INF );
  flow.reset();
  flow.solve();
  for( auto i : flow.G[ 1 ] )
    if( 1 < i.v and i.v <= 1 + R )
      ansr[ i.v - 1 ] = rsr[ i.v - 1 ] - i.c;
  for( int i = 1 + 1 ; i <= 1 + R ; i ++ )
    for( auto j : flow.G[ i ] )
      if( 1 + R < j.v and j.v <= 1 + R + C )
        ans[ i - 1 ][ j.v - 1 - R ] = ar[ i - 1 ][ j.v - 1 - R ] - j.c;
  for( int i = 1 + R + 1 ; i <= 1 + R + C ; i ++ )
    for( auto j : flow.G[ i ] )
      if( j.v == R + C + 2 )
        ansc[ i - 1 - R ] = csr[ i - 1 - R ] - j.c;
  for( int i = 1 ; i <= R ; i ++ ){
    for( int j = 1 ; j <= C ; j ++ )
      printf( "%d " , ans[ i ][ j ] );
    printf( "%d\n" , ansr[ i ] );
  }
  for( int j = 1 ; j <= C ; j ++ )
    printf( "%d%c" , ansc[ j ] , " \n"[ j == C ] );
  //return ans + flow.maxflow();
}
pair<int,int> parse(){
  int aa , dd;
  scanf( "%d.%d" , &aa , &dd );
  if( dd == 0 ) return { aa , aa };
  return { aa , aa + 1 };
}
int idr[ N ] , idc[ N ];
void init(){
  for( int i = 1 ; i <= R ; i ++ ){
    for( int j = 1 ; j <= C ; j ++ )
      tie( al[ i ][ j ] , ar[ i ][ j ] ) = parse();
    tie( rsl[ i ] , rsr[ i ] ) = parse();
  }
  for( int j = 1 ; j <= C ; j ++ )
    tie( csl[ j ] , csr[ j ] ) = parse();
  n = R + C + 2;
  m = 0;
  for( int i = 1 ; i <= R ; i ++ )
    idr[ i ] = 1 + i;
  for( int j = 1 ; j <= C ; j ++ )
    idc[ j ] = 1 + R + j;
  for( int i = 1 ; i <= R ; i ++ ){
    l[ m ] = 1;
    r[ m ] = idr[ i ];
    a[ m ] = rsl[ i ];
    b[ m ] = rsr[ i ];
    m ++;
    for( int j = 1 ; j <= C ; j ++ ){
      l[ m ] = idr[ i ];
      r[ m ] = idc[ j ];
      a[ m ] = al[ i ][ j ];
      b[ m ] = ar[ i ][ j ];
      m ++;   
    }
  }
  for( int j = 1 ; j <= C ; j ++ ){
    l[ m ] = idc[ j ];
    r[ m ] = R + C + 2;
    a[ m ] = csl[ j ];
    b[ m ] = csr[ j ];
    m ++;   
  }
}
int main(){
  while( scanf( "%d%d" , &R , &C ) == 2 ){
    init();
    solve();
  }
}
