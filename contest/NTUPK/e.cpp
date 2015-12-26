#include <bits/stdc++.h>
using namespace std;
#define N 10010001
typedef long long ll;
ll n , m;
void init(){
  scanf( "%lld%lld" , &n , &m );
  if( n > m ) swap( n , m );
}
ll sv[ N ];
void solve(){
  for( int i = 0 ; i <= n ; i ++ ) sv[ i ] = 0;
  for( ll i = 3 ; i <= m ; i += 2 ){
    for( ll j = i + i + i ; i + j <= m ; j += i + i )
      sv[ j ] ++;
  }
  ll ans = 0;
  for( ll i = 3 ; i <= n ; i += 2 ){
    ll mx = m - i;
    if( mx % 2 == 0 ) mx --;
    mx = min( mx , i - 2 );
    printf( "%lld %lld\n" , i , mx );
    ll sum = ( mx - 1ll ) / 2ll + 1ll;
    ans += sum - sv[ i ];
  }
  printf( "%lld\n" , ans );
}
int main(){
  int _; scanf( "%d" , &_ );
  while( _ -- ){
    init();
    solve();
  }
}
