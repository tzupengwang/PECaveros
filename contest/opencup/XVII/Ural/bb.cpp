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

typedef pair<int,int> PII;

struct Edge {
  int u , v , c;
};

inline bool BF( int n , vector<Edge> edges ) {
  static int d[ N ];
  fill( d+1 , d+1+n , 0 );
  for( int _ = 0 ; _ < n+1 ; _++ ) {
    bool upd = 0;
    for( auto e : edges ) {
      if ( d[ e.v ] > d[ e.u ] + e.c ) {
        upd = 1;
        d[ e.v ] = d[ e.u ] + e.c;
      }
    }
    if ( _ == n && upd ) return 0;
  }
  return 1;
}

void solve(){
  int cnt = 0;
  map<int,int> mp;
  mp[ 0 ] = ++cnt;
  vector<Edge> es;
  for( int j = 0 ; j < 2 ; j++ ) {
    for( int i = 0 ; i < k[ j ] ; i++ ) {
      int l = i*s[j] + b[j];
      int r = l+s[j] - 1;
      if ( !mp.count( l-1 ) ) mp[ l-1 ] = ++cnt;
      if ( !mp.count( r ) ) mp[ r ] = ++cnt;
      es.push_back( { mp[ l-1 ] , mp[ r ] , h[j][i] } );
      es.push_back( { mp[ r ] , mp[ l-1 ] , -h[j][i] } );
    }
  }
  vector<int> vec;
  for( auto p : mp ) {
    vec.push_back( p.second );
  }
  for( int i = 1 ; i < vec.size() ; i++ )
    es.push_back( { vec[i] , vec[i-1] , 0 } );
  puts( BF( cnt , es ) ? "Yes" : "No" );
}

int main(){
#ifndef LOCAL
  freopen( "input.txt" , "r" , stdin );
  freopen( "output.txt" , "w" , stdout );
#endif
  init();
  solve();
}
