#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL mod = 1000000007;
LL n , ans , bst;
#define N 514
LL dp[ N ][ N ] , pdp[ N ];
void init(){
  scanf( "%lld" , &n );
  dp[ 0 ][ N - 1 ] = 1;
  for( int i = 0 ; i + 1 < N ; i ++ ){
    for( int j = 0 ; j < N ; j ++ ){
      if( dp[ i ][ j ] == 0 ) continue;
      for( int k = 1 ; k <= j && i + k < N ; k ++ )
        dp[ i + k ][ k ] = ( dp[ i + k ][ k ] + dp[ i ][ j ] ) % mod;
    }
    for( int j = 0 ; j < N ; j ++ )
      pdp[ i ] = ( pdp[ i ] + dp[ i ][ j ] ) % mod;
  }
  //for( int i = 0 ; i <= n ; i ++ )
    //printf( "%d %lld\n" , i , pdp[ i ] );
}
void solve(){
  bst = mod * mod;
  ans = 0;
  for( LL i = 1 ; i <= n ; i ++ ){
    LL j = n / i + ( n % i != 0 );
    if( 2 * ( i + j ) > bst ) continue;
    LL len = 2 * ( i + j );
    LL res = i * j - n , tans = 0;
    //printf( "%lld %lld %lld %lld\n" , i , j , len );
    for( LL a1 = 0 ; a1 <= res ; a1 ++ )
      for( LL a2 = 0 ; a1 + a2 <= res ; a2 ++ )
        for( LL a3 = 0 ; a1 + a2 + a3 <= res ; a3 ++ ){
          LL cnt = 1;
          cnt = ( cnt * pdp[ a1 ] ) % mod;
          cnt = ( cnt * pdp[ a2 ] ) % mod;
          cnt = ( cnt * pdp[ a3 ] ) % mod;
          cnt = ( cnt * pdp[ res - a1 - a2 - a3 ] ) % mod;
          tans = ( tans + cnt ) % mod;
        }
    if( len == bst ){
      ans = ( ans + tans ) % mod;
    }else{
      bst = len;
      ans = tans;
    }
  }
  cout << ans << endl;
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "expedition.in" , "r" , stdin );
  freopen( "expedition.out" , "w" , stdout );
#endif
  init();
  solve();
}
