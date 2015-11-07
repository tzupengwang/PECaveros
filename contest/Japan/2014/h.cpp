// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef long double D;
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
#define N 9
#define X FI
#define Y SE
typedef pair<D,D> Pt;
typedef pair<Pt,Pt> Seg;
const D R = 100.0;
const D Pi = acosl( -1.0 );
void scan( Pt& tp ){
  tp.X = getint();
  tp.Y = getint();
}
void print( const Pt& tp ){
  printf( "%.6f %.6f\n" , (double)tp.X , (double)tp.Y );
}
D Deg( const Pt& p1 ){
  return atan2l( p1.Y , p1.X );
}
Pt operator+( const Pt& p1 , const Pt& p2 ){
  return MP( p1.X + p2.X , p1.Y + p2.Y );
}
Pt operator-( const Pt& p1 , const Pt& p2 ){
  return MP( p1.X - p2.X , p1.Y - p2.Y );
}
Pt operator*( const Pt& p1 , const D& tk ){
  return MP( p1.X * tk , p1.Y * tk );
}
Pt operator/( const Pt& p1 , const D& tk ){
  return MP( p1.X / tk , p1.Y / tk );
}
D operator%( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
D operator^( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
D norm( const Pt& tp ){
  return sqrt( tp % tp );
}
Pt rotate( const Pt& p1 , const D& tdeg ){
  return MP( p1.X * cosl( tdeg ) - p1.Y * sinl( tdeg ),
             p1.X * sinl( tdeg ) + p1.Y * cosl( tdeg ) );
}
D dist( const Pt& p1, const Pt& p2 ){
  return norm( p1 - p2 );
}
D onSeg( const Pt& tp, const Seg& ts ){
  Pt dlt = ts.SE - ts.FI;
  return ( ( tp % dlt ) - ( ts.FI % dlt ) ) /
                            ( dlt % dlt );
}
// points on cir
vector<Pt> tangP2C( const Pt& cir, const Pt& tp ){
  vector<Pt> pset;
  D ndist = dist( tp , cir );
  D ndeg = acosl( R / ndist );
  Pt rvec = ( ( tp - cir ) / ndist ) * R;
  pset.PB( cir + rotate( rvec , +ndeg ) );
  pset.PB( cir + rotate( rvec , -ndeg ) );
  return pset;
}
// points on c1
vector<Pt> tangC2C( const Pt& c1 , const Pt& c2 ){
  vector<Pt> pset;
  D ndist = dist( c1 , c2 );
  Pt rvec = ( ( c2 - c1 ) / ndist ) * R;
  pset.PB( c1 + rotate( rvec , +Pi * 0.5 ) );
  pset.PB( c1 + rotate( rvec , -Pi * 0.5 ) );
  if( ndist > R + R + eps ){
    D ndeg = acosl( ( R + R ) / ndist );
    pset.PB( c1 + rotate( rvec , +ndeg ) );
    pset.PB( c1 + rotate( rvec , -ndeg ) );
  }else{
    D ndeg = acosl( ndist / ( R + R ) );
    pset.PB( c1 + rotate( rvec , +ndeg ) );
    pset.PB( c1 + rotate( rvec , -ndeg ) );
  }
  return pset;
}
void add( vector<Pt>& v1, const vector<Pt>& v2 ){
  for( size_t i = 0 ; i < v2.size() ; i ++ )
    v1.PB( v2[ i ] );
}
void build(){

}
int n;
Pt s, g, a[ N ];
bool good( const Pt& tp ){
  for( int i = 0 ; i < n ; i ++ )
    if( dist( a[ i ] , tp ) < R - eps )
      return false;
  return true;
}
bool save( const Seg& ts ){
  for( int i = 0 ; i < n ; i ++ ){
    D tk = onSeg( a[ i ] , ts );
    Pt tp = ts.FI + ( ts.SE - ts.FI ) * tk;
    if( dist( a[ i ] , tp ) > R - eps ) continue;
    if( -eps < tk && tk < 1.0 + eps ){
      return false;
    }
    if( dist( a[ i ] , ts.FI ) < R - eps ||
        dist( a[ i ] , ts.SE ) < R - eps ){
      return false;
    }
  }
  return true;
}
void init(){
  n = getint();
  s.X = s.Y = 0.0;
  scan( g );
  for( int _ = 0 ; _ < n ; _ ++ ) scan( a[ _ ] );
}
vector<Pt> npt;
int np;
int S = 0, G = 1;
vector< pair<int,D> > v[ 514 ];
bool cmp( Pt p1 , Pt p2 ){
  return Deg( p1 ) < Deg( p2 );
}
void pre_solve(){
  npt.PB( s );
  npt.PB( g );
  if( save( MP( s , g ) ) ){
    D idist = dist( s , g );
    v[ S ].PB( MP( G , idist ) );
    v[ G ].PB( MP( S , idist ) );
  }
  np = 2;
  for( int _ = 0 ; _ < n ; _ ++ ){
    vector<Pt> pset;
    vector<Pt> tset;
    tset = tangP2C( a[ _ ] , s ); add( pset , tset );
    tset = tangP2C( a[ _ ] , g ); add( pset , tset );
    for( int u = 0 ; u < n ; u ++ ) if( _ != u ){
      tset = tangC2C( a[ _ ] , a[ u ] );
      add( pset , tset );
    }
    int xn = 0;
    for( size_t u = 0 ; u < pset.size() ; u ++ )
      if( good( pset[ u ] ) )
        pset[ xn ++ ] = pset[ u ];
    pset.resize( xn );
    for( size_t u = 0 ; u < pset.size() ; u ++ )
      pset[ u ] = pset[ u ] - a[ _ ];
    sort( ALL( pset ) , cmp );
    for( size_t u = 0 ; u < pset.size() ; u ++ )
      pset[ u ] = pset[ u ] + a[ _ ];
    for( size_t u = 0 ; u < pset.size() ; u ++ ){
      int id = np + u;
      npt.PB( pset[ u ] );
      if( save( MP( pset[ u ] , s ) ) ){
        v[ id ].PB( MP( S , dist( pset[ u ] , s ) ) );
        v[ S ].PB( MP( id , dist( pset[ u ] , s ) ) );
      }
      if( save( MP( pset[ u ] , g ) ) ){
        v[ id ].PB( MP( G , dist( pset[ u ] , g ) ) );
        v[ G ].PB( MP( id , dist( pset[ u ] , g ) ) );
      }
      for( int j = 0 ; j < np ; j ++ )
        if( save( MP( pset[ u ] , npt[ j ] ) ) ){
          v[ j ].PB( MP( id , dist( pset[ u ], npt[ j ] ) ) );
          v[ id ].PB( MP( j , dist( pset[ u ], npt[ j ] ) ) );
        }
      int nxt = ( u + 1 ) % pset.size();
      int nxtid = np + nxt;
      D cdeg = Deg( pset[ nxt ] - a[ _ ] ) -
               Deg( pset[ u ]   - a[ _ ] );
      if( cdeg < 0.0 ) cdeg += 2.0 * Pi;
      Pt mid = a[ _ ] + rotate( pset[ u ] - a[ _ ] , cdeg * 0.5 );
      if( !good( mid ) ) continue;
      D cdist = cdeg * R;
      v[ id ].PB( MP( nxtid , cdist ) );
      v[ nxtid ].PB( MP( id , cdist ) );
    }
    np += (int)pset.size();
  }
}
D dst[ 514 ];
bool got[ 514 ];
typedef pair<D,int> PDI;
priority_queue< PDI , vector<PDI> , greater<PDI> > heap;
void SP(){
  heap.push( MP( 0.0 , S ) );
  while( heap.size() ){
    PDI tp = heap.top(); heap.pop();
    D tdist = tp.FI;
    int now = tp.SE;
    if( got[ now ] ) continue;
    got[ now ] = true;
    dst[ now ] = tdist;
    for( int i = 0 ; i < (int)v[ now ].size() ; i ++ )
      if( !got[ v[ now ][ i ].FI ] )
        heap.push( MP( tdist + v[ now ][ i ].SE ,
                       v[ now ][ i ].FI ) );
  }
  if( !got[ G ] ) puts( "0.0" );
  else printf( "%.12f\n" , (double)dst[ G ] );
}
void solve(){
  pre_solve();
  SP();
}
int main(){
    build();
//    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
