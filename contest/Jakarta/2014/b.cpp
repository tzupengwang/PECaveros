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
#define N 110
int n , m , deg[ N ];
vector<int> v[ N ];
bool vv[ N ][ N ];
void build(){

}
void init(){
  n = getint();
  m = getint();
  for( int i = 1 ; i <= n ; i ++ ) v[ i ].clear();
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= n ; j ++ )
      vv[ i ][ j ] = false;
  for( int i = 0 ; i < m ; i ++ ){
    int tu = getint();
    int tv = getint();
    v[ tu ].PB( tv );
    v[ tv ].PB( tu );
    vv[ tu ][ tv ] =
    vv[ tv ][ tu ] = true;
  }
  for( int i = 1 ; i <= n ; i ++ )
    deg[ i ] = (int)v[ i ].size();
}
int got[ N ] , got2[ N ] , cnt;
void DFS1( int now ){
  got[ now ] = true;
  cnt ++;
  for( int i = 0 ; i < (int)v[ now ].size() ; i ++ )
    if( !got[ v[ now ][ i ] ] )
      DFS1( v[ now ][ i ] );
}
int cdeg , cdeg2 , nd1 , nd2;
void DFS2( int now ){
  got2[ now ] = true;
  if( deg[ now ] == cnt / 2 ){
    cdeg ++;
    if( !nd1 ) nd1 = now;
    else if( !nd2 ) nd2 = now;
  }
  if( deg[ now ] == cnt / 2 - 1 ) cdeg2 ++;
  for( int i = 0 ; i < (int)v[ now ].size() ; i ++ )
    if( !got2[ v[ now ][ i ] ] )
      DFS2( v[ now ][ i ] );
}
bool good(){
  for( int i = 0 ; i < cnt / 2 ; i ++ ) if( v[ nd1 ][ i ] != nd2 )
    for( int j = i + 1 ; j < cnt / 2 ; j ++ ) if( v[ nd1 ][ j ] != nd2 )
      if( !vv[ v[ nd1 ][ i ] ][ v[ nd1 ][ j ] ] )
        return false;
  for( int i = 0 ; i < cnt / 2 ; i ++ ) if( v[ nd2 ][ i ] != nd1 )
    for( int j = i + 1 ; j < cnt / 2 ; j ++ ) if( v[ nd2 ][ j ] != nd1 )
      if( !vv[ v[ nd2 ][ i ] ][ v[ nd2 ][ j ] ] )
        return false;
  return true;
}
void solve(){
  int ans = 0;
  for( int i = 1 ; i <= n ; i ++ )
    got[ i ] = got2[ i ] = false;
  for( int i = 1 ; i <= n ; i ++ )
    if( !got[ i ] ){
      cnt = 0;
      DFS1( i );
      nd1 = nd2 = cdeg = cdeg2 = 0;
      DFS2( i );
      if( cdeg == 2 && cdeg2 == cnt - 2 ){
        if( good() )
          ans ++;
      }
    }
  printf( "Case #%d: %d\n" , ++ cs , ans );
}
int main(){
    build();
    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
