#include <bits/stdc++.h>
using namespace std;
#define N 1021
typedef long long LL;
LL n , d , dst[ N ] , rp[ N ];
void init(){
  scanf( "%lld%lld" , &n , &d );
  for( int i = 0 ; i <= n + 1 ; i ++ )
    scanf( "%lld" , &dst[ i ] );
  for( int i = 0 ; i <= n ; i ++ )
    scanf( "%lld" , &rp[ i ] );
}
LL dp[ N ][ N ];
bool got[ N ][ N ];
int _cs;
void solve(){
  for( int i = 0 ; i <= n + 1 ; i ++ )
    for( int j = 0 ; j <= n + 1 ; j ++ )
      got[ i ][ j ] = false;
  dp[ n + 1 ][ 0 ] = 0;
  got[ n + 1 ][ 0 ] = true;
  for( int i = n + 1 ; i ; i -- ){
    for( int j = 0 ; j <= n + 1 - i ; j ++ ){
      if( !got[ i ][ j ] ) continue;
      // swim
      if( !got[ i - 1 ][ j + 1 ] ||
          dp[ i ][ j ] + rp[ i - 1 ] - ( dst[ i ] - dst[ i - 1 ] ) > dp[ i - 1 ][ j + 1 ] ){
        got[ i - 1 ][ j + 1 ] = true;
        dp[ i - 1 ][ j + 1 ] = dp[ i ][ j ] + rp[ i - 1 ] - ( dst[ i ] - dst[ i - 1 ] );
      }
      // jump
      LL ret = dp[ i ][ j ] + min( rp[ i - 1 ] , d ) - ( dst[ i ] - dst[ i - 1 ] );
      if( ret < 0 ) continue;
      if( !got[ i - 1 ][ j ] ||
          ret > dp[ i - 1 ][ j ] ){
        got[ i - 1 ][ j ] = true;
        dp[ i - 1 ][ j ] = ret;
      }
    }
    //for( int j = 0 ; j <= n ; j ++ )
      //if( got[ i - 1 ][ j ] ){
        //printf( "%d %d %lld\n" , i - 1 , j , dp[ i - 1 ][ j ] );
      //}
  }
  int ans = n + 1;
  for( int i = 0 ; i <= n ; i ++ )
    if( got[ 0 ][ i ] ){
      ans = i;
      break;
    }
  printf( "Case %d: %d\n" , ++ _cs , ans );
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
