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
#define N 101010
void build(){

}
char c[ N ];
ll n;
ll dpl[ N ] , dpr[ N ];
ll sl[ N ] , sr[ N ];
void init(){
  scanf( "%s" , c + 1 );
  n = strlen( c + 1 );
  for( int i = 1 ; i <= n ; i ++ )
    if( i == 1 || c[ i ] != c[ i - 1 ] ){
      sl[ i ] = 1;
      dpl[ i ] = dpl[ i - 1 ] + 1;
    }else{
      sl[ i ] = sl[ i - 1 ] + 1;
      dpl[ i ] = dpl[ i - sl[ i ] ] + sl[ i ] * sl[ i ];
    }
  dpr[ n + 1 ] = 0; sr[ n + 1 ] = 0;
  for( int i = n ; i >= 1 ; i -- )
    if( i == n || c[ i ] != c[ i + 1 ] ){
      sr[ i ] = 1;
      dpr[ i ] = dpr[ i + 1 ] + 1;
    }else{
      sr[ i ] = sr[ i + 1 ] + 1;
      dpr[ i ] = dpr[ i + sr[ i ] ] + sr[ i ] * sr[ i ];
    }
}
inline ll sqr( ll x ){ return x * x; }
void solve(){
  ll ans = dpl[ n ];
  for( int i = 1 ; i <= n ; i ++ )
    if( c[ i ] == c[ i - 1 ] && c[ i ] == c[ i + 1 ] ){
      ll tans = dpl[ i - sl[ i ] ] + dpr[ i + sr[ i ] ];
      tans += sqr( sl[ i ] - 1 ) + sqr( sr[ i ] - 1 ) + 1;
      ans = max( ans , tans );
    }else if( c[ i ] == c[ i - 1 ] ){
      ll tans = dpl[ i - sl[ i ] ] + dpr[ i + sr[ i + 1 ] + 1 ];
      tans += sqr( sl[ i ] - 1 ) + sqr( sr[ i + 1 ] + 1 );
      ans = max( ans , tans );
    }else if( c[ i ] == c[ i + 1 ] ){
      ll tans = dpl[ i - sl[ i - 1 ] - 1 ] + dpr[ i + sr[ i ] ];
      tans += sqr( sl[ i - 1 ] + 1 ) + sqr( sr[ i ] - 1 );
      ans = max( ans , tans );
    }else{
      ll tans = dpl[ i - sl[ i - 1 ] - 1 ] + dpr[ i + sr[ i + 1 ] + 1 ];
      tans += sqr( sl[ i - 1 ] + sr[ i + 1 ] + 1 );
      ans = max( ans , tans );
    }
  printf( "Case #%d: %lld\n" , ++ _cs , ans );
}
int main(){
  build();
  __ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
