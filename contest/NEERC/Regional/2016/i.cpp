#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define LEFT 0
#define RIGHT 1
char buf[ 16 ];
int query( int put , int dir , int gogo ){
  if( dir == LEFT )
    printf( "%d left %d\n" , put , gogo );
  else
    printf( "%d right %d\n" , put , gogo );
  fflush( stdout );
  scanf( "%s" , buf );
  if( !strcmp( buf , "treasure" ) ) exit(0);
  if( !strcmp( buf , "center" ) ) return 0;
  if( !strcmp( buf , "left" ) )  return -1;
  if( !strcmp( buf , "right" ) ) return +1;
  assert( false );
  return 1;
}
int m;
int main(){
  srand( 514514 );
  scanf( "%d" , &m );
  scanf( "%s" , buf );
  while( true )
    query( rand() % m , rand() % 2 , rand() % m );
}
