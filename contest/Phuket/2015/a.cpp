#include <bits/stdc++.h>
using namespace std;
#define N 1021
char c[ N ];
int trans( char ctmp ){
  if( ctmp >= '0' && ctmp <= '9' )
    return ctmp - '0';
  return ctmp - 'A' + 10;
}
int main(){
  while( scanf( "%s" , c ) == 1 ){
    int len = strlen( c );
    for( int i = 0 ; i < len ; i += 2 ){
      int v1 = trans( c[ i ] );
      int v2 = trans( c[ i + 1 ] );
      putchar( (char)( v1 * 16 + v2 ) );
    }
    puts( "" );
  }
}
