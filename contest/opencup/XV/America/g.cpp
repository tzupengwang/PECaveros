#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
string s;
bool okay( string ss ){
  string ts = s;
  int slen = ss.length();
  while( ts.length() > 0 ){
    bool good = false;
    int tlen = ts.length();
    for( int i = 0 ; i <= tlen - slen ; i ++ )
      if( ts.substr( i , slen ) == ss ){
        ts = ts.substr( 0 , i ) + ts.substr( i + slen , tlen );
        good = true;
        break;
      }
    if( not good )
      return false;
  }
  return true;
}
int main(){
  cin >> s;
  int len = s.length();
  string ans = s;
  for( int i = 0 ; i < len ; i ++ )
    for( int j = i ; j < len ; j ++ ){
      string tmp = s.substr( i , j - i + 1 );
      if( tmp.length() >= ans.length() )
        continue;
      if( okay( tmp ) )
        ans = tmp;
    }
  cout << ans << endl;
}
