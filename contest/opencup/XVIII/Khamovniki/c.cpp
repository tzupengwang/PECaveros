#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 1021
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
int n , m;
vector<int> v[ N ];
bool nei[ N ];
int wth[ N ];
void gogo( int now ){
  flow.init( n );
  for( int i = 1 ; i <= n ; i ++ )
    nei[ i ] = false;
  for( int i : v[ now ] )
    nei[ i ] = true;
  int nd = 0;
  for( int i = 1 ; i <= n ; i ++ ){
    if( i == now ) continue;
    if( nei[ i ] ){
      flow.addEdge( flow.s , i , 1 );
      for( int j : v[ i ] ){
        if( j == now ) continue;
        if( nei[ j ] ) continue;
        flow.addEdge( i , j , 1 );
      }
    }else{
      flow.addEdge( i , flow.t , 1 );
      nd ++;
    }
  }
  if( flow.solve() != nd ) return;
  for( int i = 1 ; i <= n ; i ++ )
    wth[ i ] = -1;
  for( int i = 1 ; i <= n ; i ++ ){
    if( i == now or not nei[ i ] ) continue;
    for( auto e : flow.G[ i ] ){
      if( 1 <= e.v and e.v <= n and e.c == 0 ){
        wth[ i ] = e.v;
        break;
      }
    }
  }
  puts( "Yes" );
  printf( "%d %d\n" , now , (int)v[ now ].size() );
  for( auto i : v[ now ] )
    printf( "%d %d\n" , i , wth[ i ] );
  exit(0);
}
int main(){
  scanf( "%d%d" , &n , &m );
  for( int i = 0 ; i < m ; i ++ ){
    int ai , bi;
    scanf( "%d%d" , &ai , &bi );
    v[ ai ].push_back( bi );
    v[ bi ].push_back( ai );
  }
  for( int i = 1 ; i <= n ; i ++ ){
    int other = n - 1 - (int)v[ i ].size();
    if( other > (int)v[ i ].size() ) continue;
    gogo( i );
  }
  puts( "No" );
}
