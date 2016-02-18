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

const int MAXN = 100010;

int n , m , h[ MAXN ];
vector< PII > qs[ MAXN ];

struct Seg {
  int dat[ MAXN << 2 ];
  void init( int id , int l , int r ) {
    if( l == r ) {
      dat[ id ] = l;
      return ;
    }
    int mid = ( l + r ) / 2;
  }
};

struct Res {
  int ans , cnt1;
  set<int> st[ 2 ];
};

void build(){
}

void init(){
  n = getint();
  m = getint();
  for( int i = 1 ; i <= n-1 ; i++ ) {
    h[ i ] = getint();
    qs[ i ].clear();
  }
  for( int i = 0 ; i < m ; i++ ) {
    int x , y , z;
    x = getint();
    y = getint();
    z = getint();
    qs[ x ].push_back( { y , z } );
  }
}

Res dq( int l , int r ) {
  if( l > r ) return Res{ 0 , 0 };

}

void solve(){
  h[ 0 ] = h[ n ] = 2000000000;
  Res ans = dq( 1 , n-1 );
  printf( "%d\n" , ans.ans );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    printf( "Case #%d: " , ++_cs );
    init();
    solve();
  }
}
