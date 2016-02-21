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
#define N 20
ll ten[ N ] , nine[ N ];
void build(){
  ten[ 0 ] = 1; nine[ 0 ] = 1;
  for( int i = 1 ; i < N ; i ++ ){
    ten[ i ] = ten[ i - 1 ] * 10;
    nine[ i ] = nine[ i - 1 ] * 9;
  }
}
ll a , b;
void init(){
  a = getint();
  b = getint();
}
ll ans , ansc;
ll cal( ll x ){
  ll mul = 1 , tmp = x;
  while( tmp ){
    mul *= ( tmp % 10 );
    tmp /= 10;
  }
  if( x < a || x > b ) return -1;
  return mul;
}
void solve(){
  ans = b;
  ansc = cal( b );
  ll bt = 0 , tmp = b;
  while( tmp ){
    bt ++;
    tmp /= 10;
  }
  if( bt > 1 && cal( ten[ bt - 1 ] - 1 ) > ansc ){
    ansc = cal( ten[ bt - 1 ] - 1 );
    ans = ten[ bt - 1 ] - 1;
  }
  for( ll i = bt - 1 ; i > 0 ; i -- ){
    ll now = ( b % ( ten[ i + 1 ] ) ) / ten[ i ];
    if( now > 1 ){
      ll tmp2 = ( b / ten[ i ] ) * ten[ i ];
      tmp2 --;
      if( cal( tmp2 ) > ansc ){
        ansc = cal( tmp2 );
        ans = tmp2;
      }
    }
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
