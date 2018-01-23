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
#define N 1010101
LL b , k , cd , cp;
vector< PLL > d , p;
LL dsum[ N ] , psum[ N ];
void init(){
  b = getint();
  k = getint();
  cd = getint();
  cp = getint();
  for( int i = 0 ; i < cd ; i ++ ){
    d.push_back( { getint() , i + 1 } );
    if( d.back().FI < 0 ) d.pop_back();
  }
  for( int i = 0 ; i < cp ; i ++ ){
    p.push_back( { getint() , i + 1 } );
    if( p.back().FI < 0 ) p.pop_back();
  }
  sort( ALL( d ) );
  reverse( ALL( d ) );
  sort( ALL( p ) );
  reverse( ALL( p ) );
  cd = (int)d.size();
  cp = (int)p.size();
  for( int i = 0 ; i < cd ; i ++ ){
    dsum[ i ] = d[ i ].FI;
    if( i ) dsum[ i ] += dsum[ i - 1 ];
  }
  for( int i = 0 ; i < cp ; i ++ ){
    psum[ i ] = p[ i ].FI;
    if( i ) psum[ i ] += psum[ i - 1 ];
  }
}
LL bstans = -1;
LL di , pi;
void go( int td ){
  if( td > k ) return;
  LL nans = b;
  if( td ) nans += dsum[ td + 1 ];
  LL sum = 100;
  int tp = max( 0ll , min( cp , k - td ) ); 
  if( tp ) sum += psum[ tp - 1 ];
  nans *= sum;
  if( nans > bstans ){
    bstans = nans;
    di = td;
    pi = tp;
  }
}
void solve(){
  for( int i = 0 ; i <= cd ; i ++ )
    go( i );
  printf( "%lld %lld\n" , di , pi );
  for( int i = 0 ; i < di ; i ++ )
    printf( "%lld%c" , d[ i ].SE , " \n"[ i + 1 == di ] );
  if( di == 0 ) puts( "" );
  for( int i = 0 ; i < pi ; i ++ )
    printf( "%lld%c" , p[ i ].SE , " \n"[ i + 1 == pi ] );
  if( pi == 0 ) puts( "" );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
