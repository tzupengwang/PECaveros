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
#define N 514
ll n , k , W;
ll w[ N ][ N ] , c[ N ][ N ];
int bt[ 1 << 12 ];
void build(){
}
void init(){
  n = getint();
  k = getint();
  W = getint();
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= n ; j ++ )
      w[ i ][ j ] = getint();
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= n ; j ++ )
      c[ i ][ j ] = getint() - 1;
}
int ans = -1;
vector<PII> pa;
ll dp[ N ][ N ];
int bk[ N ][ N ];
void find_ans( int nn , int nm ){
  if( nn != 1 || nm != 1 ){
    if( bk[ nn ][ nm ] == 1 )
      find_ans( nn - 1 , nm );
    else
      find_ans( nn , nm - 1 );
  }
  pa.PB( MP( nn , nm ) );
}
void cal( int clr ){
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= n ; j ++ )
      dp[ i ][ j ] = INF16;
  if( ( clr & ( 1 << c[ 1 ][ 1 ] ) ) == 0 ) return;
  dp[ 1 ][ 1 ] = w[ 1 ][ 1 ];
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= n ; j ++ ){
      if( i == 1 && j == 1 ) continue;
      if( ( ( clr >> c[ i ][ j ] ) & 1 ) == 0 ) continue;
      if( i > 1 && dp[ i - 1 ][ j ] != INF16 ){
        dp[ i ][ j ] = dp[ i - 1 ][ j ] + w[ i ][ j ];
        bk[ i ][ j ] = 1;
      }
      if( j > 1 &&
          dp[ i ][ j - 1 ] + w[ i ][ j ] < dp[ i ][ j ] ){
        dp[ i ][ j ] = dp[ i ][ j - 1 ] + w[ i ][ j ];
        bk[ i ][ j ] = 2;
      }
    }
  if( dp[ n ][ n ] > W ) return;
  ans = bt[ clr ];
  pa.clear();
  find_ans( n , n );
}
void solve(){
  for( int i = 1 ; i < ( 1 << k ) ; i ++ ){
    bt[ i ] = bt[ i / 2 ] + i % 2;
    if( ans != -1 && bt[ i ] >= ans ) continue;
    cal( i );
  }
  printf( "%d\n" , ans );
  if( ans != -1 ){
    for( size_t i = 0 ; i < pa.size() ; i ++ )
      printf( "%d %d " , pa[ i ].FI , pa[ i ].SE );
    puts( "" );
  }
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
