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
#define N 505050
int n , m;
vector< pair<int,char> > v[ N ];
vector< PII > gfl[ N ] , gbl[ N ] , gfr[ N ] , gbr[ N ];
char c[ N ];
void build(){

}
void init(){
  n = getint();
  m = getint();
  for( int i = 1 ; i < n ; i ++ ){
    int ai = getint();
    int bi = getint();
    char ci[ 9 ]; scanf( "%s" , ci );
    v[ ai ].PB( MP( bi , ci[ 0 ] ) );
    v[ bi ].PB( MP( ai , ci[ 0 ] ) );
  }
  scanf( "%s" , c + 1 );
}
int dpf[ N ] , dpb[ N ];
int stf[ N ] , stb[ N ];
inline void output( int a , int b ){
  printf( "%d %d\n" , a , b );
  exit( 0 );
}
void DP1( int now , int prt ){
  stf[ now ] = stb[ now ] = now;
  for( size_t i = 0 ; i < v[ now ].size() ; i ++ ){
    int son = v[ now ][ i ].FI;
    char clr = v[ now ][ i ].SE;
    if( son != prt ){
      DP1( son , now );
      gfl[ now ].PB( MP( dpf[ son ] , stf[ son ] ) );
      gfr[ now ].PB( MP( dpf[ son ] , stf[ son ] ) );
      if( gfl[ now ].back().FI + 1 <= m && c[ gfl[ now ].back().FI + 1 ] == clr )
        gfl[ now ].back().FI ++, gfr[ now ].back().FI ++;
      gbl[ now ].PB( MP( dpb[ son ] , stb[ son ] ) );
      gbr[ now ].PB( MP( dpb[ son ] , stb[ son ] ) );
      if( m - gbl[ now ].back().FI >= 1 && c[ m - gbl[ now ].back().FI ] == clr )
        gbl[ now ].back().FI ++, gbr[ now ].back().FI ++;
    }else{
      gfl[ now ].PB( MP( 0 , now ) );
      gbl[ now ].PB( MP( 0 , now ) );
      gfr[ now ].PB( MP( 0 , now ) );
      gbr[ now ].PB( MP( 0 , now ) );
    }
  }
  for( size_t i = 1 ; i < v[ now ].size() ; i ++ ){
    if( gfl[ now ][ i - 1 ].FI > gfl[ now ][ i ].FI )
      gfl[ now ][ i ] = gfl[ now ][ i - 1 ];
    if( gbl[ now ][ i - 1 ].FI > gbl[ now ][ i ].FI )
      gbl[ now ][ i ] = gbl[ now ][ i - 1 ];
  }
  for( int i = (int)v[ now ].size() - 2 ; i >= 0 ; i -- ){
    if( gfr[ now ][ i + 1 ].FI > gfr[ now ][ i ].FI )
      gfr[ now ][ i ] = gfr[ now ][ i + 1 ];
    if( gbr[ now ][ i + 1 ].FI > gbr[ now ][ i ].FI )
      gbr[ now ][ i ] = gbr[ now ][ i + 1 ];
  }
  dpf[ now ] = gfr[ now ][ 0 ].FI; stf[ now ] = gfr[ now ][ 0 ].SE;
  dpb[ now ] = gbr[ now ][ 0 ].FI; stb[ now ] = gbr[ now ][ 0 ].SE;
  if( dpf[ now ] >= m ) output( stf[ now ] , now );
  if( dpb[ now ] >= m ) output( now , stb[ now ] );
  for( size_t i = 1 ; i < v[ now ].size() ; i ++ ){
    if( gfl[ now ][ i - 1 ].FI + gbr[ now ][ i ].FI >= m )
      output( gfl[ now ][ i - 1 ].SE , gbr[ now ][ i ].SE );
    if( gbl[ now ][ i - 1 ].FI + gfr[ now ][ i ].FI >= m )
      output( gfr[ now ][ i ].SE , gbl[ now ][ i - 1 ].SE );
  }
  // printf( "%d : %d %d %d %d\n" , now , dpf[ now ] , stf[ now ] , dpb[ now ] , stb[ now ] );
}
void DP2( int now , int prt , int dl , int fl , int dr , int fr ){
  if( dpf[ now ] + dr >= m ) output( stf[ now ] , fr );
  if( dpb[ now ] + dl >= m ) output( fl , stb[ now ] );
  for( size_t i = 0 ; i < v[ now ].size() ; i ++ ){
    int son = v[ now ][ i ].FI;
    char clr = v[ now ][ i ].SE;
    if( son == prt ) continue;
    int nxtdl = dl , nxtfl = fl;
    int nxtdr = dr , nxtfr = fr;
    if( i ){
      if( gfl[ now ][ i - 1 ].FI > nxtdl ){
        nxtdl = gfl[ now ][ i - 1 ].FI;
        nxtfl = gfl[ now ][ i - 1 ].SE;
      }
      if( gbl[ now ][ i - 1 ].FI > nxtdr ){
        nxtdr = gbl[ now ][ i - 1 ].FI;
        nxtfr = gbl[ now ][ i - 1 ].SE;
      }
    }
    if( i + 1 < v[ now ].size() ){
      if( gfr[ now ][ i + 1 ].FI > nxtdl ){
        nxtdl = gfr[ now ][ i + 1 ].FI;
        nxtfl = gfr[ now ][ i + 1 ].SE;
      }
      if( gbr[ now ][ i + 1 ].FI > nxtdr ){
        nxtdr = gbr[ now ][ i + 1 ].FI;
        nxtfr = gbr[ now ][ i + 1 ].SE;
      }
    }
    if( nxtdl + 1 <= m && c[ nxtdl + 1 ] == clr ) nxtdl ++;
    if( m - nxtdr >= 1 && c[ m - nxtdr ] == clr ) nxtdr ++;
    DP2( son , now , nxtdl , nxtfl , nxtdr , nxtfr );
  }
}
void solve(){
  DP1( 1 , -1 );
  // DP2( 1 , -1 , 0 , 1 , 0 , 1 );
  output( -1 , -1 );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
