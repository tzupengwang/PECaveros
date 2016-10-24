#include <bits/stdc++.h>
using namespace std;
#define N 1021
int n , a[ N ][ N ];
bool isp( int x ){
  for( int i = 2 ; i < x ; i ++ )
    if( x % i == 0 )
      return false;
  return true;
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "avangard.in" , "r" , stdin );
  freopen( "avangard.out" , "w" , stdout );
#endif
  scanf( "%d" , &n );
  if( n == 1 ){
    puts( "Yes\n1" );
    exit( 0 );
  }
  int cand = -1;
  for( int i = 2 ; i <= n - 2 ; i ++ ){
    bool okay = true;
    if( __gcd( i , n ) != 1 ) okay = false;
    for( int j = 1 ; j < n ; j ++ ){
      if( ( i * j ) % n == j )
        okay = false;
      if( ( i * ( n - j ) ) % n == j )
        okay = false;
    }
    if( okay ){
      cand = i;
      break;
    }
  }
  if( cand == -1 ){
    puts( "No" );
    exit( 0 );
  }
  for( int i = 1 , st = 0 ; i <= n ; i ++ , st = ( st + cand ) % n )
    for( int j = 1 ; j <= n ; j ++ )
      a[ i ][ j ] = ( st + j - 1 ) % n + 1;
  puts( "Yes" );
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= n ; j ++ )
      printf( "%d%c" , a[ i ][ j ] , " \n"[ j == n ] );
}
