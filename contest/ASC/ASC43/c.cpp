#include <bits/stdc++.h>
using namespace std;
const int mod = 1000000009;
int add( int a , int b ){
  a += b;
  return a >= mod ? a - mod : a;
}
#define N 5050
int n , k , dp[ N ][ N ];
int main(){
  scanf( "%d%d" , &k , &n );
  dp[ 0 ][ 1 ] = 1;
  dp[ 1 ][ 1 ] = 1;
  dp[ 1 ][ 2 ] = 1;
  for( int i = 2 ; i <= k ; i ++ )
    for( int j = 0 ; j <= n ; j ++ ){
      dp[ i ][ j ] = dp[ i - 1 ][ j ];
      if( j > 1 )
        dp[ i ][ j ] = add( dp[ i ][ j ] , dp[ i ][ j - 2 ] );
    }
  for( int i = 1 ; i <= n ; i ++ )
    printf( "%d\n" , dp[ k - 1 ][ i ] );
}
