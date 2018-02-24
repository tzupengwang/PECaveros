#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 514
int p[ N ] , sz[ N ] , k[ N ];
int f( int x ){
  return x == p[ x ] ? x : p[ x ] = f( p[ x ] );
}
void uni( int x , int y ){
  x = f( x );
  y = f( y );
  if( x == y ) return;
  p[ x ] = y;
  sz[ y ] += sz[ x ];
}
int n , m , x[ N ] , y[ N ] , z[ N ];
double sqr( double xx ){ return xx * xx; }
double dist( int id1 , int id2 ){
  return sqrt( sqr( x[ id1 ] - x[ id2 ] ) +
               sqr( y[ id1 ] - y[ id2 ] ) +
               sqr( z[ id1 ] - z[ id2 ] ) );
}
double d[N][N];
bool show[ N ];
vector< pair<int,int> > vv;
vector<int> ee[ N ];
void init(){
  vv.clear();
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%d%d%d%d" , &x[ i ] , &y[ i ] , &z[ i ] , &sz[ i ] );
    k[ i ] = sz[ i ];
    p[ i ] = i;
    show[ i ] = false;
    vv.push_back( { z[ i ] , i } );
    ee[ i ].clear();
  }
  for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) d[i][j] = dist(i,j);
  while( m -- ){
    int ui , vi;
    scanf( "%d%d" , &ui , &vi );
    ee[ ui ].push_back( vi );
    ee[ vi ].push_back( ui );
  }
  sort( vv.begin() , vv.end() );
}
const double inf = 1e20;
int _cs;

typedef pair<double,int> XD;
vector<XD> g[N*2];
bool got[N*2];
double dis[N*2];
double calc(int up) {
  //printf("calc %d\n", up);
  for (int i = 1; i <= n; ++i) show[i] = z[i] <= up;
  vector<int> avail;
  for (int i = 1; i <= n; ++i) if (show[i]) {
    avail.push_back(i);
    g[i].clear();
    g[N+i].clear();
    p[i] = i;
    sz[i] = k[i];
  }
  for (int i = 1; i <= n; ++i) if (show[i]) {
    for (int v: ee[i]) if (show[v]) uni(i, v);
  }
  for (int u: avail) for (int v: avail) {
    if (u == v) {
      if (k[u] >= 2) {
        g[u].push_back(XD{0, N+v});
      }
    } else if (f(u) == f(v)) {
      if (k[u] > 0 && k[v] > 0) {
        g[u].push_back(XD{0, N+v});
      }
    } else {
      if (k[u] > 0 && k[v] > 0) {
        g[N+u].push_back(XD{d[u][v] - 1 + 0.5 * sz[f(v)], v});
      }
    }
  }
  if (f(1) == f(n)) return 0.5 * sz[f(1)];
  priority_queue<XD,vector<XD>,greater<XD>> heap;
  for (int u: avail) got[u] = got[N+u] = 0;
  for (int u: avail) if (f(u) == f(1)) {
    heap.push({0.5 * sz[f(1)], N+u});
  }
  while (heap.size()) {
    XD tp = heap.top(); heap.pop();
    double td = tp.first;
    int u = tp.second;
    if (got[u]) continue;
    //printf("  got %d\n", u);
    got[u] = 1;
    dis[u] = td;
    for (XD e: g[u]) {
      double ec = e.first;
      int v = e.second;
      if (!got[v]) {
        heap.push({td + ec, v});
      }
    }
  }
  double res = inf;
  for (int u: avail) if (f(u) == f(n)) {
    if (got[u]) res = min(res, dis[u]);
  }
  //printf("done %g\n", res);
  return res;
}

void solve(){
  double ans;
  ans = inf;
  for( size_t l = 0 , r = 0 ; l < vv.size() ; l = r ){
    while( r < vv.size() and vv[ l ].first == vv[ r ].first ) r ++;
    ans = min(ans, calc(vv[l].first));
    continue;
  }
  printf( "Case %d: " , ++ _cs );
  if( ans >= inf )
    puts( "impossible" );
  else
    printf( "%.4f\n" , ans );
}
int main(){
  while( scanf( "%d%d" , &n , &m ) == 2 ){
    init();
    solve();
  }
}
