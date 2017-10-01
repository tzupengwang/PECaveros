#include <bits/stdc++.h>
using namespace std;
#define N 1021
char trans( int x ){
  return x < 10 ? x + '0' : x - 10 + 'A';
}
char c[ N ];
int main(){
  int t; cin >> t; while( t -- ){
    scanf( "%s" , c );
    int len = strlen( c );
    string ans = "";
    for( int i = len - 1 ; i >= 0 ; i -= 4 ){
      int vl = 0;
      for( int j = -3 ; j <= 0 ; j ++ )
        vl = vl * 2 + ( i + j < 0 ? 0 : c[ i + j ] - '0' );
      ans += trans( vl );
    }
    reverse( ans.begin() , ans.end() );
    cout << ans << endl;
  }
}
