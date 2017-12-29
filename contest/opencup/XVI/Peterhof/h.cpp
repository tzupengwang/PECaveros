#include <bits/stdc++.h>
using namespace std;
#define N 111
int n , l[ N ] , r[ N ];
double ans , dp[ 2 ][ N ];
int main(){
  cin >> n;
  for( int i = 0 ; i < n ; i ++ )
    cin >> l[ i ] >> r[ i ];
  for( int i = -100 ; i < 100 ; i ++ ){
    {
      for( int j = 0 ; j <= n ; j ++ )
        dp[ 1 ][ j ] = 0;
      dp[ 1 ][ 0 ] = 1;
      for( int j = 0 ; j < n ; j ++ ){
        int now = j & 1 , pre = 1 - now;
        for( int k = 0 ; k <= n ; k ++ )
          dp[ now ][ k ] = 0;
        double in = ( l[ j ] <= i and r[ j ] > i ? 1. / (r[ j ] - l[ j ]) : 0 );
        double lft = ( l[ j ] < i ? min( 1. , (double)( i - l[ j ] ) / ( r[ j ] - l[ j ] ) ) : 0 );
        for( int k = 0 ; k <= n ; k ++ ){
          dp[ now ][ k ] += dp[ pre ][ k ] * lft;
          if( k )
            dp[ now ][ k ] += dp[ pre ][ k - 1 ] * in;
        }
      }
      int lst = (n + 1) & 1;
      for( int j = 2 ; j <= n ; j ++ )
        ans += dp[ lst ][ j ] * ( (double)((j + 1) * i + j - 1) / (j + 1) );
        //ans += dp[ lst ][ j ] * ( j - 1 ) / ( j + 1 );
    }
    for( int mxi = 0 ; mxi < n ; mxi ++ ){
      for( int j = 0 ; j <= n ; j ++ )
        dp[ 1 ][ j ] = 0;
      dp[ 1 ][ 0 ] = 1;
      for( int j = 0 ; j < n ; j ++ ){
        int now = j & 1 , pre = 1 - now;
        for( int k = 0 ; k <= n ; k ++ )
          dp[ now ][ k ] = 0;
        if( j != mxi ){
          double in = ( l[ j ] <= i and r[ j ] > i ? 1. / (r[ j ] - l[ j ]) : 0 );
          double lft = ( l[ j ] < i ? min( 1. , (double)( i - l[ j ] ) / ( r[ j ] - l[ j ] ) ) : 0 );
          for( int k = 0 ; k <= n ; k ++ ){
            dp[ now ][ k ] += dp[ pre ][ k ] * lft;
            if( k )
              dp[ now ][ k ] += dp[ pre ][ k - 1 ] * in;
          }
        }else{
          double rgt = ( r[ j ] > i ? min( 1. , (double)( r[ j ] - (i + 1) ) / (r[ j ] - l[ j ]) ) : 0 );
          for( int k = 0 ; k <= n ; k ++ )
            dp[ now ][ k ] = dp[ pre ][ k ] * rgt;
        }
      }
      int lst = (n + 1) & 1;
      for( int j = 1 ; j <= n ; j ++ )
        ans += dp[ lst ][ j ] * (double)((j + 1) * i + j) / ( j + 1 );
        //ans += dp[ lst ][ j ] * j / ( j + 1 );
    }
  }
  printf( "%.12f\n" , ans );
}
