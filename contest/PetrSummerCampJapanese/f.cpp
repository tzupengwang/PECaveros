#include <bits/stdc++.h>
using namespace std;
#define N 1021
#define SZ(c) ((int)(c).size())
struct Maxflow {
  static const int MAXV = 20010;
  static const int INF  = 1023456789;
  struct Edge {
    int v, c, r;
    Edge(int _v, int _c, int _r) : v(_v), c(_c), r(_r) {}
  };
  int s, t;
  vector<Edge> G[MAXV*2];
  int iter[MAXV*2], d[MAXV*2], gap[MAXV*2], tot;
  void flowinit(int x) {
    tot = x+2;
    s = x+1, t = x+2;
    for(int i = 0; i <= tot; i++) {
      G[i].clear();
      iter[i] = d[i] = gap[i] = 0;
    }
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

  int maxflow() {
    //puts("MF");
    int res = 0;
    gap[0] = tot;
    for(res = 0; d[s] < tot; res += dfs(s, INF));
    return res;
  }
} flow;
int n , m , l;
int d[ N ][ N ] , p[ N ] , k[ N ];
#define INF 1023456789
void init(){
  for( int i = 1 ; i <= n ; i ++ ){
    for( int j = 1 ; j <= n ; j ++ )
      d[ i ][ j ] = INF;
    d[ i ][ i ] = 0;
  }
  while( m -- ){
    int ui , vi , ci;
    scanf( "%d%d%d" , &ui , &vi , &ci );
    d[ ui ][ vi ] = min( d[ ui ][ vi ] , ci );
    d[ vi ][ ui ] = min( d[ vi ][ ui ] , ci );
  }
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%d" , &p[ i ] );
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%d" , &k[ i ] );
}
void solve(){
  int ans = 0;
  for( int u = 1 ; u <= n ; u ++ )
    for( int i = 1 ; i <= n ; i ++ )
      for( int j = 1 ; j <= n ; j ++ )
        d[ i ][ j ] = min( d[ i ][ j ] , d[ i ][ u ] + d[ u ][ j ] );
  flow.flowinit( n );
  for( int i = 1 ; i <= n ; i ++ ){
    if( p[ i ] > k[ i ] )
      flow.addEdge( flow.s , i , p[ i ] - k[ i ] );
    if( p[ i ] < k[ i ] )
      flow.addEdge( i , flow.t , k[ i ] - p[ i ] );
    ans += min( p[ i ] , k[ i ] );
  }
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= n ; j ++ )
      if( i != j && d[ i ][ j ] < l )
        flow.addEdge( i , j , INF );
  printf( "%d\n" , ans + flow.maxflow() );
}
int main(){
  while( scanf( "%d%d%d" , &n , &m , &l ) == 3 ){
    init();
    solve();
  }
}
