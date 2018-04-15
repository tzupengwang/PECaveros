#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 101010
LL t , n , a[ N ];
int cs;
int main(){
  scanf( "%lld" , &t ); while( t -- ){
    scanf( "%lld" , &n );
    for( LL i = 0 ; i < n ; i ++ )
      scanf( "%lld" , &a[ i ] );
    sort( a , a + n );
    LL ans = 0;
    for( LL i = 0 ; i < n ; i ++ ){
      if( i % 3 == 2 ) continue;
      ans += a[ n - i - 1 ];
    }
    printf( "Case #%d: %lld\n" , ++ cs , ans );
  }
}
