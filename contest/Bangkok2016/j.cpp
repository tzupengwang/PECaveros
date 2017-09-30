#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
inline LL getint(){
  LL _x=0,_tmp=1; char _tc=getchar();    
  while( (_tc<'0'||_tc>'9')&&_tc!='-' ) _tc=getchar();
  if( _tc == '-' ) _tc=getchar() , _tmp = -1;
  while(_tc>='0'&&_tc<='9') _x*=10,_x+=(_tc-'0'),_tc=getchar();
  return _x*_tmp;
}
const int MAXN = 22222;
const int MAXM = 403;
struct Simplex{
  const double eps = 1E-10;
  double a[MAXN][MAXM], b[MAXN], c[MAXM], d[MAXN][MAXM];
  double x[MAXM];
  int ix[MAXN + MAXM]; // !!! array all indexed from 0
  // max{cx} subject to {Ax<=b,x>=0}
  // n: constraints, m: vars !!!
  // x[] is the optimal solution vector
  // usage : 
  // value = simplex(a, b, c, N, M);
  pair<double,bool> simplex(int n, int m){
    ++m;
    int r = n, s = m - 1;
    memset(d, 0, sizeof(d));
    for (int i = 0; i < n + m; ++i) ix[i] = i;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m - 1; ++j) d[i][j] = -a[i][j];
      d[i][m - 1] = 1;
      d[i][m] = b[i];
      if (d[r][m] > d[i][m]) r = i;
    }
    for (int j = 0; j < m - 1; ++j) d[n][j] = c[j];
    d[n + 1][m - 1] = -1;
    for (double dd;; ) {
      if (r < n) {
        int t = ix[s]; ix[s] = ix[r + m]; ix[r + m] = t;
        d[r][s] = 1.0 / d[r][s];
        for (int j = 0; j <= m; ++j)
          if (j != s) d[r][j] *= -d[r][s];
        for (int i = 0; i <= n + 1; ++i) if (i != r) {
          for (int j = 0; j <= m; ++j) if (j != s)
            d[i][j] += d[r][j] * d[i][s];
          d[i][s] *= d[r][s];
        }
      }
      r = -1; s = -1;
      for (int j = 0; j < m; ++j)
        if (s < 0 || ix[s] > ix[j]) {
          if (d[n + 1][j] > eps ||
              (d[n + 1][j] > -eps && d[n][j] > eps))
            s = j;
        }
      if (s < 0) break;
      for (int i = 0; i < n; ++i) if (d[i][s] < -eps) {
        if (r < 0 ||
            (dd = d[r][m] / d[r][s] - d[i][m] / d[i][s]) < -eps ||
            (dd < eps && ix[r + m] > ix[i + m]))
          r = i;
      }
      if (r < 0) return { 0 , false }; // not bounded
    }
    if (d[n + 1][m] < -eps) return { 0 , false }; // not executable
    double ans = 0;
    for(int i=0; i<m; i++) x[i] = 0;
    for (int i = m; i < n + m; ++i) { // the missing enumerated x[i] = 0
      if (ix[i] < m - 1){
        ans += d[i - m][m] * c[ix[i]];
        x[ix[i]] = d[i-m][m];
      }
    }
    return { ans , true }; 
  }
} solver;
#define N 514
int n , x , a[ N ] , b[ N ] , c[ N ] , d[ N ];
int m , u[ N * N ] , v[ N * N ];
bool after[ N ][ N ];
void init(){
  n = getint();
  x = getint();
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      after[ i ][ j ] = false;
  for( int i = 0 ; i < n ; i ++ )
    a[ i ] = getint();
  for( int i = 0 ; i < n ; i ++ )
    b[ i ] = getint();
  for( int i = 0 ; i < n ; i ++ )
    c[ i ] = getint();
  for( int i = 0 ; i < n ; i ++ )
    d[ i ] = getint();
  m = getint();
  for( int i = 0 ; i < m ; i ++ ){
    u[ i ] = getint() - 1;
    v[ i ] = getint() - 1;
    after[ u[ i ] ][ v[ i ] ] = true;
  }
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      if( after[ i ][ j ] )
        for( int k = 0 ; k < n ; k ++ ){
          if( after[ i ][ k ] and after[ k ][ j ] ){
            after[ i ][ j ] = false;
            break;
          }
        }
  m = 0;
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      if( after[ i ][ j ] ){
        u[ m ] = i;
        v[ m ] = j;
        m ++;
      }
}
int _cs;
void solve(){
  printf( "Case %d: " , ++ _cs );
  int var = n + n;
  int con = n + n + n + n + m;
  for( int j = 0 ; j < con ; j ++ )
    for( int i = 0 ; i < var ; i ++ )
      solver.a[ j ][ i ] = 0;
  for( int i = 0 ; i < con ; i ++ )
    solver.b[ i ] = 0;
  for( int i = 0 ; i < var ; i ++ )
    solver.c[ i ] = 0;
  // max{cx} subject to {Ax<=b,x>=0}
  for( int i = 0 ; i < n ; i ++ ){
    solver.a[ i ][ i ] = 1;
    solver.a[ i ][ n + i ] = -1;
    solver.b[ i ] = x - a[ i ];
  }
  // p_i - r_i <= x - a_i
  // p_i + a_i - r_i <= x
  for( int i = 0 ; i < n ; i ++ ){
    solver.a[ n + i ][ n + i ] = 1;
    solver.b[ n + i ] = a[ i ] - b[ i ];
  }
  // r_i <= a_i - b_i
  for( int i = 0 ; i < m ; i ++ ){
    solver.a[ n + n + i ][ u[ i ] ] = 1;
    solver.a[ n + n + i ][ n + u[ i ] ] = -1;
    solver.a[ n + n + i ][ v[ i ] ] = -1;
    solver.b[ n + n + i ] = -a[ u[ i ] ];
  }
  // p_{ui} - d_{ui} - p_{vi} <= -a_{ui}
  // p_{ui} + a_{ui} - d_{ui} <= p_{vi}
  for( int i = 0 ; i < n ; i ++ ){
    solver.a[ n + n + m + i ][ i ] = -1;
    solver.b[ n + n + m + i ] = 0;
  }
  // -p_i <= 0
  // p_i >= 0
  for( int i = 0 ; i < n ; i ++ ){
    solver.a[ n + n + n + m + i ][ n + i ] = -1;
    solver.b[ n + n + n + m + i ] = 0;
  }
  // -r_i <= 0
  // r_i >= 0
  for( int i = 0 ; i < n ; i ++ )
    solver.c[ n + i ] = -d[ i ];
  // c_{r_i} * r_i
  pair<double,bool> ans = solver.simplex(con, var);
  if( not ans.second ){
    puts( "Impossible" );
    return;
  }
  printf( "%lld" , (LL)round( -ans.first ) + accumulate( c , c + n , 0LL ) );
  for( int i = 0 ; i < n ; i ++ )
    printf( " %lld %lld" , (LL)round( solver.x[ i ] ) ,
                           (LL)round( solver.x[ n + i ] ) );
  puts( "" );
}
int main(){
  int t = getint(); while( t -- ){
    init();
    solve();
  }
}
