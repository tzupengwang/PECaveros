#include <bits/stdc++.h>
using namespace std;
#define N 1010101
typedef long long LL;
LL n , a[ N ];
void init(){
  scanf( "%lld" , &n );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%lld" , &a[ i ] );
}
void solve(){
  LL mx = -1 , ans = 0;
  for( int i = n - 1 ; i >= 0 ; i -- ){
    if( mx > a[ i ] )
      ans += mx - a[ i ];
    mx = max( mx , a[ i ] );
  }
  printf( "%lld\n" , ans );
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
