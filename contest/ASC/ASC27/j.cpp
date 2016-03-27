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
struct Int{
  vector<int> v;
  Int(){ v.clear(); }
  Int( int vl ){
    v.clear();
    if( vl == 0 )
      v.PB( 0 );
    while( vl ){
      v.PB( vl % 10 );
      vl /= 10;
    }
  }
  void normalize(){
    for( size_t i = 0 ; i + 1 < v.size() ; i ++ ){
      v[ i + 1 ] += v[ i ] / 10;
      v[ i ] %= 10;
    }
    while( (int)v.size() > 1 && v.back() == 0 )
      v.pop_back();
  }
  Int operator+( const Int& ti ) const{
    Int tmp; tmp.v.resize( max( (int)v.size() , (int)ti.v.size() ) + 2 );
    for( size_t i = 0 ; i < tmp.v.size() ; i ++ ){
      if( i < v.size() ) tmp.v[ i ] += v[ i ];
      if( i < ti.v.size() ) tmp.v[ i ] += ti.v[ i ];
    }
    tmp.normalize();
    return tmp;
  }
  Int operator-( const Int& ti ) const{
    Int tmp; tmp.v.resize( max( (int)v.size() , (int)ti.v.size() ) + 2 );
    for( size_t i = 0 ; i < tmp.v.size() ; i ++ ){
      if( i < v.size() ) tmp.v[ i ] += v[ i ];
      if( i < ti.v.size() ) tmp.v[ i ] -= ti.v[ i ];
    }
    for( size_t i = 0 ; i + 1 < tmp.v.size() ; i ++ ){
      if( tmp.v[ i ] < 0 ){
        tmp.v[ i ] += 10;
        tmp.v[ i + 1 ] --;
      }
    }
    tmp.normalize();
    return tmp;
  }
  Int operator*( const Int& ti ) const{
    Int tmp; tmp.v.resize( (int)v.size() + (int)ti.v.size() + 2 );
    for( size_t i = 0 ; i < v.size() ; i ++ )
      for( size_t j = 0 ; j < ti.v.size() ; j ++ )
        tmp.v[ i + j ] += v[ i ] * ti.v[ j ];
    tmp.normalize();
    return tmp;
  }
  void print(){
    for( int i = (int)v.size() - 1 ; i >= 0 ; i -- )
      putchar( v[ i ] + '0' );
    return;
  }
};
#define N 55
Int dp1[ N ][ N ] , dp2[ N ][ N ] , ans;
int n , m;
void build(){
  ans = Int( 0 );
}
void init(){
  n = getint();
  m = getint();
}
void solve(){
  dp1[ 1 ][ 0 ] = Int( 1 );
  dp1[ 1 ][ 1 ] = Int( 1 );
  dp1[ 1 ][ 2 ] = Int( 1 );
  dp1[ 1 ][ 3 ] = Int( 0 );
  dp1[ 1 ][ 4 ] = Int( 0 );
  for( int i = 2 ; i <= m ; i ++ ){
    dp1[ i ][ 0 ] = Int( 1 );
    dp1[ i ][ 1 ] = dp1[ i - 1 ][ 0 ] + dp1[ i - 1 ][ 2 ] + dp1[ i - 1 ][ 1 ] * Int( n - 1 );
    dp1[ i ][ 2 ] = Int( 1 );
    dp1[ i ][ 3 ] = dp1[ i - 1 ][ 3 ] + dp1[ i - 1 ][ 0 ] + dp1[ i - 1 ][ 1 ] * Int( n - 1 );
    dp1[ i ][ 4 ] = dp1[ i - 1 ][ 4 ] + dp1[ i - 1 ][ 2 ] + dp1[ i - 1 ][ 1 ] * Int( n - 1 );
  }
  for( int i = 0 ; i <= n ; i ++ )
    dp2[ 1 ][ i ] = Int( 1 );
  for( int i = 2 ; i <= m ; i ++ )
    for( int j = 0 ; j <= n ; j ++ ){
      dp2[ i ][ j ] = Int( 0 );
      for( int k = 0 ; k <= j ; k ++ )
        dp2[ i ][ j ] = dp2[ i ][ j ] + dp2[ i - 1 ][ k ];
    }
  Int ans1( 0 ) , ans2( 0 );
  ans1 = dp1[ m ][ 2 ] + dp1[ m ][ 3 ] + dp1[ m ][ 4 ] + dp1[ m ][ 1 ] * Int( n - 1 );
  for( int j = 1 ; j <= n ; j ++ )
    ans2 = ans2 + dp2[ m ][ j ];
  ans1 = ans1 - ans2;
  ans = ans + ans1;
  // ans1.print(); puts( "" );
}
void Solve(){
  solve();
  swap( n , m );
  solve();
  ans.print(); puts( "" );
}
int main(){
  freopen( "separable.in" , "r" , stdin );
  freopen( "separable.out" , "w" , stdout );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    Solve();
  }
}
