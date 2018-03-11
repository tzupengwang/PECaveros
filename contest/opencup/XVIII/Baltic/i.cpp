#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N (1 << 20)
int c[ N ];
bool sub( char* aa , char* bb ){
  for( int i = 0 ; i < N ; i ++ )
    c[ i ] = 0;
  int lena = strlen( aa );
  int lenb = strlen( bb );
  for( int i = 0 ; i < lena ; i ++ )
    c[ lena - i - 1 ] += aa[ i ] - '0';
  for( int i = 0 ; i < lenb ; i ++ )
    c[ lenb - i - 1 ] -= bb[ i ] - '0';
  for( int i = 0 ; i + 1 < N ; i ++ )
    if( c[ i ] < 0 ){
      c[ i ] += 10;
      c[ i + 1 ] --;
    }
  if( c[ N - 1 ] < 0 ) return false;
  int til = N - 1;
  while( til > 0 and c[ til ] == 0 ) til --;
  for( int i = til ; i >= 0 ; i -- )
    printf( "%d" , c[ i ] );
  puts( "" );
  return true;
}
char a[ N ] , b[ N ]; 
int main(){
  scanf( "%s" , a );
  scanf( "%s" , b );
  if( !strcmp( a , b ) )
    puts( "0" );
  else{
    if( sub( a , b ) )
      return 0;
    putchar( '-' );
    sub( b , a );
  }
}
