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
    //puts("MF");
    int res = 0;
    gap[0] = tot;
    for(res = 0; d[s] < tot; res += dfs(s, INF));
    return res;
  }
} flow;
Maxflow::Edge e(1, 1, 1);
#define N 55
int n , m , a[ N ][ N ] , sum;
void init(){
  scanf( "%d%d" , &n , &m );
  sum = 0;
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < m ; j ++ ){
      scanf( "%d" , &a[ i ][ j ] );
      sum += a[ i ][ j ];
    }
}
void solve(){
  flow.init( n * m );
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < m ; j ++ ){
      if( i + 1 < n ){
        int mx = min( a[ i ][ j ] , a[ i + 1 ][ j ] );
        if( mx ){
          if( ( ( i + j ) & 1 ) == 0 )
            flow.addEdge( i * m + j , ( i + 1 ) * m + j , mx );
          else
            flow.addEdge( ( i + 1 ) * m + j , i * m + j , mx );
        }
      }
      if( j + 1 < m ){
        int mx = min( a[ i ][ j ] , a[ i ][ j + 1 ] );
        if( mx ){
          if( ( ( i + j ) & 1 ) == 0 )
            flow.addEdge( i * m + j , i * m + j + 1 , mx );
          else
            flow.addEdge( i * m + j + 1 , i * m + j , mx );
        }
      }
      if( ( ( i + j ) & 1 ) == 0 )
        flow.addEdge( flow.s , i * m + j , a[ i ][ j ] );
      else
        flow.addEdge( i * m + j , flow.t , a[ i ][ j ] );
    }
  printf( "%d\n" , sum - flow.solve() );
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
