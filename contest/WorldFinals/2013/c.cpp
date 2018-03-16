#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define SZ(c) ((int)(c).size())
#define MAXV 30303
#define INF 1000000
struct Maxflow {
  struct Edge{
    int v , c , r;
    Edge(int _v, int _c, int _r):
      v(_v), c(_c), r(_r) {}
  };
  int s , t;
  vector<Edge> G[MAXV * 2];
  int iter[MAXV * 2] , d[MAXV * 2], gap[MAXV * 2] , tot;
  bool vis[MAXV*2];
  void init( int x ){
    tot = x + 2;
    s = x + 1, t = x + 2;
    for( int i = 0 ; i <= tot ; i ++ ){
      G[ i ].clear();
      vis[i] = 0;
    }
  }
  void addEdge(int u, int v, int c) {
    G[u].push_back(Edge(v, c, SZ(G[v])));
    G[v].push_back(Edge(u, 0, SZ(G[u]) - 1 ));
  }
  int dfs(int p , int flow){
    vis[p] = 1;
    if( p == t ) return flow;
    for( int i = 0 ; i < SZ(G[p]) ; i ++ ){
      Edge& e = G[p][i];
      if(e.c > 0 && !vis[e.v]){
        int f = dfs(e.v, min(flow, e.c));
        if(f){
          e.c -= f;
          G[e.v][e.r].c += f;
          return f;
        }
      }
    }
    return 0;
  }
  int solve(){
    int res = 0;
    while (1) {
      fill(vis, vis+tot+1, 0);
      int tf = dfs(s, INF);
      if (!tf) break;
      res += tf;
    }
    return res;
  }
} flow;
#define N 30303
int n , m , c;
vector< pair<int,int> > v[ N ];
int dis[ N ] , ss[ N ];
bool got[ N ];
vector< pair<int,int> > wt;
int main(){
  scanf( "%d%d%d" , &n , &m , &c );
  while( m -- ){
    int xi , yi , ci;
    scanf( "%d%d%d" , &xi , &yi , &ci );
    v[ xi ].push_back( {yi, ci} );
    v[ yi ].push_back( {xi, ci} );
  }
typedef pair<int,int> dat;
  priority_queue< dat , vector<dat> , greater<dat> > heap;
  heap.push( {0, 1} );
  while( heap.size() ){
    int nd , who;
    tie( nd , who ) = heap.top(); heap.pop();
    if( got[ who ] ) continue;
    got[ who ] = true;
    dis[ who ] = nd;
    for( auto e : v[ who ] ){
      if( got[ e.first ] ) continue;
      heap.push( {nd + e.second , e.first} );
    }
  }
  for( int i = 0 , x ; i < c ; i ++ ){
    scanf( "%d" , &x );
    ss[ x ] ++;
  }
  int ans = 0;
  for( int i = 1 ; i <= n ; i ++ )
    wt.push_back( {dis[ i ] , i} );
  sort( wt.begin() , wt.end() );
  for( size_t l = 0 , r = 0 ; l < wt.size() ; l = r ){
    while( r < wt.size() and wt[ l ].first == wt[ r ].first ) r ++;
    int sum = 0;
    for( size_t i = l ; i < r ; i ++ )
      sum += ss[ wt[ i ].second ];
    if( sum == 0 ) continue;
    flow.init( n );
    for( size_t i = l ; i < r ; i ++ )
      if( ss[ wt[ i ].second ] )
        flow.addEdge( flow.s , wt[ i ].second , ss[ wt[ i ].second ] );
    for( int i = 1 ; i <= n ; i ++ ){
      if( dis[ i ] > wt[ l ].first ) continue;
      for( auto e : v[ i ] )
        if( dis[ e.first ] + e.second == dis[ i ] )
          flow.addEdge( i , e.first , 1 );
    }
    flow.addEdge( 1 , flow.t , sum );
    ans += flow.solve();
  }
  printf( "%d\n" , ans );
}
