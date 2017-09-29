#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define K 22
#define N 1000010
int rmq[ K ][ N ] , lg[ N ];
char c[ N ];
int n , sc[ N ] , kk[ N ] , ans;
inline int query( int lb , int rb ){
  int bt = lg[ rb - lb + 1 ];
  return min( rmq[ bt ][ lb ] ,
              rmq[ bt ][ rb - (1 << bt) + 1 ] );
}
int main(){
  for( int i = 0 ; i < N ; i ++ )
    lg[ i ] = __lg( i );
  scanf( "%s" , c + 1 );
  n = strlen( c + 1 );
  for( int i = 1 ; i <= n ; i ++ ){
    sc[ i ] = sc[ i - 1 ] + ( c[ i ] == 'M' );
    kk[ i ] = kk[ i - 1 ];
    if( c[ i ] == 'H' ) kk[ i ] ++;
    if( c[ i ] == 'K' ) kk[ i ] --;
    rmq[ 0 ][ i ] = kk[ i ];
  }
  for( int j = 1 ; j < K ; j ++ )
    for( int i = 1 ; i + (1 << j) - 1 <= n ; i ++ )
      rmq[ j ][ i ] = min( rmq[ j - 1 ][ i ] ,
                           rmq[ j - 1 ][ i + (1 << (j - 1)) ] );
  for( int i = 1 ; i <= n ; i ++ ){
    int lb = i , rb = n , ba = 0;
    while( lb <= rb ){
      int mid = (lb + rb) >> 1;
      if( query( i , mid ) >= kk[ i - 1 ] )
        ba = mid , lb = mid + 1;
      else
        rb = mid - 1;
    }
    if( i <= ba )
      ans = max( ans , sc[ ba ] - sc[ i - 1 ] );
  }
  cout << ans << endl;
}
