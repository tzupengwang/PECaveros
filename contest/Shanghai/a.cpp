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
#define eps 1e-7
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
inline void scan( Pt& tp ){
  tp.X = getint();
  tp.Y = getint();
}
inline Pt operator+( const Pt& p1 , const Pt& p2 ){
  return MP( p1.X + p2.X , p1.Y + p2.Y );
}
inline Pt operator-( const Pt& p1 , const Pt& p2 ){
  return MP( p1.X - p2.X , p1.Y - p2.Y );
}
inline Pt operator*( const Pt& p1 , const LD& tk ){
  return MP( p1.X * tk , p1.Y * tk );
}
inline LD operator%( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
inline LD norm( const Pt &tp ){
  return sqrt( tp % tp );
}
inline LD sqr( const LD& tx ){ return tx * tx; }
void build(){

}
Pt o , a , v , b;
LD r;
void init(){
  scan( o );
  r = getint();
  scan( a );
  scan( v );
  scan( b );
}
LD distance( const Pt& p1 , const Pt& p2 , const Pt& p3 ){
  Pt dv = p2 - p1;
  LD tk = ( dv % p3 - dv % p1 ) / ( dv % dv );
  if( tk != tk ) return 0.0;
  Pt tmp = p1 + dv * tk;
  return norm( tmp - p3 );
}
Pt nearest( const Pt& p1 , const Pt& p2 , const Pt& p3 ){
  Pt dv = p2 - p1;
  LD tk = ( dv % p3 - dv % p1 ) / ( dv % dv );
  if( tk != tk ) return MP( 1.0 / 0.0 , 1.0 / 0.0 );
  Pt tmp = p1 + dv * tk;
  return tmp;
}
bool onto( const Pt& p1 , const Pt& p2 , const Pt& p3 , const LD& dx = -1 ){
  Pt dv = p3 - p1;
  if( dv % p2 < 0 ) return false;
  LD dltx = dv.X / p2.X;
  LD dlty = dv.Y / p2.Y;
  if( dltx != dltx ){
    if( equal( p1.X , p3.X ) ){
      if( dx > 0 ) return dlty < dx + eps;
      return true;
    }
    return false;
  }
  if( dlty != dlty ){
    if( equal( p1.Y , p3.Y ) ){
      if( dx > 0 ) return dltx < dx + eps;
      return true;
    }
    return false;
  }
  if( dx > 0 ) return equal( dltx , dlty ) && dltx < dx + eps;
  return equal( dltx , dlty );
}
Pt infl( const Pt& aa , const Pt& o1 , const Pt& o2 ){
  Pt tp = nearest( o1 , o2 , aa );
  Pt tmp = ( tp - aa ) * 2.0 + aa;
  return tmp;
}
void cal(){
  if( equal( distance( a , a + v , b ) , 0.0 ) &&
      onto( a , v , b ) ){
    printf( "Case #%d: Yes\n" , ++ _cs );
  }else
    printf( "Case #%d: No\n" , ++ _cs );
}
void solve(){
  if( distance( a , a + v , o ) > r - eps ){
    cal();
    return;
  }
  LD ak = v % v;
  LD bk = 2.0 * ( ( a - o ) % v );
  LD ck = sqr( a.X - o.X ) + sqr( a.Y - o.Y ) - sqr( r );
  LD xa = ( -bk + sqrt( sqr( bk ) - 4.0 * ak * ck ) ) / ( 2.0 * ak );
  LD xb = ( -bk - sqrt( sqr( bk ) - 4.0 * ak * ck ) ) / ( 2.0 * ak );
  LD xx = -1;
  if( xa < eps && xb < eps ){
    cal();
    return;
  }else if( xa != xa ) xx = xb;
  else if( xb != xb ) xx = xa;
  else xx = min( xa , xb );
  if( xx != xx ){
    cal();
    return;
  }
  if( onto( a , v , b , xx ) ){
    printf( "Case #%d: Yes\n" , ++ _cs );
    return;
  }else if( onto( a , v , b ) ){
    printf( "Case #%d: No\n" , ++ _cs );
    return;
  }
  Pt op = a + v * xx;
  Pt ap = infl( a , op , o );
  v = ap - op;
  a = op;
  cal();
}
int main(){
  build();
  __ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
