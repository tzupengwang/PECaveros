#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL read_int(){
  char cc[ 100 ];
  scanf( "%s" , cc );
  int dd = 0;
  int len = strlen( cc );
  bool dot = false;
  LL ret = 0;
  for( int i = 0 ; i < len ; i ++ ){
    if( cc[ i ] == '.' ){
      dot = true;
      continue;
    }
    ret = ret * 10 + cc[ i ] - '0';
    if( dot ) dd ++;
  }
  while( dd < 5 ){
    ret = ret * 10;
    dd ++;
  }
  return ret;
}
int main(){
  freopen( "input.txt" , "r" , stdin );
  freopen( "output.txt" , "w" , stdout );
  int q; cin >> q; while( q -- ){
    LL w = read_int();
    LL d = read_int();
    LL l = read_int();
    LL bw = d * l;
    LL bd = w * l;
    LL bl = w * d;
    LL sb = bw + bd + bl;
    if( sb * 100000LL < bw * w and
        sb * 100000LL < bd * d and
        sb * 100000LL < bl * l )
      cout << "YES" << endl;
    else
      cout << "NO" << endl;
  }
}
