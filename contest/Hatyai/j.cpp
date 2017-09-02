#include <bits/stdc++.h>
using namespace std;
string ans;
char c[ 10101 ];
bool is_c( char ctmp ){
  if( 'A' <= ctmp and ctmp <= 'Z' ) return true;
  if( 'a' <= ctmp and ctmp <= 'z' ) return true;
  return ctmp == '-';
}
char lower( char ctmp ){
  if( 'A' <= ctmp and ctmp <= 'Z' ) return ctmp - 'A' + 'a';
  return ctmp;
}
int main(){
  while( scanf( "%s" , c ) == 1 ){
    int len = strlen( c );
    string tmp = "";
    for( int i = 0 ; i <= len ; i ++ )
      if( i == len or !is_c( c[ i ] ) ){
        if( tmp.length() > ans.length() )
          ans = tmp;
        tmp = "";
      }else
        tmp += lower( c[ i ] );
  }
  cout << ans << endl;
}
