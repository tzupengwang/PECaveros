// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
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
bool equal( D _x ,  D _y ){
  return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , cs;
/*********default*********/
#define L 10010
char c[ L ];
int len , n , pr[ L ];
vector<int> v[ L ];
bool ball[ L ];
void build(){

}
int parse( int l , int r ){
  int nidx = ++ n;
  if( l == r - 1 ) return nidx;
  if( l == r - 2 ){
    ball[ nidx ] = true;
    return nidx;
  }
  v[ nidx ].PB( parse( l + 1 , pr[ l + 1 ] ) );
  v[ nidx ].PB( parse( pr[ r - 1 ] , r - 1 ) );
  return nidx;
}
void init(){
  vector<int> vv;
  n = 0;
  len = strlen( c + 1 );
  for( int i = 1 ; i <= len ; i ++ ) pr[ i ] = -1;
  for( int i = 1 ; i <= len ; i ++ )
    if( c[ i ] == '(' ) vv.PB( i ) , n ++;
    else if( c[ i ] == ')' ){
      pr[ vv.back() ] = i;
      pr[ i ] = vv.back();
      vv.pop_back();
    }
  for( int i = 1 ; i <= n ; i ++ ){
    v[ i ].clear();
    ball[ i ] = false;
  }
  n = 0;
  parse( 1 , len );
}
int dp[ L ][ 2 ];
int sz[ L ] , lf[ L ] , all , dep;
PII operator+( const PII& p1 , const PII& p2 ){
  return MP( p1.FI + p2.FI ,
             p1.SE + p2.SE );
}
vector<int> pos[ L ];
// sz, lf
PII DFS( int now , int tdep ){
  dep = max( dep , tdep );
  PII tp = MP( 0 , 0 );
  for( int i = 0 ; i < (int)v[ now ].size() ; i ++ )
    tp = tp + DFS( v[ now ][ i ] , tdep + 1 );
  if( ball[ now ] ) tp = tp + MP( 1 , 0 );
  if( v[ now ].size() == 0 ) tp = tp + MP( 0 , 1 );
  sz[ now ] = tp.FI;
  lf[ now ] = tp.SE;
  return tp;
}
void DP( int now , int tdep = 1 ){
  dp[ now ][ 0 ] = dp[ now ][ 1 ] = INF;
  if( v[ now ].size() == 0 ){
    for( int i = 0 ; i < (int)pos[ tdep ].size() ; i ++ )
      if( pos[ tdep ][ i ] == 1 ){
        if( ball[ now ] ) dp[ now ][ i ] = 0;
        else dp[ now ][ i ] = 1;
      }else if( pos[ tdep ][ i ] == 0 ){
        if( ball[ now ] ) dp[ now ][ i ] = 1;
        else dp[ now ][ i ] = 0;
      }
    return;
  }
  for( int i = 0 ; i < (int)v[ now ].size() ; i ++ )
    DP( v[ now ][ i ] , tdep + 1 ); 
  int son1 = v[ now ][ 0 ];
  int son2 = v[ now ][ 1 ];
  for( int i = 0 ; i < (int)pos[ tdep ].size() ; i ++ ){
    int nd = pos[ tdep ][ i ];
    for( int j = 0 ; j < (int)pos[ tdep + 1 ].size() ; j ++ )
      for( int k = 0 ; k < (int)pos[ tdep + 1 ].size() ; k ++ )
        if( pos[ tdep + 1 ][ j ] + pos[ tdep + 1 ][ k ] == nd ){
          int nxtdp = dp[ son1 ][ j ] + dp[ son2 ][ k ];
          if( nxtdp < dp[ now ][ i ] )
            dp[ now ][ i ] = nxtdp;
        }
  }
}
void solve(){
  dep = 0;
  DFS( 1 , 1 );
  for( int i = 1 ; i <= dep ; i ++ ) pos[ i ].clear();
  pos[ 1 ].PB( sz[ 1 ] );
  for( int i = 2 ; i <= dep ; i ++ ){
    for( int j = 0 ; j < (int)pos[ i - 1 ].size() ; j ++ ){
      int tmp = pos[ i - 1 ][ j ] / 2;
      pos[ i ].PB( tmp );
      pos[ i ].PB( pos[ i - 1 ][ j ] - tmp );
    }
    sort( ALL( pos[ i ] ) );
    pos[ i ].resize( unique( ALL( pos[ i ] ) ) - pos[ i ].begin() );
  }
  DP( 1 );
  int ans = INF;
  for( int i = 0 ; i < (int)pos[ 1 ].size() ; i ++ )
    ans = min( ans , dp[ 1 ][ i ] );
  if( ans == INF ) puts( "impossible" );
  else cout << ans / 2 << endl;
}
int main(){
  build();
  //__ = getint();
  while( scanf( "%s" , c + 1 ) == 1 ){
    init();
    solve();
  }
}
