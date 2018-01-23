#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 1515
bitset<N> b[ N ];
int n , k;
int main(){
  scanf( "%d%d" , &n , &k );
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 , x ; j < k ; j ++ ){
      scanf( "%d" , &x );
      b[ j ][ i ] = abs(x) & 1;
    }
  int dim = 0;
  for( int i = 0 ; i < n ; i ++ ){
    int p = dim;
    while( p < k and !b[ p ][ i ] ) p ++;
    if( p == k ) continue;
    swap( b[ p ] , b[ dim ] );
    for( int j = 0 ; j < k ; j ++ ){
      if( dim == j ) continue;
      if( !b[ j ][ i ] ) continue;
      b[ j ] ^= b[ dim ];
    }
    dim ++;
  }
  for( int j = 0 ; j < n ; j ++ ){
    int sum = 0;
    for( int i = 0 ; i < k ; i ++ )
      if( b[ i ][ j ] )
        sum = 1 - sum;
    if( !sum ){
      puts( "No" );
      exit(0);
    }
  }
  puts( "Yes" );
}
