// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long long ll;
typedef pair<int,int> PII;
#define mod9 1000000009ll
#define mod7 1000000007ll
#define INF  1023456789ll
#define INF16 10000000000000000ll
#define FI first
#define SE second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define eps 1e-9
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(), (x).end()
ll getint(){
    ll _x=0,_tmp=1; char _tc=getchar();    
    while( (_tc<'0'||_tc>'9')&&_tc!='-' ) _tc=getchar();
    if( _tc == '-' ) _tc=getchar() , _tmp = -1;
    while(_tc>='0'&&_tc<='9') _x*=10,_x+=(_tc-'0'),_tc=getchar();
    return _x*_tmp;
}
ll mypow( ll _a , ll _x , ll _mod ){
    if( _x == 0 ) return 1ll;
    ll _tmp = mypow( _a , _x / 2 , _mod );
    _tmp = ( _tmp * _tmp ) % _mod;
    if( _x & 1 ) _tmp = ( _tmp * _a ) % _mod;
    return _tmp;
}
bool equal( D _x ,  D _y ){
    return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , cs;
/*********default*********/
#define N 510
ll n , k , p;
ll c[ N ][ N ] , lvl[ N ];
void build(){
  lvl[ 0 ] = 1;
  for( ll i = 1 ; i < N ; i ++ )
    lvl[ i ] = ( lvl[ i - 1 ] * i ) % mod7;
  c[ 0 ][ 0 ] = 1;
  for( ll i = 1 ; i < N ; i ++ )
    c[ i ][ 0 ] = c[ i ][ i ] = 1;
  for( ll i = 2 ; i < N ; i ++ )
    for( ll j = 1 ; j < i ; j ++ )
      c[ i ][ j ] = ( c[ i - 1 ][ j - 1 ] + c[ i - 1 ][ j ] ) % mod7;
}
void init(){
  n = getint();
  k = getint();
  p = getint();
}
void solve(){
  if( n == p ){
    ll ans = ( c[ n - 1 ][ n - k ] * lvl[ k - 1 ] ) % mod7;
    printf( "Case #%d: %lld\n" , ++ cs , ans );
    return;
  }
  ll ans = 0;
  for( ll i = k + 1 ; i <= n ; i ++ ){
    ll tans = c[ n - 1 ][ i - k ];
    if( i != n ) tans -= c[ p - 1 ][ i - k ];
    tans = ( tans + mod7 ) % mod7;
    ll tmp = lvl[ n - i + k - 1 ];
    tans = ( tans * tmp ) % mod7;
    ans = ( ans + tans ) % mod7;
  }
  printf( "Case #%d: %lld\n" , ++ cs , ans );
}
int main(){
    build();
    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
