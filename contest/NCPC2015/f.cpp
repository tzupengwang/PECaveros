#include <bits/stdc++.h>
using namespace std;
#define N 1000010
int p , n , __ = 1;
typedef long long ll;
ll inv[ N ];
ll mypow( ll a , ll b ){
  if( b == 0 ) return 1ll % p;
  ll tmp = mypow( a , b / 2 );
  tmp = ( tmp * tmp ) % p;
  if( b & 1 ) tmp = ( tmp * a ) % p;
  return tmp;
}
void build(){
  for( ll i = 1 ; i < N ; i ++ )
    inv[ i ] = mypow( i , p - 2 );
}
ll x[ N ] , y[ N ];
void solve(){
  for( int i = 0 ; i < n ; i ++ )
    cin >> x[ i ] >> y[ i ];
  ll ans = 0;
  for( int i = 0 ; i < n ; i ++ ){
    ll tmp = y[ i ] % p;
    for( int j = 0 ; j < n ; j ++ )
      if( i != j ){
        tmp = ( tmp * ( -x[ j ] ) ) % p;
        tmp = ( tmp + p ) % p;
        ll ttt = ( x[ i ] - x[ j ] ) % p;
        ttt = ( ttt + p ) % p;
        tmp = ( tmp * inv[ ttt ] ) % p;
      }
    ans = ( ans + tmp ) % p;
  }
  cout << ans << endl;
}
int main(){
  scanf( "%d" , &p );
  build();
  while( scanf( "%d" , &n ) == 1 && n ){
    solve();
  }
}
