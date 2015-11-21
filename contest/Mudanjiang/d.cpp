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
ll add( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x + _y;
  if( _ >= _mod ) _ -= _mod;
  return _;
}
ll sub( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x - _y;
  if( _ < 0 ) _ += _mod;
  return _;
}
ll mul( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x * _y;
  if( _ >= _mod ) _ %= _mod;
  return _;
}
bool equal( D _x ,  D _y ){
  return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , cs;
/*********default*********/
#define N 55
// D C[ N * N ][ N * N ];
void build(){
  // for( int i = 0 ; i < N * N ; i ++ )
    // C[ i ][ 0 ] = C[ i ][ i ] = 1.0;
  // for( int i = 2 ; i < N * N ; i ++ )
    // for( int j = 1 ; j < i ; j ++ )
      // C[ i ][ j ] = C[ i - 1 ][ j - 1 ] + C[ i - 1 ][ j ];
}
int n , m;
D dp[ N ][ N ][ N * N ];
bool got[ N ][ N ][ N * N ];
void init(){
  n = getint();
  m = getint();
}
D DP( int rn , int rm , int stp ){
  if( rn == 0 && rm == 0 ) return 0.0;
  if( stp >= n * m ) return 0.0;
  if( got[ rn ][ rm ][ stp ] ) return dp[ rn ][ rm ][ stp ];
  got[ rn ][ rm ][ stp ] = true;
  int total = n * m - stp, pos;
  D mr = 0.0;
  {
    pos = ( n - rn ) * ( m - rm ) - stp;
    if( pos > 0 )
      mr += pos * DP( rn , rm , stp + 1 );
  }
  if( rn > 0 ){
    pos = rn * ( m - rm );
    if( pos > 0 )
      mr += pos * DP( rn - 1 , rm , stp + 1 );
  }
  if( rm > 0 ){
    pos = rm * ( n - rn );
    if( pos > 0 )
      mr += pos * DP( rn , rm - 1 , stp + 1 );
  }
  if( rn > 0 && rm > 0 ){
    pos = rn * rm;
    if( pos > 0 )
      mr += pos * DP( rn - 1 , rm - 1 , stp + 1 );
  }
  return dp[ rn ][ rm ][ stp ] = 1.0 + mr / (D)total;
}
void solve(){
  for( int i = 0 ; i <= n ; i ++ )
    for( int j = 0 ; j <= m ; j ++ )
      for( int k = 0 ; k <= n * m ; k ++ )
        got[ i ][ j ][ k ] = false;
  printf( "%.12f\n" , (double)DP( n , m , 0 ) );
}
int main(){
  build();
  __ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
