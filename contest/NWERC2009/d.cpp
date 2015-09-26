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
#define N 110
typedef pair<D,D> PT;
#define X first
#define Y second
int n , d;
vector<PT> v;
D len , pr , q;
D sqr( D x ){ return x * x; }
D dist( const PT& x, const PT& y ){
  return sqrt( sqr( x.X - y.X ) +
               sqr( x.Y - y.Y ) );
}
PT operator-( const PT& p1 , const PT& p2 ){
  return MP( p1.X - p2.X , p1.Y - p2.Y );
}
PT operator+( const PT& p1 , const PT& p2 ){
  return MP( p1.X + p2.X , p1.Y + p2.Y );
}
PT operator*( const PT& p1 , const D& pp ){
  return MP( p1.X * pp , p1.Y * pp );
}
void build(){

}
D mypow( D _a , int _x ){
  if( _x == 0 ) return 1.0;
  D _ta = sqr( mypow( _a , _x / 2 ) );
  if( _x & 1 ) _ta *= _a;
  return _ta;
}
void init(){
  v.clear();
  len = 0.0;
  n = getint();
  for( int i = 0 ; i < n ; i ++ ){
    D tx = getint();
    D ty = getint();
    if( i ) len += dist( v.back() , MP( tx , ty ) );
    v.PB( MP( tx , ty ) );
  }
  pr = len / dist( v[ 0 ] , v.back() );
  d = getint();
  scanf( "%lf" , &q );
  q *= len * mypow( pr , d - 1 );
}
void trans( PT ps , PT pt ){
  PT ov = v.back() - v[ 0 ];
  D dego = atan2( ov.Y , ov.X );
  PT nv = pt - ps;
  D degn = atan2( nv.Y , nv.X );
  D dlt = degn - dego;
  for( int i = 1 ; i < n ; i ++ ){
    PT dv = v[ i ] - v[ 0 ];
    PT gv = MP( cos( dlt ) * dv.X - sin( dlt ) * dv.Y ,
                sin( dlt ) * dv.X + cos( dlt ) * dv.Y );
    v[ i ] = v[ 0 ] + gv;
  }
  vector<PT> nxtv;
  D yy = dist( ps , pt ) / dist( v[ 0 ] , v.back() );
  nxtv.PB( ps );
  for( int i = 1 ; i < n ; i ++ ){
    PT tv = v[ i ] - v[ i - 1 ];
    nxtv.PB( nxtv.back() + tv * yy );
  }
  v = nxtv;
}
void go( int dep , D res ){
  for( int i = 1 ; i < (int)v.size() ; i ++ ){
    D rlen = dist( v[ i - 1 ] , v[ i ] ) * mypow( pr , d - dep );
    if( rlen < res - eps ) res -= rlen;
    else if( dep == d ){
      D olen = dist( v[ i - 1 ] , v[ i ] );
      PT ans = v[ i - 1 ] + ( v[ i ] - v[ i - 1 ] ) * ( res / olen );
      printf( "(%.12f,%.12f)\n" , ans.X , ans.Y );
      return;
    }else{
      trans( v[ i - 1 ] , v[ i ] );
      go( dep + 1 , res );
      return;
    }
  }
}
void solve(){
  go( 1 , q );
}
int main(){
    build();
    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
