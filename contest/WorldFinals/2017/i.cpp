#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 514
bool can[ 26 ][ 26 ];
int n , m , len[ 2 ];
char buf[ 2 ][ N ];
int main(){
  scanf( "%d%d" , &n , &m );
  while( n -- ){
    scanf( "%s%s" , buf[ 0 ] , buf[ 1 ] );
    can[ buf[ 0 ][ 0 ] - 'a' ][ buf[ 1 ][ 0 ] - 'a' ] = true;
  }
  for( int i = 0 ; i < 26 ; i ++ )
    can[ i ][ i ] = true;
  for( int k = 0 ; k < 26 ; k ++ )
    for( int i = 0 ; i < 26 ; i ++ )
      for( int j = 0 ; j < 26 ; j ++ )
        if( can[ i ][ k ] and can[ k ][ j ] )
          can[ i ][ j ] = true;
  while( m -- ){
    scanf( "%s%s" , buf[ 0 ] , buf[ 1 ] );
    len[ 0 ] = strlen( buf[ 0 ] );
    len[ 1 ] = strlen( buf[ 1 ] );
    if( len[ 0 ] != len[ 1 ] ){
      puts( "no" );
      continue;
    }
    bool ok = true;
    for( int i = 0 ; i < len[ 0 ] ; i ++ )
      if( not can[ buf[ 0 ][ i ] - 'a' ][ buf[ 1 ][ i ] - 'a' ] ){
        ok = false;
        break;
      }
    if( not ok )
      puts( "no" );
    else
      puts( "yes" );
  }
}
