// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long long ll;
typedef pair<int,int> PII;
#define mod9 1000000009ll
#define mod7 1000000007ll
#define INF  1023456789ll
#define INF16 10000000000000000ll
#define FI first
#define SE second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define eps 1e-9
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(), (x).end()
ll getint(){
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
bool equal( D _x ,  D _y ){
    return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , cs;
/*********default*********/
#define N 2010
typedef pair<D,D> PT;
#define X first
#define Y second
const D pi = acos( -1.0 );
D deg( const PT& tp ){
  return atan2( tp.Y , tp.X );
}
PT operator+( const PT& p1 , const PT& p2 ){
  return MP( p1.X + p2.X , p1.Y + p2.Y );
}
PT operator-( const PT& p1 , const PT& p2 ){
  return MP( p1.X - p2.X , p1.Y - p2.Y );
}
PT operator*( const PT& p1 , const D& tk ){
  return MP( p1.X * tk , p1.Y * tk );
}
PT operator/( const PT& p1 , const D& tk ){
  return MP( p1.X / tk , p1.Y / tk );
}
D operator%( const PT& p1 , const PT& p2 ){
  return p1.X * p2.X +
         p1.Y * p2.Y;
}
D operator^( const PT& p1 , const PT& p2 ){
  return p1.X * p2.Y -
         p1.Y * p2.X;
}
bool operator==( const PT& p1 , const PT& p2 ){
  return equal( p1.X , p2.X ) &&
         equal( p1.Y , p2.Y );
}
D norm( const PT& tp ){
  return sqrt( tp % tp );
}
D dist( const PT& p1 , const PT& p2 ){
  return norm( p1 - p2 );
}
PT vec( const D& tdeg ){
  return MP( cosl( tdeg ) , sinl( tdeg ) );
}
PT perp( const PT& tp ){
  return MP( tp.Y , -tp.X );
}
// -pi ~ pi
pair<bool,PT> interPnt( PT p1 , PT p2, PT q1, PT q2){
	D f1 = ( p2 - p1 ) ^ ( q1 - p1 );
	D f2 = ( p2 - p1 ) ^ ( p1 - q2 );
	D f = ( f1 + f2 );
	if(fabs(f) < eps)
    return MP( false , MP( -1 , -1 ) );
	return MP( true , q1 * ( f2 / f ) +
                    q2 * ( f1 / f ) );
}
bool onseg( PT p1 , PT p2 , PT qp ){
  if( !equal( ( p2 - p1 ) ^ ( qp - p1 ) , 0.0 ) ) return false;
  return ( p2 - p1 ) % ( qp - p1 ) > -eps &&
         norm( p2 - p1 ) + eps >
         norm( qp - p1 );
}
int n , _;
D theta , r , v , d;
PT pos;
PT a[ N ];
bool good[ N ];
void build(){
  
}
bool btw( D ldeg , D qdeg , D rdeg ){
  return ( qdeg > ldeg - eps &&
           qdeg < rdeg + eps ) ||
         ( qdeg > ldeg + 2.0 * pi - eps &&
           qdeg < rdeg + 2.0 * pi + eps ) ||
         ( qdeg > ldeg - 2.0 * pi - eps &&
           qdeg < rdeg - 2.0 * pi + eps );
}
bool okay( D deg1 , D deg2 ){
  return btw( deg2 - theta , deg1 ,
              deg2 + theta );
}
bool in_sector( PT qp , D with_r = 0.0 ){
  if( dist( qp , pos ) < eps ) return true;
  if( dist( qp , pos ) < r + eps ){
    D ndeg = deg( qp - pos );
    if( btw( v - with_r - theta , ndeg ,
             v + theta ) )
      return true;
  }
  return false;
}
void test_sector( D with_r = 0.0 ){
  for( int i = 0 ; i < n ; i ++ )
    if( in_sector( a[ i ] , with_r ) )
      good[ i ] = false;
}
void test_rec( D len ){
  if( len < eps ) return;
  PT tri[ 3 ];
  tri[ 0 ] = pos;
  tri[ 1 ] = pos + vec( v + theta ) * r;
  tri[ 2 ] = pos + vec( v - theta ) * r;
  for( int i = 0 ; i < n ; i ++ ) if( good[ i ] ){
    PT nxta = a[ i ] - vec( d ) * len;
    for( int j = 1 ; j <= 2 ; j ++ ){
      pair<bool,PT> tq = interPnt( a[ i ] , nxta ,
                                   tri[ 0 ] , tri[ j ] );
      if( tq.FI ){
        if( onseg( tri[ 0 ] , tri[ j ] , tq.SE ) &&
            onseg( a[ i ] , nxta , tq.SE ) )
          good[ i ] = false;
      }else{
        if( onseg( tri[ 0 ] , tri[ j ] , a[ i ] ) ||
            onseg( tri[ 0 ] , tri[ j ] , nxta ) ||
            onseg( a[ i ] , nxta , tri[ 0 ] ) ||
            onseg( a[ i ] , nxta , tri[ j ] ) )
          good[ i ] = false;
      }
    }
    D k = ( ( nxta - a[ i ] ) ^ ( pos - a[ i ] ) ) /
          ( ( nxta - a[ i ] ) % ( nxta - a[ i ] ) );
    if( equal( k , 0.0 ) ){
      if( onseg( a[ i ] , nxta , pos ) )
        good[ i ] = false;
    }else{
      PT xp = pos + perp( nxta - a[ i ] ) * k;
      if( onseg( a[ i ] , nxta , xp ) && in_sector( xp ) )
        good[ i ] = false;
    }
  }
}
void init(){
  n = getint();
  _ = getint();
  scanf( "%lf%lf" , &theta , &r );
  theta = ( theta / 360.0 ) * pi;
  scanf( "%lf%lf" , &pos.X , &pos.Y );
  PT tp1 , tp2;
  scanf( "%lf%lf" , &tp1.X , &tp1.Y ); v = deg( tp1 );
  scanf( "%lf%lf" , &tp2.X , &tp2.Y ); d = deg( tp2 );
  for( int i = 0 ; i < n ; i ++ ){
    scanf( "%lf%lf" , &a[ i ].X , &a[ i ].Y );
    good[ i ] = true;
  }
}
void solve(){
  test_sector();
  int pret = 0;
  while( _ -- ){
    int kd , nt;
    D alpha;
    kd = getint();
    nt = getint();
    scanf( "%lf" , &alpha );
    alpha = ( alpha / 180.0 ) * pi;
    test_rec( nt - pret );
    pos = pos + vec( d ) * (D)( nt - pret );
    test_sector();
    pret = nt;
    if( kd == 1 ){
      test_sector( alpha );
      v -= alpha;
      if( v < -pi + eps ) v += 2.0 * pi;
    }else{
      d -= alpha;
      if( d < -pi + eps ) d += 2.0 * pi;
    }
  }
  printf( "Case #%d: " , ++ cs );
  for( int i = 0 ; i < n ; i ++ )
    printf( "%c" , "01"[ good[ i ] ] );
  puts( "" );
}
int main(){
    build();
    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
