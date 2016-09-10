#include <bits/stdc++.h>
using namespace std;
#define N 101010
#define NIL -1
#define E -1
char c[ N ];
int r[ 4 ] , len = 0;
int trans( char ctmp ){
  if( ctmp == '+' ) return 0;
  if( ctmp == '-' ) return 1;
  if( ctmp == '*' ) return 2;
  return -1;
}
#define INF 9999
int cal( int a , int b , int op ){
  if( a == E || b == E ) return E;
  if( op == 0 ) a += b;
  if( op == 1 ) a -= b;
  if( op == 2 ) a *= b;
  if( a < 0 || a > INF ) a = E;
  return a;
}
void solve(){
  for( int i = 0 ; i < 4 ; i ++ )
    r[ i ] = 0;
  r[ 3 ] = NIL;
  len = strlen( c );
  for( int i = 0 ; i < len ; i ++ )
    if( '0' <= c[ i ] && c[ i ] <= '9' ){
      r[ 2 ] = r[ 2 ] * 10 + c[ i ] - '0';
      if( r[ 2 ] < 0 || r[ 2 ] > INF ) r[ 2 ] = E;
    }else{
      if( r[ 3 ] != NIL )
        r[ 1 ] = cal( r[ 1 ] , r[ 2 ] , r[ 3 ] );
      else
        r[ 1 ] = r[ 2 ];
      r[ 2 ] = 0;
      r[ 3 ] = trans( c[ i ] );
    }
  if( r[ 1 ] == E ) puts( "E" );
  else printf( "%d\n" , r[ 1 ] );
}
int main(){
  while( scanf( "%s" , c ) == 1 )
    solve();
}
