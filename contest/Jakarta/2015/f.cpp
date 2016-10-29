#include <bits/stdc++.h>
using namespace std;
#define N 514
int n , a[ N ][ 3 ] , nxt[ N ];
void init(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ ){
    for( int j = 0 ; j < 3 ; j ++ )
      scanf( "%d" , &a[ i ][ j ] );
    nxt[ i ] = 0;
    while( nxt[ i ] < 3 && a[ i ][ nxt[ i ] ] == 0 ) nxt[ i ] ++;
  }
}
int tt[ 3 ] , _cs , ot[ N ];
void solve(){
  for( int i = 0 ; i < 3 ; i ++ )
    tt[ i ] = 0;
  for( int i = 0 ; i < n ; i ++ )
    ot[ i ] = 0;
  while( true ){
    int wt[ 3 ] = { -1 , -1 , -1 };
    int nt[ 3 ] = {};
    int mn[ 3 ] = {};
    for( int i = 0 ; i < 3 ; i ++ )
      mn[ i ] = 1023456789;
    for( int i = 0 ; i < n ; i ++ ){
      if( nxt[ i ] == 3 ) continue;
      mn[ nxt[ i ] ] = min( mn[ nxt[ i ] ] , ot[ i ] );
    }
    for( int i = 0 ; i < 3 ; i ++ )
      mn[ i ] = max( mn[ i ] , tt[ i ] );
    for( int i = 0 ; i < n ; i ++ ){
      if( nxt[ i ] == 3 ) continue;
      if( ot[ i ] <= mn[ nxt[ i ] ] ){
        if( wt[ nxt[ i ] ] == -1 ){
          wt[ nxt[ i ] ] = i;
          nt[ nxt[ i ] ] = mn[ nxt[ i ] ];
        }
      }
    }
    int which = -1;
    for( int i = 0 ; i < 3 ; i ++ ){
      if( wt[ i ] == -1 ) continue;
      if( which == -1 || nt[ i ] < nt[ which ] )
        which = i;
    }
    if( which == -1 ) break;
    int who = wt[ which ];
    ot[ who ] = mn[ which ] + a[ who ][ which ];
    tt[ which ] = mn[ which ] + a[ who ][ which ];
    nxt[ who ] ++;
    while( nxt[ who ] < 3 && a[ who ][ nxt[ who ] ] == 0 ) nxt[ who ] ++;
  }
  int ans = 0;
  for( int i = 0 ; i < 3 ; i ++ )
    ans = max( ans , tt[ i ] );
  printf( "Case #%d: %d\n" , ++ _cs , ans );
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
