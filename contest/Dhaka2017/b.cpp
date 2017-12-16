#include <bits/stdc++.h>
using namespace std;
bool can( char cl , char cr ){
  if( cl == '('  and cr == ')' ) return true;
  if( cl == '['  and cr == ']' ) return true;
  if( cl == '{'  and cr == '}' ) return true;
  if( cl == '<'  and cr == '>' ) return true;
  return false;
}
#define N 101010
char c[ N ];
int cs , dp[ N ];
int main(){
  int t; scanf( "%d" , &t ); while( t -- ){
    scanf( "%s" , c );
    int len = strlen( c );
    for( int i = len ; i <= len + 3 ; i ++ )
      c[ i ] = 0;
    for( int i = 0 ; i <= len ; i ++ )
      dp[ i ] = 0;
    for( int i = len - 1 ; i >= 0 ; i -- )
      if( c[ i ] == '(' or 
          c[ i ] == '[' or
          c[ i ] == '{' or
          c[ i ] == '<' ){
        if( can( c[ i ] , c[ i + 1 ] ) )
          dp[ i ] = 2 + dp[ i + 2 ];
        else{
          int tans = dp[ i + 1 ];
          if( tans == 0 ) continue;
          if( can( c[ i ] , c[ i + tans + 1 ] ) )
            dp[ i ] = tans + 2 + dp[ i + tans + 2 ];
        }
      }
    printf( "Case %d:\n" , ++ cs );
    for( int i = 0 ; i < len ; i ++ )
      printf( "%d\n" , dp[ i ] );
  }
}
