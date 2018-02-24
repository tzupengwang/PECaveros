#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 33
const int inf = 1e9;
int n , m , d[ N ][ N ] , mxh;
int dp[ 2 ][ 1 << 18 ][ 18 ];
int _cs;
int main(){
  while( cin >> n >> m ){
    for( int i = 0 ; i < n ; i ++ ){
      for( int j = 0 ; j < n ; j ++ )
        d[ i ][ j ] = inf;
      d[ i ][ i ] = 0;
    }
    while( m -- ){
      int ui , vi , di;
      cin >> ui >> vi >> di;
      d[ ui ][ vi ] = min( d[ ui ][ vi ] , di );
      d[ vi ][ ui ] = min( d[ vi ][ ui ] , di );
    }
    for( int k = 0 ; k < n ; k ++ )
      for( int i = 0 ; i < n ; i ++ )
        for( int j = 0 ; j < n ; j ++ )
          d[ i ][ j ] = min( d[ i ][ j ] , d[ i ][ k ] + d[ k ][ j ] );
    mxh = min( (n + 2) / 2 , n - 2); 
    for( int s = 0 ; s < 2 ; s ++ )
      for( int i = 0 ; i < (1 << (n - 2)) ; i ++ )
        for( int j = 0 ; j < n - 2 ; j ++ )
          dp[ s ][ i ][ j ] = inf;
    for( int s = 0 ; s < 2 ; s ++ ){
      for( int i = 1 ; i < (1 << (n - 2)) ; i ++ ){
        if( __builtin_popcount( i ) > mxh ) continue;
        if( i == (i & (-i)) )
          dp[ s ][ i ][ __lg( i ) ] = d[ s * (n - 1) ][ 1 + __lg( i ) ];
        for( int j = 0 ; j < n - 2 ; j ++ ){
          if( dp[ s ][ i ][ j ] == inf ) continue;
          for( int k = 0 ; k < n - 2 ; k ++ ){
            if( (i >> k) & 1 ) continue;
            dp[ s ][ i | (1 << k) ][ k ] = min(
              dp[ s ][ i | (1 << k) ][ k ] ,
              dp[ s ][ i ][ j ] + d[ 1 + j ][ 1 + k ] );
          }
        }
      }
    }
    int ans = inf , goal = (n - 2) / 2;
    for( int i = 0 ; i < (1 << (n - 2)) ; i ++ ){
      if( __builtin_popcount( i ) != goal ) continue;
      int lbst = inf , rbst = inf;
      for( int j = 0 ; j < (n - 2) ; j ++ ){
        if( !((i >> j) & 1) ) continue;
        int oi = ((1 << (n - 2)) - 1) ^ i ^ (1 << j);
        lbst = min( lbst ,
                   dp[ 0 ][ i ][ j ] +
                   dp[ 1 ][ oi ][ j ] );
        rbst = min( rbst ,
                   dp[ 1 ][ i ][ j ] +
                   dp[ 0 ][ oi ][ j ] );
      }
      ans = min( ans , lbst + rbst );
    }
    if( n == 3 ) ans = ( d[ 0 ][ 1 ] + d[ 1 ][ 2 ] ) * 2;
    printf( "Case %d: %d\n" , ++ _cs , ans );
  }
}
