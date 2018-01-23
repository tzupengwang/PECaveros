// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long double LD;
typedef long long ll;
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<ll,ll> PLL;
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
int __ = 1 , cs;
/*********default*********/
#define N 303030
ll fac[ N ] , ifac[ N ];
void build(){
  fac[ 0 ] = ifac[ 0 ] = 1;
  for( ll i = 1 ; i < N ; i ++ ){
    fac[ i ] = mul( fac[ i - 1 ] , i );
    ifac[ i ] = mypow( fac[ i ] , mod7 - 2 , mod7 );
  }
}
inline ll C( ll _a , ll _b ){
  return mul( fac[ _a ] , mul( ifac[ _b ] , ifac[ _a - _b ] ) );
}
ll n , k , a[ N ];
void init(){
  k = getint(); n = 1 << k;
  for( int i = 1 ; i <= n ; i ++ )
    a[ i ] = getint();
}
ll cal( int dep ){
  ll xn = ( 1 << dep );
  ll tk = xn - 1;
  ll ssum = 0 , tans = 0;
  for( int i = n - tk ; i >= 1 ; i -- ){
    if( n - i >= xn + xn - 1 ){
      ll dlt = mul( mul( a[ i ] , C( n - i - xn , tk ) ) , ssum );
      tans = add( tans , dlt );
    }
    ssum = add( ssum , mul( C( n - i , tk ) , a[ i ] ) );
  }
  return mul( mul( mul( tans , 2ll ) , mypow( mul( C( n , xn ) , C( n - xn , xn ) ) , mod7 - 2 , mod7 ) ) ,
              1ll << ( k - dep - 1 ) );
}
void solve(){
  ll ans = 0;
  for( int i = 0 ; i < k ; i ++ )
    ans = add( ans , cal( i ) );
  printf( "%lld\n" , ans );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
