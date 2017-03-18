#include <bits/stdc++.h>
using namespace std;
#define N 1021
int dp[ N ][ N ] , n , m , k;
int main(){
  scanf( "%d%d%d" , &n , &m , &k );
  for( int i = 0 ; i < k ; i ++ ){
    int ai , bi; scanf( "%d%d" , &ai , &bi );
    dp[ ai ][ bi ] = 1;
  }
  for( int i = n ; i >= 1 ; i -- )
    for( int j = m ; j >= 1 ; j -- )
      dp[ i ][ j ] += max( dp[ i + 1 ][ j ] , dp[ i ][ j + 1 ] );
  if( dp[ 1 ][ 1 ] != k ){
    puts( "Impossible" );
    exit( 0 );
  }
  int nown = 1 , nowm = 1;
  while( nown != n or nowm != m ){
    int bst = 0;
    if( dp[ nown + 1 ][ nowm ] < dp[ nown ][ nowm + 1 ] )
      bst = 1;
    if( nowm == m ) bst = 0;
    if( nown == n ) bst = 1;
    if( bst == 0 ){
      putchar( 'D' );
      nown ++;
    }else{
      putchar( 'R' );
      nowm ++;
    }
  }
  puts( "" );
}
