#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define K 101
#define N 101010
int n , fl[ N ] , gt[ K ] , plen , stmp;
LL dp[ K ];
char p[ N ];
bitset<N> lft[ K ] , rgt[ K ];
bitset<N+N> q;
int len[ K ];
LL DP( int i ){
  if( gt[ i ] == stmp ) return dp[ i ];
  gt[ i ] = stmp;
  if( i <= 1 ){
    LL ret = 0;
    if( plen == 1 and p[ 0 ] - '0' == i ) ret = 1;
    return dp[ i ] = ret;
  }
  LL ret = DP( i - 1 ) + DP( i - 2 );
  for( int j = 0 ; j < len[ i - 1 ] ; j ++ )
    q[ len[ i - 1 ] - j - 1 ] = rgt[ i - 1 ][ j ];
  //puts( "==>" );
  //for( int j = 0 ; j < len[ i - 1 ] ; j ++ )
    //printf( "%d" , (int)q[ j ] );
  //puts( "" );
  for( int j = 0 ; j < len[ i - 2 ] ; j ++ )
    q[ len[ i - 1 ] + j     ] = lft[ i - 2 ][ j ];
  int totlen = len[ i - 1 ] + len[ i - 2 ];
  //puts( "==>" );
  //for( int j = 0 ; j < totlen ; j ++ )
    //printf( "%d" , (int)q[ j ] );
  //puts( "" );
  for( int j = 0 , f = -1 ; j < totlen ; j ++ ){
    while( f >= 0 and p[ f + 1 ] - '0' != q[ j ] )
      f = fl[ f ];
    if( p[ f + 1 ] - '0' == q[ j ] ) f ++;
    if( f + 1 == plen ){
      if( j >= len[ i - 1 ] and j - plen + 1 < len[ i - 1 ] )
        ret ++;
      f = fl[ f ];
    }
  }
  return dp[ i ] = ret;
}
int _cs;
int main(){
  len[ 0 ] = 1;
  len[ 1 ] = 1;
  lft[ 1 ][ 0 ] = 1;
  rgt[ 1 ][ 0 ] = 1;
  for( int i = 2 ; i < K ; i ++ ){
    len[ i ] = min( len[ i - 1 ] + len[ i - 2 ] , 100000 );
    rgt[ i ] = (rgt[ i - 1 ] << len[ i - 2 ]) | rgt[ i - 2 ];
    lft[ i ] = (lft[ i - 2 ] << len[ i - 1 ]) | lft[ i - 1 ];
  }
  while( scanf( "%d" , &n ) == 1 ){
    scanf( "%s" , p );
    plen = strlen( p );
    fl[ 0 ] = -1;
    for( int i = 1 , f = -1 ; i < plen ; i ++ ){
      while( f >= 0 and p[ f + 1 ] != p[ i ] ) f = fl[ f ];
      if( p[ f + 1 ] == p[ i ] ) f ++;
      fl[ i ] = f;
    }
    ++ stmp;
    printf( "Case %d: %lld\n" , ++ _cs , DP( n ) );
  }
}
