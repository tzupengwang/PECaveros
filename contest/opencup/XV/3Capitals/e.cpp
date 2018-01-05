#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
int move( int dir ){
  if( dir == 0 ) puts( "move north" );
  else if( dir == 1 ) puts( "move east" );
  else if( dir == 2 ) puts( "move south" );
  else if( dir == 3 ) puts( "move west" );
  fflush( stdout );
  char buf[ 512 ];
  scanf( "%s" , buf );
  if( buf[ 0 ] == 'w' ) exit(0);
  if( buf[ 0 ] == 'f' ) return 1;
  if( buf[ 0 ] == 'm' ) return 0;
  assert( false );
  return -1;
}
void echo( const char* lazi ){
  printf( "echo %s\n" , lazi );
  fflush( stdout );
  char buf[ 512 ];
  scanf( "%s" , buf );
}
int cand[]={0,3,2,2,1,1,0,0,3,2};
int main(){
  for( int i = 0 ; i < 10 ; i ++ )
    if( move( cand[ i ] ) ){
      move( cand[ i ] ^ 2 );
      for( int j = i + 1 ; j + 2 < 10 ; j ++ )
        echo( "lazi" );
      move( cand[ i ] );
      exit(0);
    }
}
