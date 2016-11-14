#include <bits/stdc++.h>
using namespace std;
#define N 33
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
char name[ N ][ 1021 ];
int n , d[ N ][ N ] , w[ N ] , sum;
void init(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%s%d" , name[ i ] , &w[ i ] );
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      scanf( "%d" , &d[ i ][ j ] );
}
int deg[ N ];
bool okay( int now , double x ){
  flow.init( n );
  for( int i = 0 ; i < n ; i ++ )
    deg[ i ] = 0;
  for( int i = 0 ; i < n ; i ++ )
    if( i != now )
      flow.addEdge( flow.s , i , sum );
  for( int i = 0 ; i < n ; i ++ ) if( i != now )
    for( int j = 0 ; j < n ; j ++ ) if( j != now )
      if( d[ i ][ j ] ){
        deg[ i ] += d[ i ][ j ];
        flow.addEdge( i , j , d[ i ][ j ] );
      }
  for( int i = 0 ; i < n ; i ++ )
    if( i != now )
      flow.addEdge( i , flow.t , sum + 2. * x - deg[ i ] - 2 * w[ i ] );
  return sum * ( n - 1 ) - flow.solve() > eps;
}
vector< int > cand;
bool got[ N ];
void gogo( int now ){
  got[ now ] = true;
  if( now < n ) cand.push_back( now );
  for( auto i : flow.G[ now ] )
    if( i.c > eps && !got[ i.v ] )
      gogo( i.v );
}
bool in[ N ];
void go( int now ){
  sum = 0;
  for( int i = 0 ; i < n ; i ++ )
    if( i != now )
      sum += w[ i ];
  for( int i = 0 ; i < n ; i ++ ) if( i != now )
    for( int j = i + 1 ; j < n ; j ++ ) if( j != now )
      sum += d[ i ][ j ];
  double l = 0 , r = sum;
  while( r - l >= 1e-6 ){
    double mid = ( r + l ) * 0.5;
    if( okay( now , mid ) ) l = mid;
    else r = mid;
  }
  okay( now , l );
  //printf( "%.12f\n" , l );
  cand.clear();
  for( int i = 0 ; i < n ; i ++ )
    got[ i ] = false;
  gogo( flow.s );
  sort( cand.begin() , cand.end() );
  int ss = 0 , sw = w[ now ];
  for( int i = 0 ; i < n ; i ++ ) in[ i ] = false;
  for( int x : cand ) in[ x ] = true;
  for( int i = 0 ; i < n ; i ++ )
    if( in[ i ] ){
      ss += w[ i ];
      for( int j = i + 1 ; j < n ; j ++ )
        if( in[ j ] )
          ss += d[ i ][ j ];
    }
  for( int i = 0 ; i < n ; i ++ )
    sw += d[ now ][ i ];
  if( ss > sw * (int)cand.size() ){
    printf( "%s cannot win because of the following teams:\n" , name[ now ] );
    printf( "  " );
    for( size_t i = 0 ; i < cand.size() ; i ++ ){
      if( i ) printf( ", " );
      printf( "%s" , name[ cand[ i ] ] );
    }
    puts( "" );
  }else{
    printf( "%s can win\n" , name[ now ] );
  }
}
void solve(){
  for( int i = 0 ; i < n ; i ++ )
    go( i );
}
int main(){
  freopen( "high.in" , "r" , stdin );
  freopen( "high.out" , "w" , stdout );
  init();
  solve();
}
