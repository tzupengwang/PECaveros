#include <bits/stdc++.h>
using namespace std;
const int MAXN = 514;
const int MAXM = 514;
const double eps = 1E-10;
struct Simplex{
  double a[MAXN][MAXM], b[MAXN], c[MAXM], d[MAXN][MAXM];
  double x[MAXM];
  int ix[MAXN + MAXM]; // !!! array all indexed from 0
  // max{cx} subject to {Ax<=b,x>=0}
  // n: constraints, m: vars !!!
  // x[] is the optimal solution vector
  // usage : 
  // value = simplex(a, b, c, N, M);
  double simplex(int n, int m){
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
      if (r < 0) return -1; // not bounded
    }
    if (d[n + 1][m] < -eps) return -1; // not executable
    double ans = 0;
    for(int i=0; i<m; i++) x[i] = 0;
    for (int i = m; i < n + m; ++i) { // the missing enumerated x[i] = 0
      if (ix[i] < m - 1){
        ans += d[i - m][m] * c[ix[i]];
        x[ix[i]] = d[i-m][m];
      }
    }
    return ans; 
  }
} solver;
#define N 20
char c[ N ][ N ];
int h , w , bomb[ N ][ N ] , ans;
vector< pair<int,int> > b;
bool n[ N ][ N ] , y[ N ][ N ];
bool got , gg;
clock_t s;
void go( int cur , int st );
void go2( int cur , int st , pair<int,int> cst[] , int cstsz , int nowat , int ndsz ){
  if( got ) return;
  if( ndsz == 0 ){
    bool on[ 10 ];
    for( int i = nowat + 1 ; i < cstsz ; i ++ ){
      on[ i ] = n[ cst[ i ].first ][ cst[ i ].second ];
      n[ cst[ i ].first ][ cst[ i ].second ] = true;
    }
    go( cur + 1 , st );
    for( int i = nowat + 1 ; i < cstsz ; i ++ )
      n[ cst[ i ].first ][ cst[ i ].second ] = on[ i ];
    return;
  }
  if( clock() - s > CLOCKS_PER_SEC * 0.2 ){
    got = true;
    gg = true;
    return;
  }
  y[ cst[ nowat ].first ][ cst[ nowat ].second ] = true;
  go2( cur , st + 1 , cst , cstsz , nowat + 1 , ndsz - 1 );
  y[ cst[ nowat ].first ][ cst[ nowat ].second ] = false;
  if( got ) return;
  if( cstsz - nowat - 1 >= ndsz ){
    n[ cst[ nowat ].first ][ cst[ nowat ].second ] = true;
    go2( cur , st , cst , cstsz , nowat + 1 , ndsz );
    n[ cst[ nowat ].first ][ cst[ nowat ].second ] = false;
  }
}
void go( int cur , int st ){
  if( st >= ans ) return;
  if( got ) return;
  if( clock() - s > CLOCKS_PER_SEC * 0.2 ){
    got = true;
    gg = true;
    return;
  }
  if( cur == (int)b.size() ){
    ans = st;
    return;
  }
  int nd = c[ b[ cur ].first ][ b[ cur ].second ] - '0';
  int gt = 0;
  pair<int,int> cst[ 9 ];
  int ctt = 0;
  for( int i = -1 ; i <= 1 ; i ++ )
    for( int j = -1 ; j <= 1 ; j ++ ){
      int ni = b[ cur ].first + i;
      int nj = b[ cur ].second + j;
      if( ni < 0 or ni >= h ) continue;
      if( nj < 0 or nj >= w ) continue;
      if( y[ ni ][ nj ] ) gt ++;
      else if( !n[ ni ][ nj ] )
        cst[ ctt ++ ] = { ni , nj };
    }
  if( gt > nd ) return;
  if( st + nd - gt >= ans ) return;
  if( gt + ctt < nd ) return;
  go2( cur , st , cst , ctt , 0 , nd - gt );
}
bool cmp( pair<int,int> p1 , pair<int,int> p2 ){
  return c[ p1.first ][ p1.second ] >
         c[ p2.first ][ p2.second ];
}
int id[ N ][ N ];
int solve2(){
  int var = 0;
  vector< pair<int,int> > dgt;
  for( int i = 0 ; i < h ; i ++ ){
    for( int j = 0 ; j < w ; j ++ ){
      if( c[ i ][ j ] != '.' )
        id[ i ][ j ] = var ++;
      if( '0' <= c[ i ][ j ] and 
          c[ i ][ j ] <= '9' )
        dgt.push_back( { i , j } );
    }
  }
  int con = (int)dgt.size() * 2 + var;
  // max{cx} subject to {Ax<=b,x>=0}
  for( int i = 0 ; i < var ; i ++ )
    solver.c[ i ] = -1;
  for( int i = 0 ; i < con ; i ++ )
    for( int j = 0 ; j < var ; j ++ )
      solver.a[ i ][ j ] = 0;
  for( int i = 0 ; i < (int)dgt.size() ; i ++ ){
    vector<int> vid;
    for( int di = -1 ; di <= 1 ; di ++ )
      for( int dj = -1 ; dj <= 1 ; dj ++ ){
        int ni = dgt[ i ].first + di;
        int nj = dgt[ i ].second + dj;
        if( ni < 0 or ni >= h or
            nj < 0 or nj >= w )
          continue;
        if( c[ ni ][ nj ] == '.' )
          continue;
        vid.push_back( id[ ni ][ nj ] );
      }
    int dd = c[ dgt[ i ].first ][ dgt[ i ].second ] - '0';
    solver.b[ i * 2 + 0 ] = dd;
    solver.b[ i * 2 + 1 ] = -dd;
    for( auto j : vid ){
      solver.a[ i * 2 + 0 ][ j ] = 1;
      solver.a[ i * 2 + 1 ][ j ] = -1;
    }
  }
  for( int i = 0 ; i < var ; i ++ ){
    solver.a[ (int)dgt.size() * 2 + i ][ i ] = 1;
    solver.b[ (int)dgt.size() * 2 + i ] = 1;
  }
  return (int)round( -solver.simplex( con , var ) );
}
int main(){
  while( scanf( "%d%d" , &h , &w ) == 2 and h ){
    b.clear();
    for( int i = 0 ; i < h ; i ++ ){
      scanf( "%s" , c[ i ] );
      for( int j = 0 ; j < w ; j ++ ){
        bomb[ i ][ j ] = 0;
        n[ i ][ j ] = y[ i ][ j ] = false;
      }
    }
    ans = h * w;
    for( int i = 0 ; i < h ; i ++ )
      for( int j = 0 ; j < w ; j ++ )
        if( '0' <= c[ i ][ j ] and c[ i ][ j ] <= '9' )
          b.push_back( { i , j } );
    sort( b.begin() , b.end() , cmp );
    for( int i = 0 ; i < h ; i ++ )
      for( int j = 0 ; j < w ; j ++ )
        if( c[ i ][ j ] == '.' )
          n[ i ][ j ] = true;
    got = false;
    ans = h * w;
    gg = false;
    s = clock();
    go( 0 , 0 );
    if( got )
      ans = min( ans , solve2() );
    printf( "%d\n" , ans );
  }
}
