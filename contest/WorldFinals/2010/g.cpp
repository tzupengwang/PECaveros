#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 111
double sqr( double x ){ return x * x; }
const double inf = 1e20;
const double eps = 1e-6;
int n , b1 , b2 , x[ N ] , y[ N ];
double dp[ N ][ N ];
int bki[ N ][ N ];
int bkj[ N ][ N ];
int _cs;
double dist( int id1 , int id2 ){
  return sqrt( sqr( x[ id1 ] - x[ id2 ] ) +
               sqr( y[ id1 ] - y[ id2 ] ) );
}
double cal(){
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      dp[ i ][ j ] = inf;
  dp[ 0 ][ 0 ] = 0;
  for( int i = 0 ; i + 1 < n ; i ++ )
    for( int j = 0 ; j <= i ; j ++ ){
      int nxt = i + 1;
      if( nxt != b2 ){
        {
          double ndp = dp[ i ][ j ] + dist( i , nxt );
          if( ndp < dp[ nxt ][ j ] - eps ){
            dp[ nxt ][ j ] = ndp;
            bki[ nxt ][ j ] = i;
            bkj[ nxt ][ j ] = j;
          }
        }
        {
          double ndp = dp[ j ][ i ] + dist( j , nxt );
          if( ndp < dp[ nxt ][ i ] - eps ){
            dp[ nxt ][ i ] = ndp;
            bki[ nxt ][ i ] = j;
            bkj[ nxt ][ i ] = i;
          }
        }
      }
      if( nxt != b1 ){
        {
          double ndp = dp[ i ][ j ] + dist( j , nxt );
          if( ndp < dp[ i ][ nxt ] - eps ){
            dp[ i ][ nxt ] = ndp;
            bki[ i ][ nxt ] = i;
            bkj[ i ][ nxt ] = j;
          }
        }
        {
          double ndp = dp[ j ][ i ] + dist( i , nxt );
          if( ndp < dp[ j ][ nxt ] - eps ){
            dp[ j ][ nxt ] = ndp;
            bki[ j ][ nxt ] = j;
            bkj[ j ][ nxt ] = i;
          }
        }
      }
    }
  for( int i = 1 ; i < n - 1 ; i ++ ){
    {
      double ndp = dp[ n - 1 ][ i ] + dist( i , n - 1 );
      if( ndp < dp[ n - 1 ][ n - 1 ] - eps ){
        dp[ n - 1 ][ n - 1 ] = ndp;
        bki[ n - 1 ][ n - 1 ] = n - 1;
        bkj[ n - 1 ][ n - 1 ] = i;
      }
    }
    {
      double ndp = dp[ i ][ n - 1 ] + dist( i , n - 1 );
      if( ndp < dp[ n - 1 ][ n - 1 ] - eps ){
        dp[ n - 1 ][ n - 1 ] = ndp;
        bki[ n - 1 ][ n - 1 ] = i;
        bkj[ n - 1 ][ n - 1 ] = n - 1;
      }
    }
  }
  return dp[ n - 1 ][ n - 1 ];
}
void find_ans(){
  vector<int> up , dn;
  int cn = n - 1 , cm = n - 1;
  while( cn or cm ){
    //printf( "%d %d\n" , cn , cm );
    int bkn = bki[ cn ][ cm ];
    int bkm = bkj[ cn ][ cm ];
    if( bkn != cn )
      up.push_back( cn );
    if( bkm != cm )
      dn.push_back( cm );
    cn = bkn;
    cm = bkm;
  }
  reverse( up.begin() , up.end() );
  up.pop_back();
  reverse( dn.begin() , dn.end() );
  dn.pop_back();
  reverse( dn.begin() , dn.end() );
  vector<int> ans;
  ans.push_back( 0 );
  for( auto i : up )
    ans.push_back( i );
  ans.push_back( n - 1 );
  for( auto i : dn )
    ans.push_back( i );
  ans.push_back( 0 );
  if( ans[ 1 ] != 1 )
    reverse( ans.begin() , ans.end() );
  for( size_t i = 0 ; i < ans.size() ; i ++ )
    printf( "%d%c" , ans[ i ] , " \n"[ i + 1 == ans.size() ] );
}
void solve(){
  double ans1 = cal();
  swap( b1 , b2 );
  double ans2 = cal();
  if( ans1 < ans2 ){
    swap( b1 , b2 );
    ans2 = cal();
  }
  printf( "Case %d: %.2f\n" , ++ _cs , ans2 );
  find_ans();
}
int main(){
  while( scanf( "%d%d%d" , &n , &b1 , &b2 ) == 3 and n ){
    for( int i = 0 ; i < n ; i ++ )
      scanf( "%d%d" , &x[ i ] , &y[ i ] );
    solve();
  }
}
