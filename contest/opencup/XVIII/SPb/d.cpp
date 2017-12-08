#include <bits/stdc++.h>
using namespace std;
#define N 300
inline int read(){
  char c[ 128 ];
  scanf( "%s" , c );
  if( c[ 0 ] == 'X' ) return -1;
  int x; sscanf( c , "%d" , &x );
  return x;
}
int n , m , a[ N ][ N ];
const int inf = 1e8;
int d[ N ][ N ];
int main(){
  cin >> n >> m;
  for( int i = 0 ; i < m ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      a[ i ][ j ] = read();
  for( int i = 0 ; i < m ; i ++ )
    for( int j = 0 ; j < m ; j ++ )
      d[ i ][ j ] = inf;
  for( int i = 0 ; i < m ; i ++ )
    for( int j = 0 ; j < m ; j ++ ){
      if( i == j ) continue;
      int dlt = -1;
      for( int k = 0 ; k < n ; k ++ )
        if( a[ i ][ k ] != -1 and
            a[ j ][ k ] != -1 and
            a[ i ][ k ] < a[ j ][ k ] ){
          dlt = a[ j ][ k ] - a[ i ][ k ];
          break;
        }
      if( dlt == -1 ) continue;
      d[ i ][ j ] = dlt;
      break;
    }
  for( int k = 0 ; k < m ; k ++ )
    for( int i = 0 ; i < m ; i ++ )
      for( int j = 0 ; j < m ; j ++ )
        d[ i ][ j ] = min( d[ i ][ j ] , d[ i ][ k ] + d[ k ][ j ] );
  for( int i = 0 ; i < m ; i ++ )
    if( d[ i ][ i ] < inf ){
      printf( "%d\n" , d[ i ][ i ] );
      exit(0);
    }
  puts( "-1" );
}
