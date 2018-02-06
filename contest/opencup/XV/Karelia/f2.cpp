#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
vector<string> s;
string to_s( int x ){
  char buf[ 32 ] = {};
  sprintf( buf , "%d" , x );
  string ret = "";
  int len = strlen( buf );
  for( int i = 0 ; i < len ; i ++ )
    ret += buf[ i ];
  return ret;
}
int main(){
  s.push_back( "2" );
  for( int i = 1 ; i < 30 ; i ++ ){
    string now = "";
    int len = s[ i - 1 ].length();
    for( int bl = 0 , br = 0 ; bl < len ; bl = br ){
      while( br < len and s[ i - 1 ][ bl ] == s[ i - 1 ][ br ] ) br ++;
      now += to_s( br - bl );
      now += s[ i - 1 ][ bl ];
    }
    s.push_back( now );
    //if (i % 3 == 0)
    //printf( "%2d %s\n" , i , s[ i ].substr( 0 , 80 ).c_str() );
    //printf( "%2d %90s\n" , i , s[ i ].substr( max( 0 , (int)s[ i ].length() - 80 ) , 80 ).c_str() );
    printf( "%d\n" , (int)s[ i ].length() );
  }
}
