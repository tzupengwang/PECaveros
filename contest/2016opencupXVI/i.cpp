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
#define N (1ll<<20)
int cnt[ N ];
void build(){
  for( int i = 1 ; i < N ; i ++ )
    cnt[ i ] = cnt[ i / 2 ] + i % 2;
}
set<int> s[ 2 ];
typedef set<int>::iterator si;
#define A 487237ll
#define B 1011807ll
inline ll nxt( ll tmp ){
  return ( tmp * A + B ) % N;
}
void init(){
  for( int i = 0 ; i < N ; i ++ )
    s[ 0 ].insert( i );
}
void solve(){
  int pn = getint() , lst = 0;
  for( int now = 1 ; ; now = 1 - now ){
    int pre = 1 - now;
    s[ now ].clear();
    puts( "1" ); fflush( stdout );
    int n = getint();
    if( n == -1 ) exit( 0 );
    if( n < pn ){
      for( si it = s[ pre ].begin() ; it != s[ pre ].end() ; it ++ )
        if( cnt[ (*it) ] % 2 == 0 )
          s[ now ].insert( nxt( *it ) );
    }else{
      for( si it = s[ pre ].begin() ; it != s[ pre ].end() ; it ++ )
        if( cnt[ (*it) ] % 2 == 1 )
          s[ now ].insert( nxt( *it ) );
    }
    lst = now;
    pn = n;
    if( (int)s[ now ].size() == 1 ) break;
  }
  int X = *s[ lst ].begin();
  while( true ){
    if( cnt[ X ] % 2 == 0 ){
      puts( "1" ); fflush( stdout );
      pn = getint();
      if( pn == -1 ) exit( 0 );
    }else{
      printf( "%d\n" , min( pn , 200 - pn ) );
      fflush( stdout );
      pn = getint();
      if( pn == -1 ) exit( 0 );
    }
    X = nxt( X );
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
