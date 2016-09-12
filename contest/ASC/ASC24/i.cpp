#include <bits/stdc++.h>
using namespace std;
#define N 3030
char c[ 2 ][ N ];
int len[ 2 ];
void init(){
  for( int i = 0 ; i < 2 ; i ++ ){
    scanf( "%s" , c[ i ] + 1 );
    len[ i ] = strlen( c[ i ] + 1 );
  }
}
short dpl[ 2 ][ N ] , dpr[ 2 ][ N ];
short bstl[ N ][ N ] , bstr[ 2 ][ N ];
short bl[ N ][ N ] , cl[ 2 ][ N ];
short br[ N ][ N ] , cr[ 2 ][ N ];
void printl( int tlen , int i , int j ){
  for( int k = i - tlen + 1 ; k <= i ; k ++ )
    putchar( c[ 0 ][ k ] );
  puts( "" );
}
void printr( int tlen , int i , int j ){
  for( int k = i ; k < i + tlen ; k ++ )
    putchar( c[ 0 ][ k ] );
  puts( "" );
}
void solve(){
  for( int i = 1 ; i <= len[ 0 ] ; i ++ ){
    int now = i , pre = i - 1;
    for( int j = 1 ; j <= len[ 1 ] ; j ++ ){
      if( c[ 0 ][ i ] != c[ 1 ][ j ] )
        dpl[ now & 1 ][ j ] = 0;
      else
        dpl[ now & 1 ][ j ] = dpl[ 1 - ( now & 1 ) ][ j - 1 ] + 1;
      bl[ now ][ j ] = i;
      br[ now ][ j ] = j;
      bstl[ now ][ j ] = dpl[ now & 1 ][ j ];
      if( bstl[ now ][ j - 1 ] > bstl[ now ][ j ] ){
        bstl[ now ][ j ] = bstl[ now ][ j - 1 ];
        bl[ now ][ j ] = bl[ now ][ j - 1 ];
        br[ now ][ j ] = br[ now ][ j - 1 ];
      }
      if( bstl[ pre ][ j ] > bstl[ now ][ j ] ){
        bstl[ now ][ j ] = bstl[ pre ][ j ];
        bl[ now ][ j ] = bl[ pre ][ j ];
        br[ now ][ j ] = br[ pre ][ j ];
      }
    }
  }
  int bst = 0 , bi = 0 , bj = 0 , tbstl = 0 , tbstr = 0 , ci = 0 , cj = 0;
  for( int i = len[ 0 ] ; i >= 1 ; i -- ){
    int now = i & 1 , pre = 1 - now;
    for( int j = 1 ; j <= len[ 1 ] ; j ++ )
      bstr[ now ][ j ] = dpr[ now ][ j ] = 0;
    for( int j = len[ 1 ] ; j >= 1 ; j -- ){
      if( c[ 0 ][ i ] != c[ 1 ][ j ] )
        dpr[ now ][ j ] = 0;
      else
        dpr[ now ][ j ] = dpr[ pre ][ j + 1 ] + 1;
      cl[ now ][ j ] = i;
      cr[ now ][ j ] = j;
      bstr[ now ][ j ] = dpr[ now ][ j ];
      if( bstr[ now ][ j + 1 ] > bstr[ now ][ j ] ){
        bstr[ now ][ j ] = bstr[ now ][ j + 1 ];
        cl[ now ][ j ] = cl[ now ][ j + 1 ];
        cr[ now ][ j ] = cr[ now ][ j + 1 ];
      }
      if( bstr[ pre ][ j ] > bstr[ now ][ j ] ){
        bstr[ now ][ j ] = bstr[ pre ][ j ];
        cl[ now ][ j ] = cl[ pre ][ j ];
        cr[ now ][ j ] = cr[ pre ][ j ];
      }
      if( bstr[ now ][ j ] + bstl[ i - 1 ][ j - 1 ] > bst ){
        bst = bstr[ now ][ j ] + bstl[ i - 1 ][ j - 1 ];
        bi = bl[ i - 1 ][ j - 1 ];
        bj = br[ i - 1 ][ j - 1 ];
        ci = cl[ now ][ j ];
        cj = cr[ now ][ j ];
        tbstl = bstl[ i - 1 ][ j - 1 ];
        tbstr = bstr[ now ][ j ];
      }
    }
  }
  if( bst == 0 ){
    puts( "" );
    puts( "" );
    exit( 0 );
  }
  // printf( "%d %d %d %d\n" , bi , bj , ci , cj );
  printl( tbstl , bi , bj );
  printr( tbstr , ci , cj );
}
int main(){
  freopen( "subpair.in" , "r" , stdin );
  freopen( "subpair.out" , "w" , stdout );
  init();
  solve();
}
