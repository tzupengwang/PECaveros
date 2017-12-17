#include <bits/stdc++.h>
using namespace std;
char c[ 1048576 ];
int dgt( int x ){
  if( x < 10 ) return x;
  int r = 0;
  while( x ){
    r += x % 10;
    x /= 10;
  }
  return dgt( r );
}
bool is(){
  int len = strlen( c );
  if( len < 19 ){
    LL x;
    sscanf( c , "%lld" , &x );
    LL cand = sqrtl( x );
    while( cand * cand < x ) cand ++;
    while( cand * cand > x ) cand --;
    return cand * cand == x;
  }
  int s = 0;
  for( int i = 0 ; c[ i ] ; i ++ )
    s += c[ i ] - '0';
  int d = dgt( s );
  if( c[ len - 1 ] == '2' ) return false;
  if( c[ len - 1 ] == '3' ) return false;
  if( c[ len - 1 ] == '7' ) return false;
  if( c[ len - 1 ] == '8' ) return false;
  int cc = 0;
  for( int i = len - 1 ; i >= 0 ; i -- )
    if( c[ i ] == '0' )
      cc ++;
    else
      break;
  if( cc & 1 ) return false;
  if( c[ len - 1 ] == '6' ){
    if( c[ len - 2 ] % 2 == 0 )
      return false;
  }else{
    if( c[ len - 2 ] % 2 == 1 )
      return false;   
  }
  if( c[ len - 1 ] == '5' and c[ len - 2 ] != '2' )
    return false;
  if( c[ len - 1 ] % 2 == 0 ){
    LL tmp = (c[ len - 2 ] - '0') * 10 + c[ len - 1 ] - '0';
    if( tmp % 4 ) return false;
  }
}
int main(){
  
}
