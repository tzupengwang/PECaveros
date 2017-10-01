#include <bits/stdc++.h>
using namespace std;
#define N 101010
int n , len , alen;
char c[ N ] , a[ N ];
bool gg;
void init(){
  alen = 0;
  gg = false;
  scanf( "%d" , &n ); while( n -- ){
    scanf( "%s" , c );
    len = strlen( c );
    for( int i = 0 ; i < min( len , alen ) ; i ++ )
      if( c[ i ] != a[ i ] ){
        gg = true;
        break;
      }
    if( not gg and len > alen ){
      alen = len;
      for( int i = 0 ; i < len ; i ++ )
        a[ i ] = c[ i ];
    }
  }
}
void solve(){
  if( gg ) puts( "Impossible" );
  else printf( "%d\n" , alen );
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
