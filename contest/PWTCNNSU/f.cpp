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
typedef tuple<int,int,int> tiii;
typedef tuple<LL,LL,LL> tlll;
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
ll mypow( ll _a , ll _x , ll _mod ){
  if( _x == 0 ) return 1ll;
  ll _tmp = mypow( _a , _x / 2 , _mod );
  _tmp = mul( _tmp , _tmp , _mod );
  if( _x & 1 ) _tmp = mul( _tmp , _a , _mod );
  return _tmp;
}
ll mymul( ll _a , ll _x , ll _mod ){
  if( _x == 0 ) return 0ll;
  ll _tmp = mymul( _a , _x / 2 , _mod );
  _tmp = add( _tmp , _tmp , _mod );
  if( _x & 1 ) _tmp = add( _tmp , _a , _mod );
  return _tmp;
}
inline bool equal( D _x ,  D _y ){
  return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , _cs;
/*********default*********/
void build(){

}
LD lm , lg , x[ 3 ] , y[ 3 ];
void init(){
  lm = getint();
  lg = getint();
  for( int i = 0 ; i < 3 ; i ++ ){
    x[ i ] = getint();
    y[ i ] = getint();
  }
}
inline LD sqr( LD _ ){ return _ * _; }
inline bool okay( int i1 , int i2 ){
  int i3 = 3 - i1 - i2;
  if( equal( ( x[ i1 ] - x[ i2 ] ) * ( y[ i1 ] - y[ i3 ] ) -
             ( y[ i1 ] - y[ i2 ] ) * ( x[ i1 ] - x[ i3 ] ) , 0.0 ) ){
      
  }
  LD a1 = y[ i1 ] - y[ i2 ];
  LD b1 = x[ i2 ] - x[ i1 ];
  LD c1 = a1 * x[ i1 ] + b1 * y[ i1 ];
  LD t = ( c1 - a1 * x[ i3 ] - b1 * y[ i3 ] ) / ( a1 * a1 + b1 * b1 );
  LD rx = x[ i3 ] + t * a1;
  LD ry = y[ i3 ] + t * b1;
  LD d1 = sqr( rx - x[ i1 ] ) + sqr( ry - y[ i1 ] );
  LD d2 = sqr( rx - x[ i2 ] ) + sqr( ry - y[ i2 ] );
  LD d3 = sqr( rx - x[ i3 ] ) + sqr( ry - y[ i3 ] );
  LD dd = sqr( x[ i1 ] - x[ i2 ] ) + sqr( y[ i1 ] - y[ i2 ] );
  if( d1 < lg * lg + eps &&
      d2 < lg * lg + eps &&
      d3 < lm * lm + eps ) return true;
  if( d1 < dd - eps && d2 < dd - eps ) return false;
  if( d1 < lm * lm + eps &&
      d2 < lm * lm + eps &&
      d3 < lg * lg + eps ) return true;
  return false;
}
void solve(){
  if( okay( 0 , 1 ) ||
      okay( 0 , 2 ) ||
      okay( 1 , 2 ) )
    puts( "YES" );
  else puts( "NO" );
}
int main(){
  build();
  __ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
