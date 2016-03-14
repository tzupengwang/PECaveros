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
inline LD operator*( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
inline Pt operator*( const LD& tk , const Pt& tp ){
  return MP( tk * tp.X , tk * tp.Y );
}
inline Pt operator/( const LD& tk , const Pt& tp ){
  return MP( tp.X / tk , tp.Y / tk );
}
inline LD operator%( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
inline LD norm( const Pt& tp ){
  return sqrt( tp % tp );
}
vector<Pt> interCircle( Pt o1 , LD r1 , Pt o2 , LD r2 ){
  LD d2 = ( o1 - o2 ) % ( o1 - o2 );
  LD d = sqrt( d2 );
	if( d > r1+r2 ) return {};
  Pt u = 0.5*(o1+o2) + ((r2*r2-r1*r1)/(2*d2))*(o1-o2);
  LD A = sqrt((r1+r2+d) * (r1-r2+d) * (r1+r2-d) * (-r1+r2+d));
  Pt v = A / (2*d2) * Pt(o1.Y-o2.Y, -o1.X+o2.X);
  return {u+v, u-v};
}
void scan( Pt& tp ){
  tp.X = getint();
  tp.Y = getint();
}
void print( const Pt& tp ){
  printf( "%.12f %.12f\n" , (D)tp.X , (D)tp.Y );
}
const LD pi = acosl( -1.0 );
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
vector< pair<Pt,LD> > find_circle( Pt p1 , Pt p2 , int deg ){
  if( deg == 90 )
    return { MP( 0.5 * ( p1 + p2 ) , norm( p1 - p2 ) * 0.5 ) };
  if( deg > 90 ) deg = 180 - deg;
  Pt tmp = 0.5 * ( p1 + p2 );
  Pt dlt = p2 - p1;
  swap( dlt.X , dlt.Y );
  dlt.Y = -dlt.Y;
  LD tkk = norm( tmp - p1 ) / tanl( pi * (LD)deg / 180.0 );
  dlt = ( tkk / norm( dlt ) ) * dlt;
  Pt o1 = tmp + dlt;
  Pt o2 = tmp - dlt;
  LD r = norm( o1 - p1 );
  return { MP( o1 , r ) , MP( o2 , r ) };
}
bool flag;
bool inbad( const Pt& o , const Pt& p1 , const Pt& p2 , const Pt& pos ){
  Pt tp1 = p1 - o;
  Pt tp2 = p2 - o;
  Pt tpos = pos - o;
  LD tdeg1 = atan2l( tp1.Y , tp1.X );
  LD tdeg2 = atan2l( tp2.Y , tp2.X );
  LD tdegp = atan2l( tpos.Y , tpos.X );
  while( fabs( tdeg1 - tdeg2 ) > pi + eps ){
    if( tdeg1 < tdeg2 ) tdeg1 += 2.0 * pi;
    else tdeg2 += 2.0 * pi;
  }
  if( tdeg1 > tdeg2 ) swap( tdeg1 , tdeg2 );
  while( tdegp > tdeg1 - eps ) tdegp -= 2.0 * pi;
  while( tdegp < tdeg1 - eps ) tdegp += 2.0 * pi;
  return tdeg1 + eps < tdegp && tdegp < tdeg2 - eps;
}
void checkPt( pair<Pt,LD> cir1 , pair<Pt,LD> cir2 , Pt pos ){
  if( pos.X != pos.X ) return;
  if( pos.Y != pos.Y ) return;
  for( int i = 1 ; i <= 3 ; i ++ )
    if( equal( m[ i ].X , pos.X ) &&
        equal( m[ i ].Y , pos.Y ) )
      return;
  if( inbad( cir1.FI , m[ 1 ] , m[ 2 ] , pos ) ){
    if( deg1 < 90 ) return;
  }else{
    if( deg1 > 90 ) return;
  }
  if( inbad( cir2.FI , m[ 2 ] , m[ 3 ] , pos ) ){
    if( deg2 < 90 ) return;
  }else{
    if( deg2 > 90 ) return;
  }
  print( pos );
  flag = true;
}
void check( pair<Pt,LD> cir1 , pair<Pt,LD> cir2 ){
  vector<Pt> ppp = interCircle( cir1.FI , cir1.SE , cir2.FI , cir2.SE );
  for( size_t i = 0 ; i < ppp.size() && !flag ; i ++ )
    checkPt( cir1 , cir2 , ppp[ i ] );
  if( !flag &&
      equal( cir1.FI.X , cir2.FI.X ) &&
      equal( cir1.FI.Y , cir2.FI.Y ) &&
      equal( cir1.SE , cir2.SE ) ){
    for( int i = 0 ; i < 100 && !flag ; i ++ ){
      Pt tp = cir1.FI + cir1.SE * MP( cosl( 2.0 * pi * (LD)i / 100.0 ) ,
                                      sinl( 2.0 * pi * (LD)i / 100.0 ) );
      checkPt( cir1 , cir2 , tp );
    }
  }
}
void solve(){
  vector< pair<Pt,LD> > cir1 = find_circle( m[ 1 ] , m[ 2 ] , deg1 );
  vector< pair<Pt,LD> > cir2 = find_circle( m[ 2 ] , m[ 3 ] , deg2 );
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
