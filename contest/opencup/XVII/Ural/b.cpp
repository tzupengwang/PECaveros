#include <bits/stdc++.h>
using namespace std;
#define SZ(c) ((int)(c).size())
struct Maxflow {
  static const int MAXV = 40010;
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
#define N 44444
int b[ 2 ] , k[ 2 ] , s[ 2 ];
int h[ 2 ][ N ];
void init(){
  for( int i = 0 ; i < 2 ; i ++ ){
    scanf( "%d%d%d" , &k[ i ] , &b[ i ] , &s[ i ] );
    for( int j = 0 ; j < k[ i ] ; j ++ )
      scanf( "%d" , &h[ i ][ j ] );
  }
}
void solve(){
  int sum[ 2 ];
  for( int i = 0 ; i < 2 ; i ++ )
    sum[ i ] = accumulate( h[ i ] , h[ i ] + k[ i ] , 0 );
  if( sum[ 0 ] != sum[ 1 ] ){
    puts( "No" );
    exit(0);
  }
#define K 20000
  flow.init( K + k[ 0 ] + k[ 1 ] );
  for( int i = 0 ; i < 2 ; i ++ )
    for( int j = 0 , now = b[ i ] ; j < k[ i ] ; j ++ , now += s[ i ] ){
      if( i == 0 ){
        flow.addEdge( flow.s , K + j + 1 , h[ i ][ j ] );
        for( int kk = now ; kk < now + s[ i ] ; kk ++ )
          flow.addEdge( K + j + 1 , kk , K );
      }else{
        flow.addEdge( K + k[ 0 ] + j + 1 , flow.t , h[ i ][ j ] );
        for( int kk = now ; kk < now + s[ i ] ; kk ++ )
          flow.addEdge( kk , K + k[ 0 ] + j + 1 , K );
      }
    }
  int ret = flow.solve();
  puts( ret == sum[ 0 ] ? "Yes" : "No" );
}
int main(){
#ifndef LOCAL
  freopen( "input.txt" , "r" , stdin );
  freopen( "output.txt" , "w" , stdout );
#endif
  init();
  solve();
}
