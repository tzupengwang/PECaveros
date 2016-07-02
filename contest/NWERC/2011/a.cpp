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
#define INF18 1000000000000000000ll
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
#define N 3030
LL C[ N ][ N ];
void build(){
  for( int i = 0 ; i < N ; i ++ )
    C[ i ][ 0 ] = C[ i ][ i ] = 1;
  for( int i = 2 ; i < N ; i ++ )
    for( int j = 1 ; j < i ; j ++ ){
      if( C[ i - 1 ][ j - 1 ] == -1 ||
          C[ i - 1 ][ j     ] == -1 )
        C[ i ][ j ] = -1;
      else{
        C[ i ][ j ] = C[ i - 1 ][ j - 1 ] +
                      C[ i - 1 ][ j ];
        if( C[ i ][ j ] > INF18 )
          C[ i ][ j ] = -1;
      }
    }
}
ll m;
void init(){
  m = getint();
}
vector< PLL > ans;
inline void test( LL xx ){
  LL xm = m;
  for( int i = 1 ; i <= xx ; i ++ )
    xm *= i;
  LL bl = 1 , br = INF16 , bmid;
  while( bl <= br ){
    bmid = ( bl + br ) >> 1;
    LL vl = 1;
    for( ll i = 0 ; i < xx ; i ++ ){
      if( vl > INF18 / ( bmid + i ) ){
        vl = -1; break;
      }
      vl *= ( bmid + i );
    }
    if( vl == -1 || vl > xm )
      br = bmid - 1;
    else if( vl < xm )
      bl = bmid + 1;
    else{
      ans.push_back( { bmid + xx - 1 , xx } );
      ans.push_back( { bmid + xx - 1 , bmid - 1 } );
      return;
    }
  }
}
void solve(){
  ans.clear();
  for( int i = 1 ; i < N ; i ++ )
    for( int j = 1 ; j <= i ; j ++ )
      if( C[ i ][ j ] == m )
        ans.push_back( { i , j } );
  ans.push_back( { m , 1 } );
  ans.push_back( { m , m - 1 } );
  for( int i = 2 ; i <= 6 ; i ++ )
    test( i );
  sort( ALL( ans ) );
  ans.resize( unique( ALL( ans ) ) - ans.begin() );
  printf( "%d\n" , (int)ans.size() );
  for( size_t i = 0 ; i < ans.size() ; i ++ )
    printf( "(%lld,%lld)%c" , ans[ i ].FI , ans[ i ].SE , " \n"[ i + 1 == ans.size() ] );
}
int main(){
  build();
  __ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
