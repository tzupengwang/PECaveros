#include <bits/stdc++.h>
using namespace std;
#define N 514
int getint(){
  int x;
  scanf( "%d" , &x );
  return x;
}
int x[ N ][ N ] , cnt;
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
int main(){
  int n = getint();
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= n ; j ++ )
      x[ i ][ j ] = getint();
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= n ; j ++ )
      if( x[ i ][ j ] > 1 &&
          x[ i ][ j ] < n * n ){
        if( x[ i ][ j - 1 ] == x[ i ][ j ] - 1 &&
            x[ i ][ j + 1 ] == x[ i ][ j ] + 1 ) cnt ++;
        if( x[ i ][ j - 1 ] == x[ i ][ j ] + 1 &&
            x[ i ][ j + 1 ] == x[ i ][ j ] - 1 ) cnt ++;
        if( x[ i - 1 ][ j ] == x[ i ][ j ] - 1 &&
            x[ i + 1 ][ j ] == x[ i ][ j ] + 1 ) cnt ++;
        if( x[ i - 1 ][ j ] == x[ i ][ j ] + 1 &&
            x[ i + 1 ][ j ] == x[ i ][ j ] - 1 ) cnt ++;
        bool got1 = false , got2 = false;
        for( int k = 0 ; k < 4 ; k ++ ){
          if( x[ i + dx[ k ] ][ j + dy[ k ] ] == x[ i ][ j ] - 1 ) got1 = true;
          if( x[ i + dx[ k ] ][ j + dy[ k ] ] == x[ i ][ j ] + 1 ) got2 = true;
        }
        if( !got1 || !got2 ){
          printf( "GG %d %d\n" , i ,  j );
          exit( 0 );
        }
      }
  printf( "%d\n" , n * n - cnt );
}
