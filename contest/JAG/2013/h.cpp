// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long double LD;
typedef long long ll;
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
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
typedef double type;
typedef pair<type,type> Pt;
typedef pair<Pt,Pt> Line;
typedef pair<Pt,type> Circle;
Pt operator+( const Pt& p1 , const Pt& p2 ){
  return { p1.X + p2.X , p1.Y + p2.Y };
}
Pt operator-( const Pt& p1 , const Pt& p2 ){
  return { p1.X - p2.X , p1.Y - p2.Y };
}
Pt operator*( const Pt& tp , const type& tk ){
  return { tp.X * tk , tp.Y * tk };
}
Pt operator/( const Pt& tp , const type& tk ){
  return { tp.X / tk , tp.Y / tk };
}
type operator*( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
type operator^( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
type norm2( const Pt& tp ){
  return tp * tp;
}
double norm( const Pt& tp ){
  return sqrt( norm2( tp ) );
}
Pt perp( const Pt& tp ){
  return { tp.Y , -tp.X };
}
type pi = acos( -1.0 );
void build(){

}
inline type sqr( type x ){ return x * x; }
int w , h , a , b , ab;
bool inv;
bool init(){
  inv = false;
  scanf( "%d%d%d%d%d" , &w , &h , &a , &b , &ab );
  return w != 0;
}
type ra , rb , d;
Pt oa , ob , tp;
inline type cal( type dst ){
  if( dst > ra + rb ) return 0.0;
  if( dst < fabs( ra - rb ) + eps ) return min( a , b );
  type theta = 2.0 * acos( ( sqr( dst ) + sqr( ra ) - sqr( rb ) ) / ( 2.0 * dst * ra ) );
  type thetb = 2.0 * acos( ( sqr( dst ) + sqr( rb ) - sqr( ra ) ) / ( 2.0 * dst * rb ) );
  type area = (type)a * theta / ( 2.0 * pi ) - ra * ra * sin( theta ) * 0.5;
  type brea = (type)b * thetb / ( 2.0 * pi ) - rb * rb * sin( thetb ) * 0.5;
  return area + brea;
}
inline void print_ans( type dst ){
  Pt tb = oa + tp * ( dst / d );
  if( oa.X - ra < 0.0 || oa.X + ra > w ||
      oa.Y - ra < 0.0 || oa.Y + ra > h ){
    puts( "impossible" );
    return;
  }
  if( tb.X - rb < 0.0 || tb.X + rb > w ||
      tb.Y - rb < 0.0 || tb.Y + rb > h ){
    puts( "impossible" );
    return;
  }
  if( inv ){
    printf( "%.8f %.8f %.8f " , tb.X , tb.Y , rb );
    printf( "%.8f %.8f %.8f\n" , oa.X , oa.Y , ra );
  }else{
    printf( "%.8f %.8f %.8f " , oa.X , oa.Y , ra );
    printf( "%.8f %.8f %.8f\n" , tb.X , tb.Y , rb );
  }
}
void solve(){
  if( b > a ){
    swap( a , b );
    inv = true;
  }
  ra = sqrt( (type)a / pi );
  rb = sqrt( (type)b / pi );
  oa = { ra , ra };
  ob = { w - rb , h - rb };
  if( ra > w + eps || ra > h + eps ||
      rb > w + eps || rb > h + eps ){
    puts( "impossible" );
    return;
  }
  tp = ob - oa;
  d = norm( tp );
  type bl = 0.0 , br = d , bmid;
  for( int i = 0 ; i < 100 ; i ++ ){
    bmid = ( bl + br ) * 0.5;
    type area = cal( bmid );
    if( area < ab ) br = bmid;
    else bl = bmid;
    // printf( "%.8f %.8f\n" , bmid , area );
  }
  if( !equal( ab , cal( bl ) ) ) puts( "impossible" );
  else print_ans( bl );
} 
int main(){
  build();
  while( init() ){
    solve();
  }
}
