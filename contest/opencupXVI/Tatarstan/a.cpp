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
inline Pt operator+( const Pt& p1 , const Pt& p2 ){
  return MP( p1.X + p2.X , p1.Y + p2.Y );
}
inline Pt operator-( const Pt& p1 , const Pt& p2 ){
  return MP( p1.X - p2.X , p1.Y - p2.Y );
}
inline D operator*( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
inline Pt operator*( const D& tk , const Pt& tp ){
  return MP( tk * tp.X , tk * tp.Y );
}
inline Pt operator/( const D& tk , const Pt& tp ){
  return MP( tp.X / tk , tp.Y / tk );
}
inline D operator%( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
inline D norm( const Pt& tp ){
  return sqrt( tp % tp );
}
vector<Pt> interCircle( Pt o1 , D r1 , Pt o2 , D r2 ){
  D d2 = ( o1 - o2 ) % ( o1 - o2 );
  D d = sqrt( d2 );
	if( d > r1+r2 ) return {};
  Pt u = 0.5*(o1+o2) + ((r2*r2-r1*r1)/(2*d2))*(o1-o2);
  D A = sqrt((r1+r2+d) * (r1-r2+d) * (r1+r2-d) * (-r1+r2+d));
  Pt v = A / (2*d2) * Pt(o1.Y-o2.Y, -o1.X+o2.X);
  return {u+v, u-v};
}
void scan( Pt& tp ){
  tp.X = getint();
  tp.Y = getint();
}
void print( const Pt& tp ){
  printf( "%.6f %.6f\n" , (D)tp.X , (D)tp.Y );
}
const D pi = acos( -1.0 );
Pt m[ 4 ];
void build(){

}
int deg1 , deg2;
void init(){
  for( int i = 1 ; i <= 3 ; i ++ )
    scan( m[ i ] );
  deg1 = getint();
  deg2 = getint();
}
vector< pair<Pt,D> > find_circle( Pt p1 , Pt p2 , int deg ){
  if( deg == 90 )
    return { MP( 0.5 * ( p1 + p2 ) , norm( p1 - p2 ) * 0.5 ) };
  if( deg > 90 ) deg = 180 - deg;
  Pt tmp = 0.5 * ( p1 + p2 );
  Pt dlt = p2 - p1;
  swap( dlt.X , dlt.Y );
  dlt.Y = -dlt.Y;
  D tkk = norm( tmp - p1 ) / tan( pi * (D)deg / 180.0 );
  dlt = ( tkk / norm( dlt ) ) * dlt;
  Pt o1 = tmp + dlt;
  Pt o2 = tmp - dlt;
  D r = norm( o1 - p1 );
  return { MP( o1 , r ) , MP( o2 , r ) };
}
bool flag;
void checkPt( pair<Pt,D> cir1 , pair<Pt,D> cir2 , Pt pos ){
  if( pos.X != pos.X ) return;
  if( pos.Y != pos.Y ) return;
  for( int i = 1 ; i <= 3 ; i ++ )
    if( equal( m[ i ].X , pos.X ) &&
        equal( m[ i ].Y , pos.Y ) )
      return;
  if( ( pos - cir1.FI ) % ( m[ 1 ] - cir1.FI ) > eps &&
      ( pos - cir1.FI ) % ( m[ 2 ] - cir1.FI ) > eps && 
      ( ( pos - cir1.FI ) * ( m[ 1 ] - cir1.FI ) ) *
      ( ( pos - cir1.FI ) * ( m[ 2 ] - cir1.FI ) ) < -eps ){
    if( deg1 < 90 ) return;
  }else{
    if( deg1 > 90 ) return;
  }
  if( ( pos - cir2.FI ) % ( m[ 2 ] - cir2.FI ) > eps &&
      ( pos - cir2.FI ) % ( m[ 3 ] - cir2.FI ) > eps && 
      ( ( pos - cir2.FI ) * ( m[ 2 ] - cir2.FI ) ) *
      ( ( pos - cir2.FI ) * ( m[ 3 ] - cir2.FI ) ) < -eps ){
    if( deg2 < 90 ) return;
  }else{
    if( deg2 > 90 ) return;
  }
  printf( "%.12f %.12f\n" , (D)pos.X , (D)pos.Y );
  flag = true;
}
void check( pair<Pt,D> cir1 , pair<Pt,D> cir2 ){
  vector<Pt> ppp = interCircle( cir1.FI , cir1.SE , cir2.FI , cir2.SE );
  for( size_t i = 0 ; i < ppp.size() && !flag ; i ++ )
    checkPt( cir1 , cir2 , ppp[ i ] );
  if( !flag &&
      equal( cir1.FI.X , cir2.FI.X ) &&
      equal( cir1.FI.Y , cir2.FI.Y ) &&
      equal( cir1.SE , cir2.SE ) ){
    for( int i = 0 ; i < 100 && !flag ; i ++ ){
      Pt tp = cir1.FI + cir1.SE * MP( cos( 2.0 * pi * (D)i / 100.0 ) ,
                                      sin( 2.0 * pi * (D)i / 100.0 ) );
      checkPt( cir1 , cir2 , tp );
    }
  }
}
void solve(){
  vector< pair<Pt,D> > cir1 = find_circle( m[ 1 ] , m[ 2 ] , deg1 );
  vector< pair<Pt,D> > cir2 = find_circle( m[ 2 ] , m[ 3 ] , deg2 );
  flag = false;
  for( size_t i = 0 ; i < cir1.size() && !flag ; i ++ )
    for( size_t j = 0 ; j < cir2.size() && !flag ; j ++ )
      check( cir1[ i ] , cir2[ j ] );
}
int main(){
  build();
  __ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
