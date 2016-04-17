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
class frac{
public:
  ll u , d;
  frac(){}
  frac( ll x ){
    u = x; d = 1;
  }
  frac( ll _u , ll _d ) : u( _u ) , d ( _d ) {
    reduce();
  }
  void reduce(){
    ll tmp = __gcd( u , d );
    u /= tmp; d /= tmp;
    if( d < 0 ){
      u = -u;
      d = -d;
    }
  }
  frac operator*( const frac& f ){
    frac tmp( u * f.u , d * f.d );
    tmp.reduce();
    return tmp;
  }
  frac operator/( const frac& f ){
    frac tmp( u * f.d , d * f.u );
    tmp.reduce();
    return tmp;
  }
  frac operator+( const frac& f ){
    frac tmp( u * f.d + d * f.u , d * f.d );
    tmp.reduce();
    return tmp;
  }
  frac operator-( const frac& f ){
    frac tmp( u * f.d - d * f.u , d * f.d );
    tmp.reduce();
    return tmp;
  }
  bool operator>( const frac& f ){
    return u * f.d > d * f.u;
  }
  void print(){
    printf( "%lld/%lld\n" , u , d );
  }
};
ll lm , lg , x[ 3 ] , y[ 3 ];
void init(){
  lm = getint();
  lg = getint();
  for( int i = 0 ; i < 3 ; i ++ ){
    x[ i ] = getint();
    y[ i ] = getint();
  }
}
inline LD sqr( LD xx ){ return xx * xx; }
bool okay( ll i1 , ll i2 ){
  ll i3 = 3 - i1 - i2;
  if( x[ i1 ] == x[ i2 ] ){
    if( x[ i1 ] == x[ i3 ] ){
      ll maxd = max( abs( y[ i1 ] - y[ i2 ] ) ,
                     max( abs( y[ i1 ] - y[ i3 ] ) ,
                          abs( y[ i2 ] - y[ i3 ] ) ) );
      if( maxd <= lm || maxd <= lg * 2 )
         return true;
    }
    ll d2 = abs( x[ i1 ] - x[ i3 ] );
    ll d3 = abs( y[ i1 ] - y[ i3 ] );
    ll d4 = abs( y[ i2 ] - y[ i3 ] );
    bool can1 = true , can2 = true;
    if( d2 > lm ) can1 = false;
    if( d3 > lg ) can1 = false;
    if( d4 > lg ) can1 = false;
    if( d2 > lg ) can2 = false;
    if( d3 > lm ) can2 = false;
    if( d4 > lm ) can2 = false;
    if( y[ i3 ] < max( y[ i1 ] , y[ i2 ] ) &&
        y[ i3 ] > min( y[ i1 ] , y[ i2 ] ) )
      can2 = false;
    return can1 || can2;
  }
  if( y[ i1 ] == y[ i2 ] ){
    if( y[ i1 ] == y[ i3 ] ){
      ll maxd = max( abs( x[ i1 ] - x[ i2 ] ) ,
                     max( abs( x[ i1 ] - x[ i3 ] ) ,
                          abs( x[ i2 ] - x[ i3 ] ) ) );
      if( maxd <= lm || maxd <= lg * 2 )
         return true;
    }
    ll d2 = abs( y[ i1 ] - y[ i3 ] );
    ll d3 = abs( x[ i1 ] - x[ i3 ] );
    ll d4 = abs( x[ i2 ] - x[ i3 ] );
    bool can1 = true , can2 = true;
    if( d2 > lm ) can1 = false;
    if( d3 > lg ) can1 = false;
    if( d4 > lg ) can1 = false;
    if( d2 > lg ) can2 = false;
    if( d3 > lm ) can2 = false;
    if( d4 > lm ) can2 = false;
    if( x[ i3 ] < max( x[ i1 ] , x[ i2 ] ) &&
        x[ i3 ] > min( x[ i1 ] , x[ i2 ] ) )
      can2 = false;
    return can1 || can2;
  }
  LD m1 = (LD)( y[ i1 ] - y[ i2 ] ) / (LD)( x[ i1 ] - x[ i2 ] );
  LD c1 = y[ i1 ] - m1 * x[ i1 ];
  LD ccc = y[ i3 ] - m1 * x[ i3 ];
  LD m2 = (LD)( x[ i1 ] - x[ i2 ] ) / (LD)( y[ i2 ] - y[ i1 ] );
  LD c2 = y[ i3 ] - m2 * x[ i3 ];
  if( equal( c1 , ccc ) ){
    LD dd1 = sqr( x[ i1 ] - x[ i2 ] ) + sqr( y[ i1 ] - y[ i2 ] );
    LD dd2 = sqr( x[ i1 ] - x[ i3 ] ) + sqr( y[ i1 ] - y[ i3 ] );
    LD dd3 = sqr( x[ i3 ] - x[ i2 ] ) + sqr( y[ i3 ] - y[ i2 ] );
    if( dd2 > dd1 ) dd1 = dd2;
    if( dd3 > dd1 ) dd1 = dd3;
    if( dd1 < (LD)lm * lm + eps ) return true;
    if( dd1 < (LD)lg * lg * 4.0 + eps ) return true;
  }
  LD rx = ( c2 - c1 ) / ( m1 - m2 );
  LD ry = m1 * rx + c1;
  LD d3 = sqr( rx - x[ i1 ] ) + sqr( ry - y[ i1 ] );
  LD d4 = sqr( rx - x[ i2 ] ) + sqr( ry - y[ i2 ] );
  LD d2 = sqr( rx - x[ i3 ] ) + sqr( ry - y[ i3 ] );
  LD dd = sqr( x[ i1 ] - x[ i2 ] ) + sqr( y[ i1 ] - y[ i2 ] );
  bool can1 = true , can2 = true;
  if( d2 > (LD)lm * (LD)lm + eps ) can1 = false;
  if( d3 > (LD)lg * (LD)lg + eps ) can1 = false;
  if( d4 > (LD)lg * (LD)lg + eps ) can1 = false;
  if( d2 > (LD)lg * (LD)lg + eps ) can2 = false;
  if( d3 > (LD)lm * (LD)lm + eps ) can2 = false;
  if( d4 > (LD)lm * (LD)lm + eps ) can2 = false;
  if( d3 < dd - eps && d4 < dd - eps ) can2 = false;
  return can1 || can2;
}
void solve(){
  if( okay( 0 , 1 ) ||
      okay( 0 , 2 ) ||
      okay( 1 , 2 ) ) puts( "YES" );
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
