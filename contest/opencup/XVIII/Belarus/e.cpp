#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 101010
const int mod = 1000000007;
LL ds( LL x ){
  LL ret = 0;
  while( x ){
    ret += x % 10;
    x /= 10;
  }
  return ret;
}
LL bf( LL n ){
  LL ret = 0;
  for( LL i = 1 ; i < n ; i ++ ){
    ret += abs( ds( i ) - ds( i + 1 ) );
    ret %= mod;
  }
  return ret;
}
char c[ N ];
int n;
LL vl[ N ];
LL ans;
int main(){
  scanf( "%s" , c + 1 );
  n = strlen( c + 1 );
  for( int i = 1 ; i <= n ; i ++ )
    vl[ i ] = (vl[ i - 1 ] * 10 + c[ i ] - '0' ) % mod;
  ans = (vl[ n ] + mod - 1) % mod;
  {
    LL tms = vl[ n - 1 ];
    ans = (ans + tms * 7) % mod;
  }
  for( int i = n - 2 ; i >= 0 ; i -- ){
    LL tms = vl[ i ];
    ans = (ans + tms * 9) % mod;
  }
  cout << ans << endl;
  //cerr << bf( atol( c + 1 ) ) << endl;
}
