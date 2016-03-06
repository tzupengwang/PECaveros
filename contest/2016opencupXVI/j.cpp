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
#define N 111
#define M 1000001
void build(){

}
bitset<101> dp[ 2 ][ M ];
int n , tdp[ 2 ][ M ] , p[ 2 ] , w[ 2 ][ N ];
void init(){
  n = getint();
  for( int i = 0 ; i < 2 ; i ++ ){
    p[ i ] = getint();
    for( int j = 1 ; j <= n ; j ++ )
      w[ i ][ j ] = getint();
  }
}
void cal(){
  for( int i = 0 ; i < p[ 0 ] ; i ++ ){
    dp[ 0 ][ i ].reset();
    tdp[ 0 ][ i ] = 0;
  }
  for( int i = 1 ; i <= n ; i ++ ){
    int now = i % 2 , pre = 1 - now;
    for( int j = 0 ; j < p[ 0 ] ; j ++ ){
      dp[ now ][ j ] = dp[ pre ][ j ];
      tdp[ now ][ j ] = tdp[ pre ][ j ];
    }
    for( int k = p[ 0 ] - 1 ; k >= w[ 0 ][ i ] ; k -- )
      if( tdp[ pre ][ k - w[ 0 ][ i ] ] + w[ 1 ][ i ] >
          tdp[ now ][ k ] ){
        tdp[ now ][ k ] = tdp[ pre ][ k - w[ 0 ][ i ] ] + w[ 1 ][ i ];
        dp[ now ][ k ] = dp[ pre ][ k - w[ 0 ][ i ] ];
        dp[ now ][ k ][ i ] = 1;
      }
  }
  int lst = n & 1;
  for( int i = 0 ; i < p[ 0 ] ; i ++ )
    if( tdp[ lst ][ i ] >= p[ 1 ] ){
      puts( "NO" );
      for( int j = 1 ; j <= n ; j ++ )
        if( dp[ lst ][ i ][ j ] )
          putchar( '1' );
        else
          putchar( '0' );
      puts( "" );
      exit( 0 );
    }
}
void solve(){
  cal();
  swap( p[ 0 ] , p[ 1 ] );
  for( int i = 1 ; i <= n ; i ++ )
    swap( w[ 0 ][ i ] , w[ 1 ][ i ] );
  cal();
  puts( "YES" );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
