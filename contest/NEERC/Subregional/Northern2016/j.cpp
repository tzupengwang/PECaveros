#include <bits/stdc++.h>
using namespace std;
string mx[ 11 ] , two[ 9 ];
int main(){
  freopen( "java2016.in" , "r" , stdin );
  freopen( "java2016.out" , "w" , stdout );
  mx[ 0 ] = "a=? max ?";
  for( int i = 1 ; i <= 10 ; i ++ ){
    string ret = "";
    ret += (char)( i + 'a' );
    ret += "=";
    ret += (char)( i - 1 + 'a' );
    ret += " max ";
    ret += (char)( i - 1 + 'a' );
    mx[ i ] = ret;
  }
  two[ 0 ] = "l=k / d";
  for( int i = 1 ; i < 8 ; i ++ ){
    string ret = "";
    ret += (char)( 11 + i + 'a' );
    ret += "=";
    ret += (char)( 10 + i + 'a' );
    ret += " + ";
    ret += (char)( 10 + i + 'a' );
    two[ i ] = ret;
  }
  int n;
  scanf( "%d" , &n );
  if( n == 0 ){
    puts( "?/?/?" );
    exit( 0 );
  }
  bool first = true;
  string ans = "";
  for( int i = 0 ; i < 8 ; i ++ )
    if( ( n >> i ) & 1 ){
      if( first ){
        ans += (char)( 11 + i + 'a' );
        first = false;
      }else{
        ans = "(" + ans + " + " + (char)( 11 + i + 'a' ) + ")";
      }
    }
  for( int i = 0 ; i < 11 ; i ++ )
    cout << mx[ i ] << endl;
  for( int i = 0 ; i < 8 ; i ++ )
    cout << two[ i ] << endl;
  cout << ans << endl;
}
