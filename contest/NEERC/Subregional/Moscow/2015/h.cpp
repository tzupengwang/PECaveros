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
#define N 101010
#define M 514
int trans( char ctmp ){
  if( ctmp >= '0' && ctmp <= '9' ) return ctmp - '0';
  return ctmp - 'A' + 10;
}
ll n , a[ N ] , dp[ 2 ][ M ];
void build(){

}
void init(){
  n = getint();
  for( int i = 0 ; i < n ; i ++ ){
    char _c[ 9 ]; scanf( "%s" , _c );
    a[ i ] = trans( _c[ 0 ] ) * 16 + trans( _c[ 1 ] );
  }
}
void solve(){
  ll ans = a[ 0 ];
  dp[ 0 ][ 0 ] = a[ 0 ];
  dp[ 0 ][ 1 ] = 0;
  for( int i = 1 ; i < n ; i ++ ){
    int now = i&1 , pre = 1 - now;
    for( int j = 0 ; j < M ; j ++ ){ // rm j terms
      if( j ) dp[ now ][ j ] = dp[ pre ][ j - 1 ];
      dp[ now ][ j ] = max( dp[ now ][ j ] , dp[ pre ][ j ] + ( a[ i ] ^ ( i - j ) ) );
      ans = max( ans , dp[ now ][ j ] );
    }
  }
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
