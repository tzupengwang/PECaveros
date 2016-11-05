#include <bits/stdc++.h>
using namespace std;
#define N 2020
typedef long long LL;
LL n , l , a[ N ];
void init(){
  scanf( "%lld%lld" , &n , &l );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%lld" , &a[ i ] );
  sort( a , a + n );
}
int _cs;
void solve(){
  LL ac = 0 , lst = 0 , pen = 0 , tt = 0;
  for( int i = 0 ; i < n ; i ++ ){
    tt += a[ i ];
    if( tt > l ) break;
    ac ++;
    lst = tt;
    pen += tt;
  }
  printf( "Case %d: %lld %lld %lld\n" , ++ _cs , ac , lst , pen );
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
