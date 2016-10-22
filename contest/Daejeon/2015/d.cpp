#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 101010
LL n , x[ N ] , y[ N ];
void init(){
  scanf( "%lld" , &n );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%lld%lld" , &x[ i ] , &y[ i ] );
  x[ n ] = x[ 0 ];
  y[ n ] = y[ 0 ];
}
void solve(){
  int cnt = 0;
  for( int i = 0 ; i < n ; i ++ ){
    LL ret = x[ i ] * y[ i + 1 ] - y[ i ] * x[ i + 1 ];
    if( ret < 0 ) cnt ++;
  }
  puts( cnt > 2 ? "NO" : "YES" );
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
