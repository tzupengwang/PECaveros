#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define SZ(c) ((int)(c).size())
struct Maxflow {
  static const int MAXV = 20010;
  static const int INF  = 1000000;
  struct Edge {
    int v, c, r;
    Edge(int _v, int _c, int _r):
      v(_v), c(_c), r(_r) {}
  };
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
#define N 1021
int n , m , clr[ N ];
vector<int> v[ N ];
void init(){
  for( int i = 1 ; i <= n ; i ++ ){
    clr[ i ] = 0;
    v[ i ].clear();
  }
  while( m -- ){
    int ui , vi;
    scanf( "%d%d" , &ui , &vi );
    v[ ui ].push_back( vi );
    v[ vi ].push_back( ui );
  }
}
void go( int now , int tclr ){
  clr[ now ] = tclr;
  for( int x : v[ now ] )
    if( !clr[ x ] )
      go( x , 3 - tclr );
}
bool vst[ N ];
void gogo( int cur ){
  vst[ cur ] = true;
  for( auto i : flow.G[ cur ] )
    if( i.c > 0 and not vst[ i.v ] and
        i.v != flow.t )
      gogo( i.v );
}
void solve(){
  for( int i = 0 ; i <= n + 3 ; i ++ )
    vst[ i ] = false;
  for( int i = 1 ; i <= n ; i ++ ){
    if( !clr[ i ] )
      go( i , 1 );
  }
  flow.init( n );
  for( int i = 1 ; i <= n ; i ++ ){
    if( clr[ i ] == 1 ){
      flow.addEdge( flow.s , i , 1 );
      for( auto j : v[ i ] )
        flow.addEdge( i , j , 1 );
    }else
      flow.addEdge( i , flow.t , 1 );
  }
  int ans = flow.solve();
  vector< pair<int,int> > vans;
  for( int i = 1 ; i <= n ; i ++ )
    if( clr[ i ] == 1 ){
      for( auto e : flow.G[ i ] )
        if( 1 <= e.v and e.v <= n and
            e.c == 0 ){
          vans.push_back( { i , e.v } );
        }
    }
  gogo( flow.s );
  vector<int> vv;
  for( int i = 1 ; i <= n ; i ++ )
    if( clr[ i ] == 1 and vst[ i ] )
      vv.push_back( i );
    else if( clr[ i ] == 2 and not vst[ i ] )
      vv.push_back( i );
  printf( "%d\n" , ans );
  for( auto i : vans )
    printf( "%d %d\n" , i.first , i.second );
  printf( "%d\n" , (int)vv.size() );
  for( size_t i = 0 ; i < vv.size() ; i ++ )
    printf( "%d%c" , vv[ i ] , " \n"[ i + 1 == vv.size() ] );
}
int main(){
  while( scanf( "%d%d" , &n , &m ) == 2 ){
    init();
    solve();
  }
}
