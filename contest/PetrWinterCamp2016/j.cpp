// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long double LD;
typedef long long ll;
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef pair<LD,LD> Pt;
#define mod9 1000000009ll
#define mod7 1000000007ll
#define INF  1023456789ll
#define INF16 10000000000000000ll
#define FI first
#define SE second
#define X FI
#define Y SE
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define eps 1e-9
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(), (x).end()
#ifndef ONLINE_JUDGE
#define debug(...) printf(__VA_ARGS__)
#else 
#define debug(...)
#endif
inline ll getint(){
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
inline ll add( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x + _y;
  if( _ >= _mod ) _ -= _mod;
  return _;
}
inline ll sub( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x - _y;
  if( _ < 0 ) _ += _mod;
  return _;
}
inline ll mul( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x * _y;
  if( _ >= _mod ) _ %= _mod;
  return _;
}
inline bool equal( D _x ,  D _y ){
  return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , _cs;
/*********default*********/
#define N 2222
ll n , p[ N ] , lb[ N ] , BIT[ N ][ N ] , pw[ N ] , C[ N ][ N ];
inline void modify( ll len , ll x , ll dlt ){
  for( ll i = x ; i <= n ; i += lb[ i ] )
    BIT[ len ][ i ] = add( BIT[ len ][ i ] , dlt );
}
inline ll query( ll len , ll x ){
  ll sum = 0;
  for( ll i = x ; i ; i -= lb[ i ] )
    sum = add( sum , BIT[ len ][ i ] );
  return sum;
}
void build(){
  for( ll i = 1 ; i < N ; i ++ )
    lb[ i ] = i & (-i);
}
void init(){
  n = getint();
  for( ll i = 1 ; i <= n ; i ++ )
    p[ i ] = getint();
  for( ll i = 0 ; i <= n ; i ++ )
    C[ i ][ i ] = C[ i ][ 0 ] = 1;
  for( ll i = 2 ; i <= n ; i ++ )
    for( ll j = 1 ; j < i ; j ++ )
      C[ i ][ j ] = add( C[ i - 1 ][ j ] , C[ i - 1 ][ j - 1 ] );
  for( ll i = 1 ; i <= n ; i ++ ){
    pw[ i ] = mypow( i , n , mod7 );
    for( ll j = 1 ; j < i ; j ++ )
      pw[ i ] = sub( pw[ i ] , mul( C[ i ][ j ] , pw[ j ] ) );
    // printf( "%lld %lld\n" , i , pw[ i ] );
  }
}
void solve(){
  modify( 0 , 1 , 1 );
  ll ans = 0;
  for( ll i = 1 ; i <= n ; i ++ )
    for( ll j = i ; j >= 1 ; j -- ){
      ll c = query( j - 1 , p[ i ] );
      // printf( "%lld %lld : %lld\n" , i , j , c );
      ans = add( ans , mul( c , pw[ j ] ) );
      modify( j , p[ i ] , c );
    }
  cout << ans << endl;
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
