#include<bits/stdc++.h>
using namespace std;

char s[ 330005 ] ;
int l ;
vector< int > ans ;

void go( int x ) {
  if ( s[ x ] == '1' ) s[ x ] = '0' ;
  else s[ x ] = '1' ;
  if ( s[ x + 1 ] == '1' ) s[ x + 1 ] = '0' ;
  else s[ x + 1 ] = '1' ;
  ans.push_back( x ) ;
}

int main() {
  scanf( "%s" , s ) ;
  l = strlen( s ) ;
  
  if ( s[ 0 ] == s[ 1 ] && s[ 1 ] == s[ 2 ] ) go( 1 ) ;
  for ( int i = 1 ; i * 3 < l ; i ++ ) {
    int j = i * 3 ;
    if ( s[ j - 1 ] == s[ j ] && s[ j + 1 ] == s[ j + 2 ] )
      go( j ) ;
    else if ( s[ j - 1 ] == s[ j ] && s[ j ] == s[ j + 1 ] )
      go( j + 1 ) ;
    else if ( s[ j + 2 ] == s[ j ] && s[ j ] == s[ j + 1 ] )
      go( j + 1 ) ;
  }
  printf( "%d\n" , (int)ans.size() ) ;
  for ( int i = 0 ; i < (int)ans.size() ; i ++ ) {
    printf( "%d%c" , ans[ i ] + 1 , " \n"[ i + 1 == (int)ans.size() ] ) ;
  }
  return 0 ;
}
