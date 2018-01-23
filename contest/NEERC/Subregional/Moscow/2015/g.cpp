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
int __ = 1 , cs;
/*********default*********/
#define N 202020
void build(){

}
int n;
vector< PII > v;
vector<int> idx;
D vl( const PII& tp ){
  return ( sqrt(2) - 1 ) * (D)tp.X + tp.Y;
}
bool cmp1( int i1 , int i2 ){
  return vl( v[ i1 ] ) < vl( v[ i2 ] );
}
void init(){
  n = getint();
  for( int i = 0 ; i < n ; i ++ ){
    int tx = getint();
    int ty = getint();
    v.PB( MP( tx , ty ) );
    idx.PB( i );
  }
}
void rotate(){
  for( int i = 0 ; i < n ; i ++ ){
    swap( v[ i ].X , v[ i ].Y );
    v[ i ].X = -v[ i ].X;
  }
}
void solve(){
  int ansi = 1 , ansj = 1;
  D bstans = 0.0;
  for( int _ = 0 ; _ < 2 ; _ ++ ){
    for( int i = 0 ; i < 4 ; i ++ ){
      sort( ALL( idx ) , cmp1 );
      D dlt = vl( v[ idx.back() ] ) -
              vl( v[ idx[ 0 ] ] );
      if( dlt > bstans ){
        bstans = dlt;
        ansi = idx[ 0 ];
        ansj = idx.back();
      }
      rotate();
    }
    for( int i = 0 ; i < n ; i ++ )
      swap( v[ i ].X , v[ i ].Y );
  }
  assert( ansi != ansj );
  printf( "%d %d\n" , ansi + 1 , ansj + 1 );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
