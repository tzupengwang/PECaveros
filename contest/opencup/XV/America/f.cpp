#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const double eps = 1e-7;
#define N 222
#define SZ(c) ((int)(c).size())
const double INF  = 1e8;
struct Maxflow {
  static const int MAXV = N * N;
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
      if(e.c > eps && d[p] == d[e.v]+1) {
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
    double res = 0;
    gap[0] = tot;
    for(res = 0; d[s] < tot; res += dfs(s, INF));
    return res;
  }
} flow;
int n , m , w , h;
double v[ N ] , x[ N ] , mn[ N ][ N ] , mx[ N ][ N ];
void init(){
  scanf( "%d%d%d%d" , &n , &m , &w , &h );
  for( int i = 0 ; i < m ; i ++ )
    scanf( "%lf" , &v[ i ] );
  for( int i = 0 ; i + 1 < n ; i ++ )
    scanf( "%lf" , &x[ i ] );
  x[ n - 1 ] = w;
  for( int i = n - 1 ; i ; i -- )
    x[ i ] -= x[ i - 1 ];
  //for( int i = 1 ; i < n ; i ++ )
    //x[ i ] -= x[ i - 1 ];
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < m ; j ++ )
      scanf( "%lf" , &mn[ i ][ j ] );
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < m ; j ++ )
      scanf( "%lf" , &mx[ i ][ j ] );
}
double sum[ N ];
int id( int i , int j ){
  return i * m + j;
}
bool okay( double atleast ){
  flow.init( m + n * m + n );
  for( int i = 0 ; i < m ; i ++ )
    flow.addEdge( flow.s , i , v[ i ] );
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < m ; j ++ ){
      flow.addEdge( j , id( i , j ) + m , mx[ i ][ j ] );
      flow.addEdge( id( i , j ) + m , n * m + m + i , 1e8 );
    }
  double nd = 0;
  for( int i = 0 ; i < n ; i ++ ){
    if( sum[ i ] > atleast - eps ) continue;
    double tnd = ( atleast - sum[ i ] ) * x[ i ];
    nd += tnd;
    flow.addEdge( n * m + m + i , flow.t , tnd );
  }
  return flow.solve() > nd - eps;
}
void solve(){
  for( int i = 0 ; i < n ; i ++ ){
    for( int j = 0 ; j < m ; j ++ ){
      sum[ i ] += mn[ i ][ j ];
      v[ j ] -= mn[ i ][ j ];
      mx[ i ][ j ] -= mn[ i ][ j ];
    }
    sum[ i ] /= x[ i ];
  }
  double mxsum = *max_element( sum , sum + n );
  double mnsum = *min_element( sum , sum + n );
  double bl = 0 , br = mxsum - mnsum;
  for( int i = 0 ; i < 60 ; i ++ ){
    double bmid = (bl + br) * .5;
    if( okay( mnsum + bmid ) ) bl = bmid;
    else br = bmid;
  }
  printf( "%.12f\n" , mxsum - (mnsum + bl) );
}
int main(){
  init();
  solve();
}
