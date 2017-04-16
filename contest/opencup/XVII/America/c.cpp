#include <bits/stdc++.h>
using namespace std;
#define N 333
typedef long long LL;
const int mod = 1000000007;
int n , a[ N ];
bool can[ N ][ N ];
int dp[ N ][ N ] ;
int dp1[ N ][ N ] ;

void add( int &x , int y ) {
  x += y ;
  if ( x >= mod ) x -= mod ;
}

int mul( int x , int y ) {
  return (LL)x * y % mod ;
}

int DP( int , int ) ;

int DP1( int l , int r ) {
  if ( dp1[ l ][ r ] != -1 ) return dp1[ l ][ r ] ;
  if ( l == r ) return dp1[ l ][ r ] = 1 ;

  dp1[ l ][ r ] = 0 ;
  for ( int k = l ; k < r ; k ++ ) {
    //if ( l == 0 && r == 3 )
      //printf( "k = %d, add %d\n" , k ,  mul( DP1( l , k ) , DP( k + 1 , r ) ) ) ;
    add( dp1[ l ][ r ] , mul( DP( l , k ) , DP( k + 1 , r ) ) ) ;
  }
  //printf( "dp1: %d %d -> %d\n" , l , r , dp1[ l ][ r ] ) ;
  return dp1[ l ][ r ] ;
}

int DP( int l , int r ) {
  if ( dp[ l ][ r ] != -1 ) return dp[ l ][ r ] ;
  if ( l == r ) return dp[ l ][ r ] = 1 ;

  dp[ l ][ r ] = 0 ;
  for ( int k = l + 1 ; k <= r ; k ++ ) {
    if ( can[ l ][ k ] ) {
      add( dp[ l ][ r ] , mul( DP1( l , k ) , DP( k , r ) ) ) ;
    }
  }
  //printf( "%d %d\n" , DP1( 2 , 3 ) , DP( 3 , 3 ) ) ;
  //printf( "dp : %d %d -> %d\n" , l , r , dp[ l ][ r ] ) ;
  return dp[ l ][ r ] ;
}

int main(){  
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%d" , &a[ i ] );
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      can[ i ][ j ] = __gcd( a[ i ] , a[ j ] ) > 1;

  memset( dp , -1 , sizeof dp ) ;
  memset( dp1 , -1 , sizeof dp1 ) ;
  printf( "%d\n" , DP( 0 , n - 1 ) ) ;
}
