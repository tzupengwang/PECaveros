#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = 1000000007;
inline int parity( LL x ){
  return __builtin_popcountll( x ) % 2;
}
pair<LL,LL> count( LL l , LL r ){
  LL odd = 0 , even = 0;
  if( r - l < 10 ){
    for( LL i = l ; i <= r ; i ++ )
      if( parity( i ) )
        odd ++;
      else
        even ++;
    return { odd , even };
  }
  if( l & 1LL ){
    if( parity( l ) ) odd ++;
    else even ++;
    l ++;
  }
  if( !( r & 1LL ) ){
    if( parity( r ) ) odd ++;
    else even ++;
    r --;
  }
  LL hf = (r - l + 1) / 2;
  return { odd + hf , even + hf };
}
LL o = 0 , e = 0;
int ans , n;
LL ql , qr;
int main(){
  scanf( "%d" , &n ); while( n -- ){
    scanf( "%lld%lld" , &ql , &qr );
    pair<LL,LL> q = count( ql , qr );
    LL co = q.first % mod;
    LL ce = q.second % mod;
    ans = (ans + o * ce) % mod;
    ans = (ans + e * co) % mod;
    o = (o + co) % mod;
    e = (e + ce) % mod;
  }
  cout << ans << endl;
}
