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
#define N 222
#define X 100
ll n , k , nn;
void build(){

}
void init(){
  n = getint();
  k = getint();
  nn = n % 100;
}
int tag[ N ];
ll pdp[ N ];
void solve(){
  for( int i = 0 ; i < X ; i ++ ) tag[ i ] = 0;
  ll now = nn , dlt = -1 , tsum = 0;
  for( int i = 0 ; i < k ; i ++ ){
    if( tag[ now ] ){
      pdp[ i ] = now;
      pdp[ i ] += pdp[ i - 1 ];
      tsum = pdp[ i ];
      dlt = i + 1 - tag[ now ];
      k -= ( i + 1 );
      ll bonus = ( k / dlt ) * ( pdp[ i ] - pdp[ tag[ now ] - 1 ] );
      bonus += ( pdp[ tag[ now ] - 1 + k % dlt ] - pdp[ tag[ now ] - 1 ] );
      printf( "%lld\n" , n + tsum + bonus );
      return;
    }else{
      pdp[ i ] = now;
      tag[ now ] = i + 1;
      if( i ) pdp[ i ] += pdp[ i - 1 ];
      tsum = pdp[ i ];
      now = ( 2 * now ) % 100;
    }
  }
  printf( "%lld\n" , n + tsum );
}
int main(){
  build();
  __ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
