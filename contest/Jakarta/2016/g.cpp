#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 111
int n , l[ N ] , r[ N ];
vector<int> reg;
double p[ N ][ N + N ];
inline double prob( int id , int bl , int br ){
  int pl = max( bl , l[ id ] );
  int pr = min( br , r[ id ] );
  return (double)( max( 0 , pr - pl + 1 ) ) / ( r[ id ] - l[ id ] + 1 );
}
void init(){
  scanf( "%d" , &n );
  reg.clear();
  for( int i = 0 ; i < n ; i ++ ){
    scanf( "%d%d" , &l[ i ] , &r[ i ] );
    reg.push_back( l[ i ] );
    reg.push_back( r[ i ] + 1 );
  }
  sort( reg.begin() , reg.end() );
  reg.resize( unique( reg.begin() , reg.end() ) - reg.begin() );
  for( int i = 0 ; i < n ; i ++ )
    for( size_t j = 0 ; j + 1 < reg.size() ; j ++ )
      p[ i ][ j ] = prob( i , reg[ j ] , reg[ j + 1 ] - 1 );
}
double dp[ N ][ N + N ][ N ] , sdp[ N ][ N ];
int _cs;
void solve(){
  for( int i = 0 ; i < n ; i ++ ){
    for( size_t j = 0 ; j + 1 < reg.size() ; j ++ )
      for( int k = 0 ; k <= n ; k ++ )
        dp[ i ][ j ][ k ] = 0.0;
    for( int k = 0 ; k <= n ; k ++ )
      sdp[ i ][ k ] = 0.0;
  }
  for( size_t j = 0 ; j + 1 < reg.size() ; j ++ )
    dp[ 0 ][ j ][ 1 ] = p[ 0 ][ j ];
  for( int i = 1 ; i < n ; i ++ ){
    for( size_t j = 0 ; j + 1 < reg.size() ; j ++ )
      for( int k = 1 ; k <= i + 1 ; k ++ )
        sdp[ i - 1 ][ k ] += dp[ i - 1 ][ j ][ k ];
    for( size_t j = 0 ; j + 1 < reg.size() ; j ++ )
      for( int k = 1 ; k <= i + 1 ; k ++ ){
        double tmp = sdp[ i - 1 ][ k - 1 ] - dp[ i - 1 ][ j ][ k - 1 ];
        tmp += dp[ i - 1 ][ j ][ k - 1 ] * ( 1. - 1. / ( reg[ j + 1 ] - reg[ j ] ) );
        tmp += dp[ i - 1 ][ j ][ k ] * ( 1. / ( reg[ j + 1 ] - reg[ j ] ) );
        tmp *= p[ i ][ j ];
        dp[ i ][ j ][ k ] = tmp;
      } 
  }
  double ans = 0.0;
  for( int k = 1 ; k <= n ; k ++ ){
    double ss = 0;
    for( size_t j = 0 ; j + 1 < reg.size() ; j ++ )
      ss += dp[ n - 1 ][ j ][ k ];
    ans += ss * powl( k - 1 , 1.5 );
  }
  printf( "Case #%d: %.9f\n" , ++ _cs , ans );
}
int main(){
  int t; scanf( "%d" , &t ); while( t -- ){
    init();
    solve();
  }
}
