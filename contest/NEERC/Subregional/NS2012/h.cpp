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
#define N 50505
int bt[ 100 ];
void build(){
  for( int i = 1 ; i < 100 ; i ++ )
    bt[ i ] = bt[ i / 2 ] + i % 2;
}
int n;
char c[ N ][ 9 ];
void init(){
  n = getint();
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%s" , c[ i ] );
}
ll ans[ 6 ];
#define BS 65
int trans( char x ){
  if( x >= '0' && x <= '9' ) return x - '0';
  if( x >= 'A' && x <= 'Z' ) return x - 'A' + 10;
  if( x >= 'a' && x <= 'z' ) return x - 'a' + 36;
  return 64;
}
map<int,int> M;
int vl[ 5 ] , tvl[ 5 ];
inline int hsvl(){
  int hsh = 0;
  for( int j = 0 ; j < 5 ; j ++ )
    hsh = hsh * BS + tvl[ j ];
  return hsh;
}
void add( int idx ){
  for( int i = 0 ; i < 5 ; i ++ )
    vl[ i ] = trans( c[ idx ][ i ] );
  for( int i = 0 ; i < ( 1 << 5 ) ; i ++ ){
    for( int j = 0 ; j < 5 ; j ++ )
      if( ( ( i >> j ) & 1 ) == 0 )
        tvl[ j ] = vl[ j ];
      else tvl[ j ] = BS - 1;
    M[ hsvl() ] ++;
  }
}
void solve(){
  add( 0 );
  for( int i = 1 ; i < n ; i ++ ){
    ll cnt[ 33 ] = {};
    for( int j = 0 ; j < 5 ; j ++ )
      vl[ j ] = trans( c[ i ][ j ] );
    for( int j = 0 ; j < ( 1 << 5 ) ; j ++ ){
      for( int k = 0 ; k < 5 ; k ++ )
        if( ( ( j >> k ) & 1 ) == 0 )
          tvl[ k ] = vl[ k ];
        else tvl[ k ] = BS - 1;
      int vl = hsvl();
      if( M.count( vl ) ) cnt[ j ] += M[ vl ];
    }
    for( int j = 0 ; j < ( 1 << 5 ) ; j ++ )
      for( int k = 0 ; k < j ; k ++ )
        if( ( j & k ) == k )
          cnt[ j ] -= cnt[ k ];
    for( int j = 0 ; j < ( 1 << 5 ) ; j ++ )
      ans[ bt[ j ] ] += cnt[ j ];
    add( i );
  }
  for( int i = 0 ; i < 6 ; i ++ )
    printf( "%lld%c" , ans[ i ] , " \n"[ i + 1 == 6 ] );
}
int main(){
  freopen( "high.in" , "r" , stdin );
  freopen( "high.out" , "w" , stdout );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
