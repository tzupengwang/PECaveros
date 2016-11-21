#include <bits/stdc++.h>
using namespace std;
#define N 1021
#define M 10
int to[ N ] , now[ N ] , n , m , bad[ N ];
void init(){
  scanf( "%d%d" , &n , &m );
  for( int i = 0 ; i < m ; i ++ ){
    int x; scanf( "%d" , &x );
    bad[ x ] = 1;
  }
  for( int i = 2 ; i <= n ; i ++ ){
    char c[ 9 ]; scanf( "%s" , c );
    if( c[ 0 ] == 'h' ) to[ i ] = 0;
    else to[ i ] = 1;
    now[ i ] = to[ i ];
  }
}
// 0 good
int cc[ N ][ 2 ];
void solve(){
  for( int i = 1 ; i <= m ; i ++ ){
    for( int j = 1 ; j <= n ; j ++ )
      cc[ j ][ 0 ] = cc[ j ][ 1 ] = 0;
    for( int j = 1 ; j <= n ; j ++ )
      for( int k = 1 ; k <= n ; k ++ ){
        if( j == k ) continue;
        if( k == 1 )
          cc[ j ][ to[ j ] ] ++;
        else
          cc[ j ][ bad[ k ] ? 1 : now[ k ] ] ++;
      }
    for( int j = 1 ; j <= n ; j ++ )
      if( cc[ j ][ 0 ] > cc[ j ][ 1 ] )
        now[ j ] = 0;
      else
        now[ j ] = 1;
  }
  for( int i = 2 ; i <= n ; i ++ )
    if( !bad[ i ] )
      puts( now[ i ] ? "cat" : "hat" );
}
int main(){
  init();
  solve();
}
