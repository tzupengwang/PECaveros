#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 514
char buf[ N ];
bool is_cap( int l , int r ){
  if( r - l + 1 <= 1 ) return false;
  if( !isupper( buf[ l ] ) ) return false;
  for( int i = l + 1 ; i <= r ; i ++ )
    if( !islower( buf[ i ] ) )
      return false;
  return true;
}
int til[ N ];
int main(){
  freopen( "abbreviation.in" , "r" , stdin );
  freopen( "abbreviation.out" , "w" , stdout );
  while( fgets( buf , N , stdin ) ){
    vector<string> cand;
    int len = strlen( buf );
    for( int i = 0 ; i < len ; i ++ )
      if( isalpha( buf[ i ] ) ){
        til[ i ] = i;
        while( til[ i ] < len and isalpha( buf[ til[ i ] ] ) )
          til[ i ] ++;
      }
    for( int i = 0 ; i < len ; ){
      if( !isalpha( buf[ i ] ) ){
        putchar( buf[ i ++ ] );
        continue;
      }
      if( is_cap( i , til[ i ] - 1 ) and
          buf[ til[ i ]     ] == ' ' and
          isupper( buf[ til[ i ] + 1 ] ) and 
          is_cap( til[ i ] + 1 , til[ til[ i ] + 1 ] - 1 ) ){
        string abbr = "";
        abbr += buf[ i ];
        abbr += buf[ til[ i ] + 1 ];
        int s = i , t = til[ til[ i ] + 1 ] - 1;
        while( buf[ t + 1 ] == ' ' and
               is_cap( t + 2 , til[ t + 2 ] - 1 ) ){
          abbr += buf[ t + 2 ];
          t = til[ t + 2 ] - 1;
        }
        i = t + 1;
        printf( "%s " , abbr.c_str() );
        putchar( '(' );
        for( int j = s ; j <= t ; j ++ )
          putchar( buf[ j ] );
        putchar( ')' );
      }else{
        for( int j = i ; j < til[ i ] ; j ++ )
          putchar( buf[ j ] );
        i = til[ i ];
        continue;
      }
    }
  }
}
