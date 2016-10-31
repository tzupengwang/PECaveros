#include <bits/stdc++.h>
using namespace std;
#define SZ(c) ((int)(c).size())
const double eps = 1e-8;
const double INF  = 1e10;
struct Maxflow {
  static const int MAXV = 20010;
  struct Edge {
    int v;
    double c;
    int r;
    Edge(int _v, double _c, int _r):
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
  void addEdge(int u, int v, double c) {
    G[u].push_back(Edge(v, c, SZ(G[v]) ));
    G[v].push_back(Edge(u, 0, SZ(G[u]) - 1));
  }
  double dfs(int p, double flow) {
    if(p == t) return flow;
    for(int &i = iter[p]; i < SZ(G[p]); i++) {
      Edge &e = G[p][i];
      if(e.c > 0 && d[p] == d[e.v]+1) {
        double f = dfs(e.v, min(flow, e.c));
        if(f > eps) {
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
  double solve() {
    //puts("MF");
    double res = 0;
    gap[0] = tot;
    for(res = 0; d[s] < tot; res += dfs(s, INF));
    return res;
  }
} flow;
#define N 111
int n , m , k , d[ N ];
vector< pair<int,int> > e;
void init(){
  scanf( "%d%d%d" , &n , &m , &k );
  for( int i = 0 ; i < m ; i ++ ){
    int ui, vi; scanf( "%d%d" , &ui , &vi );
    e.push_back( { ui , vi } );
    d[ ui ] ++;
    d[ vi ] ++;
  }
}
bool okay( double x ){
  flow.init( n );
  for( int i = 1 ; i <= n ; i ++ )
    flow.addEdge( flow.s , i , m );
  for( auto i : e ){
    flow.addEdge( i.first , i.second , 1.0 );
    flow.addEdge( i.second , i.first , 1.0 );
  }
  for( int i = 1 ; i <= n ; i ++ )
    flow.addEdge( i , flow.t , m + 2. * x - d[ i ] );
  return m * n - flow.solve() > eps;
}
vector< int > ans;
bool got[ N ];
void go( int now ){
  got[ now ] = true;
  if( now <= n ) ans.push_back( now );
  for( auto i : flow.G[ now ] )
    if( i.c > eps && !got[ i.v ] )
      go( i.v );
}
bool in[ N ];
inline bool good(){
  for( int i : ans ) in[ i ] = true;
  int cnt = 0;
  for( auto i : e )
    if( in[ i.first ] && in[ i.second ] )
      cnt ++;
  if( cnt <= k * ( (int)ans.size() - 1 ) )
    return false;
  puts( "Redundant" );
  printf( "%d\n" , (int)ans.size() );
  for( size_t i = 0 ; i < ans.size() ; i ++ )
    printf( "%d%c" , ans[ i ] , " \n"[ i + 1 == ans.size() ] );
  return true;
}
void solve(){
  double l = 0 , r = m , x = 1. / n / n;
  while( r - l >= x ){
    double mid = ( r + l ) * 0.5;
    if( okay( mid ) ) l = mid;
    else r = mid;
  }
  okay( l );
  go( flow.s );
  sort( ans.begin() , ans.end() );
  if( !good() ) puts( "OK" );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "highways.in" , "r" , stdin );
  freopen( "highways.out" , "w" , stdout );
#endif
  init();
  solve();
}
