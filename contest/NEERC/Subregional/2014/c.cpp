// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long double LD;
typedef long long ll;
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<ll,ll> PLL;
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
#define eps 1e-2
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
int __ = 1 , cs;
/*********default*********/
#define N 111
const LD PI = acos( -1.0 );
const LD cir = PI * 10000.0;
typedef pair<LD,LD> Pt;
void scan( Pt& tp ){
  double ta , tb;
  scanf( "%lf%lf" , &ta , &tb );
  tp = MP( ta , tb );
}
Pt operator+( const Pt& p1 , const Pt& p2 ){
  return MP( p1.FI + p2.FI , p1.SE + p2.SE );
}
Pt operator-( const Pt& p1 , const Pt& p2 ){
  return MP( p1.FI - p2.FI , p1.SE - p2.SE );
}
Pt operator*( const Pt& p1 , const D& tk ){
  return MP( p1.FI * tk , p1.SE * tk );
}
Pt operator/( const Pt& p1 , const D& tk ){
  return MP( p1.FI / tk , p1.SE / tk );
}
LD operator^( const Pt& p1 , const Pt& p2 ){
  return p1.FI * p2.SE - p1.SE * p2.FI;
}
LD operator%( const Pt& p1 , const Pt& p2 ){
  return p1.FI * p2.FI + p1.SE * p2.SE;
}
LD dist( const Pt& p1 , const Pt& p2 ){
  return sqrt( ( p1 - p2 ) % ( p1 - p2 ) );
}
Pt p[ 4 ];
vector< pair<LD,int> > v;
int n , m;
void build(){

}
LD cal_ep(){
  Pt mid = ( p[ 0 ] + p[ 1 ] ) * 0.5;
  return PI * dist( p[ 0 ] , mid ) *
              dist( p[ 2 ] , mid );
}
LD cal_rec(){
  LD tsum = p[ 3 ] ^ p[ 0 ];
  for( int i = 1 ; i < 4 ; i ++ )
    tsum += p[ i - 1 ] ^ p[ i ];
  if( tsum < 0 ) tsum = -tsum;
  return tsum * 0.5;
}
void init(){
  n = getint();
  for( int i = 1 ; i <= n ; i ++ ){
    for( int j = 0 ; j < 4 ; j ++ )
      scan( p[ j ] );
    D ecp = cal_ep();
    D area = 0;
    int ri = getint(); while( ri -- ){
      for( int j = 0 ; j < 4 ; j ++ )
        scan( p[ j ] );
      area += cal_rec();
    }
    area = ( area * cir ) / ecp;
    v.PB( MP( area , i ) );
  }
}
int type[ N ];
void solve(){
  sort( ALL( v ) );
  type[ v[ 0 ].SE ] = 1;
  for( int i = 1 ; i < n ; i ++ )
    if( equal( v[ i ].FI , v[ i - 1 ].FI ) )
      type[ v[ i ].SE ] = type[ v[ i - 1 ].SE ];
    else
      type[ v[ i ].SE ] = type[ v[ i - 1 ].SE ] + 1;
  for( int i = 1 ; i <= n ; i ++ )
    printf( "%d%c" , type[ i ] , " \n"[ i == n ] );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
