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
#define N 111
void build(){

}
int n;
int type[ N ];
vector<int> v[ 3 ];
void init(){
  n = getint();
  v[ 1 ].clear(); v[ 2 ].clear();
  for( int i = 1 ; i <= n ; i ++ ){
    printf( "1\n%d\n" , i );
    fflush( stdout );
    type[ i ] = 2 - getint();
    v[ type[ i ] ].push_back( i );
  }
}
void solve(){
  for( int i = 1 ; i <= n ; i ++ ){
    vector<int> tmp;
    tmp.push_back( i );
    int inv = 3 - type[ i ];
    for( int j = 0 ; j < (int)v[ inv ].size() ; j ++ )
      tmp.push_back( v[ inv ][ j ] );
    printf( "%d\n" , (int)tmp.size() );
    for( int j = 0 ; j < (int)tmp.size() ; j ++ )
      printf( "%d%c" , tmp[ j ] , " \n"[ j == (int)tmp.size() - 1 ] );
    fflush( stdout );
    int x = getint();
    if( x == 0 || x == (int)tmp.size() )
      type[ i ] = 3;
  }
  puts( "-1" );
  for( int i = 1 ; i <= n ; i ++ )
    printf( "%d%c" , type[ i ] , " \n"[ i == n ] );
  fflush( stdout );
}
int main(){
  build();
  __ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
