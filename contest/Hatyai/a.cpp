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
#define N 44
int r , c;
char a[ N ][ N ];
void init(){
  scanf( "%d%d" , &r , &c );
  for( int i = 0 ; i < r ; i ++ )
    scanf( "%s" , a[ i ] );
}
int _cs , dltr[ N ] , dltc[ N ];
int cal( int x , int y ){
  for( int i = 0 ; i < r ; i ++ ){
    dltr[ i ] = x;
    for( int j = 0 ; j < c ; j ++ )
      if( a[ i ][ j ] == '1' )
        dltr[ i ] --;
  }
  for( int j = 0 ; j < c ; j ++ ){
    dltc[ j ] = y;
    for( int i = 0 ; i < r ; i ++ )
      if( a[ i ][ j ] == '1' )
        dltc[ j ] --;
  }
  int ret = 0;
  { // 0 -> 1
    flow.init( r + c );
    for( int i = 0 ; i < r ; i ++ )
      if( dltr[ i ] > 0 )
        flow.addEdge( flow.s , i , dltr[ i ] );
    for( int j = 0 ; j < c ; j ++ )
      if( dltc[ j ] > 0 )
        flow.addEdge( r + j , flow.t , dltc[ j ] );
    for( int i = 0 ; i < r ; i ++ )
      for( int j = 0 ; j < c ; j ++ )
        if( a[ i ][ j ] == '0' )
          flow.addEdge( i , r + j , 1 );
    if( flow.solve() ){
      for( int i = 0 ; i < r ; i ++ )
        for( auto e : flow.G[ i ] ){
          if( e.c == 0 and r <= e.v and e.v < r + c ){
            ret ++;
            dltr[ i ] --;
            dltc[ e.v - r ] --;
          }
        }
    }
  }
  { // 1 -> 0
    flow.init( r + c );
    for( int i = 0 ; i < r ; i ++ )
      if( dltr[ i ] < 0 )
        flow.addEdge( flow.s , i , -dltr[ i ] );
    for( int j = 0 ; j < c ; j ++ )
      if( dltc[ j ] < 0 )
        flow.addEdge( r + j , flow.t , -dltc[ j ] );
    for( int i = 0 ; i < r ; i ++ )
      for( int j = 0 ; j < c ; j ++ )
        if( a[ i ][ j ] == '1' )
          flow.addEdge( i , r + j , 1 );
    if( flow.solve() ){
      for( int i = 0 ; i < r ; i ++ )
        for( auto e : flow.G[ i ] ){
          if( e.c == 0 and r <= e.v and e.v < r + c ){
            ret ++;
            dltr[ i ] ++;
            dltc[ e.v - r ] ++;
          }
        }
    }
  }
  int cst1 = 0 , cst2 = 0;
  for( int i = 0 ; i < r ; i ++ )
    cst1 += abs( dltr[ i ] );
  for( int j = 0 ; j < c ; j ++ )
    cst2 += abs( dltc[ j ] );
  ret += cst1 + cst2 + min( cst1 , cst2 );
  //printf( "%d %d : %d\n" , x , y , ret );
  return ret;
}
void solve(){
  int ans = r * c;
  for( int x = 0 ; x <= c ; x ++ ){
    int v = x * r;
    if( v % c ) continue;
    ans = min( ans , cal( x , v / c ) );
  }
  printf( "Case %d: %d\n" , ++ _cs , ans );
}
int main(){
  int t; scanf( "%d" , &t ); while( t -- ){
    init();
    solve();
  }
}
