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
typedef pair<Pt,LD> Cir;
#define O FI
#define R SE
const LD PI = acosl( -1.0 );
inline Pt operator+( const Pt& p1 , const Pt& p2 ){
  return MP( p1.X + p2.X , p1.Y + p2.Y );
}
inline Pt operator-( const Pt& p1 , const Pt& p2 ){
  return MP( p1.X - p2.X , p1.Y - p2.Y );
}
inline Pt operator*( const Pt& tp , const LD& tk ){
  return MP( tp.X * tk , tp.Y * tk );
}
inline Pt operator/( const Pt& tp , const LD& tk ){
  return MP( tp.X / tk , tp.Y / tk );
}
inline LD operator%( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
vector<Pt> interCircle( Pt o1 , LD r1 , Pt o2 , LD r2 ){
  LD d2 = ( o1 - o2 ) % ( o1 - o2 ); // dot
  LD d = sqrt( d2 );
	if( d > r1+r2 ) return {};
  Pt u = (o1+o2) * 0.5 + (o1-o2) * ((r2*r2-r1*r1)/(2*d2));
  LD A = sqrt((r1+r2+d) * (r1-r2+d) * (r1+r2-d) * (-r1+r2+d));
  Pt v = Pt( o1.Y-o2.Y , -o1.X + o2.X ) * A / (2*d2);
  return {u+v, u-v};
}
inline LD norm( const Pt& tp ){
  return sqrt( tp % tp );
}
inline void scan( Cir& cir ){
  cir.O.X = getint();
  cir.O.Y = getint();
  cir.R = getint();
}
inline Pt cir_deg( const Cir& cir , const LD& tdeg ){
  return cir.O + MP( cosl( tdeg ) , sinl( tdeg ) ) * cir.R;
}
void build(){

}
Cir c[ 2 ];
int deg[ 2 ][ 2 ];
void init(){
  for( int i = 0 ; i < 2 ; i ++ ){
    scan( c[ i ] );
    for( int j = 0 ; j < 2 ; j ++ )
      deg[ i ][ j ] = getint();
    if( deg[ i ][ 1 ] < deg[ i ][ 0 ] )
      deg[ i ][ 1 ] += 360;
  }
}
vector<Pt> pos[ 2 ];
bool okay( int idx , LD tdeg ){
  LD ldeg = (LD)deg[ idx ][ 0 ] / 180.0 * PI;
  LD rdeg = (LD)deg[ idx ][ 1 ] / 180.0 * PI;
  for( int dlt = -1 ; dlt <= 1 ; dlt ++ )
    if( ldeg + (LD)dlt * 2.0 * PI - eps < tdeg &&
        rdeg + (LD)dlt * 2.0 * PI + eps > tdeg )
      return true;
  return false;
}
bool good( const Pt& tp ){
  bool flag = true;
  for( int i = 0 ; i < 2 ; i ++ ){
    Pt tmp = tp - c[ i ].O;
    LD tdeg = atan2( tmp.Y , tmp.X );
    if( !okay( i , tdeg ) )
      flag = false;
    else pos[ i ].PB( tp );
  }
  return flag;
}
void solve(){
  Pt dir = c[ 1 ].O - c[ 0 ].O;
  LD dir_deg = atan2( dir.Y , dir.X );
  for( int i = 0 ; i < 2 ; i ++ ){
    if( okay( i , dir_deg ) )
      pos[ i ].PB( cir_deg( c[ i ] , dir_deg ) );
    if( okay( i , dir_deg + PI ) )
      pos[ i ].PB( cir_deg( c[ i ] , dir_deg + PI ) );
    for( int j = deg[ i ][ 0 ] ; j <= deg[ i ][ 1 ] ; j ++ )
      pos[ i ].PB( cir_deg( c[ i ] , (LD)j / 180.0 * PI ) );
  }
  LD ans = 1e20;
  vector<Pt> vv = interCircle( c[ 0 ].O , c[ 0 ].R , c[ 1 ].O , c[ 1 ].R );
  for( size_t i = 0 ; i < vv.size() ; i ++ ){
    if( good( vv[ i ] ) )
      ans = 0.0;
  }
  for( size_t i = 0 ; i < pos[ 0 ].size() ; i ++ )
    for( size_t j = 0 ; j < pos[ 1 ].size() ; j ++ )
      ans = min( ans , norm( pos[ 0 ][ i ] - pos[ 1 ][ j ] ) );
  printf( "%.12f\n" , (D)ans );
}
#define K 1000
LD cal( const Pt& tp ){
  LD l = deg[ 1 ][ 0 ] , r = deg[ 1 ][ 1 ] , m1 , m2 , ans = 1e20;
  for( int i = 0 ; i < K ; i ++ ){
    m1 = l + ( r - l ) / 3.0;
    m2 = r - ( r - l ) / 3.0;
    Pt p1 = cir_deg( c[ 1 ] , (LD)m1 / 180.0 * PI );
    Pt p2 = cir_deg( c[ 1 ] , (LD)m2 / 180.0 * PI );
    LD d1 = norm( p1 - tp );
    LD d2 = norm( p2 - tp );
    if( d1 < d2 ) r = m2;
    else l = m1;
    ans = min( ans , d1 );
    ans = min( ans , d2 );
  }
  return ans;
}
void solve2(){
  LD l = deg[ 0 ][ 0 ] , r = deg[ 0 ][ 1 ] , m1 , m2 , ans = 1e20;
  for( int i = 0 ; i < K ; i ++ ){
    m1 = l + ( r - l ) / 3.0;
    m2 = r - ( r - l ) / 3.0;
    LD d1 = cal( cir_deg( c[ 0 ] , (LD)m1 / 180.0 * PI ) );
    LD d2 = cal( cir_deg( c[ 0 ] , (LD)m2 / 180.0 * PI ) );
    if( d1 < d2 ) r = m2;
    else l = m1;
    // printf( "%.6f : %.6f %.6f : %.6f\n" , (D)m1 , (D)d1 , (D)m2 , (D)d2 );
    ans = min( ans , d1 );
    ans = min( ans , d2 );
  }
  printf( "%.12f\n" , (D)ans );
}
int main(){
  freopen( "circular.in" , "r" , stdin );
  freopen( "circular.out" , "w" , stdout );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve2();
  }
}
