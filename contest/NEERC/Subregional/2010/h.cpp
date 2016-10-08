#include <bits/stdc++.h>
using namespace std;
#define N 101010
char cmd[ 100 ];
int n;
map< int , int > cnt;
int c1 , c2;
inline void add( int x ){
  cnt[ x ] ++;
  if( cnt[ x ] == 2 ) c1 ++;
  if( cnt[ x ] == 1 ) c2 ++;
}
inline void sub( int x ){
  if( cnt[ x ] == 0 ) return;
  cnt[ x ] --;
  if( cnt[ x ] == 1 ) c1 --;
  if( cnt[ x ] == 0 ) c2 --;
}
void solve(){
  while( n -- ){
    scanf( "%s" , cmd );
    int x; scanf( "%d" , &x );
    if( cmd[ 0 ] == 'i' ) add( x );
    else sub( x );
    if( c1 > 0 && c2 > 1 ) puts( "both" );
    else if( c1 > 0 ) puts( "homo" );
    else if( c2 > 1 ) puts( "hetero" );
    else puts( "neither" );
  }
}
int main(){
  freopen( "homo.in" , "r" , stdin );
  freopen( "homo.out" , "w" , stdout );
  scanf( "%d" , &n );
  solve();
}
