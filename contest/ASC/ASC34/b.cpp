#include <bits/stdc++.h>
using namespace std;
#define N 1021
char c[ N ];
int len , v[ N ] , tv[ N ];
void solve(){
  for( int i = 0 ; i < len ; i ++ )
    v[ len - i - 1 ] = c[ i ] - '0';
  if( len % 2 ){
    int hf = ( len + 1 ) / 2;
    putchar( '1' );
    for( int i = 1 ; i < hf ; i ++ )
      putchar( '0' );
    for( int i = 1 ; i < hf ; i ++ )
      putchar( '1' );
    putchar( '0' );
    puts( "" );
    return;
  }
  int hf = len / 2;
  for( int i = 0 ; i < len ; i ++ ){
    bool okay = true;
    for( int j = i + 1 ; j < hf ; j ++ )
      if( v[ j ] == v[ len - 1 - j ] ){
        okay = false;
        break;
      }
    if( !okay || v[ i ] == 9 ) continue;
    for( int j = 0 ; j < len ; j ++ )
      tv[ j ] = v[ j ];
    tv[ i ] ++;
    if( i < hf ){
      while( tv[ i ] <= 9 && tv[ i ] == tv[ len - 1 - i ] )
        tv[ i ] ++;
    }
    if( tv[ i ] > 9 ) continue;
    for( int j = i - 1 ; j >= 0 ; j -- ){
      tv[ j ] = 0;
      if( j < hf ){
        while( tv[ j ] == tv[ len - 1 - j ] )
          tv[ j ] ++;
      }
    }
    for( int j = len - 1 ; j >= 0 ; j -- )
      printf( "%d" , tv[ j ] );
    puts( "" );
    return;
  }
  hf = ( len + 2 ) / 2;
  putchar( '1' );
  for( int i = 1 ; i < hf ; i ++ )
    putchar( '0' );
  for( int i = 1 ; i < hf ; i ++ )
    putchar( '1' );
  putchar( '0' );
  puts( "" );
  return;
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "anti.in" , "r" , stdin );
  freopen( "anti.out" , "w" , stdout );
#endif
  while( scanf( "%s" , c ) == 1 ){
    len = strlen( c );
    if( len == 1 && c[ 0 ] == '0' ) break;
    solve();
  }
}
