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
#define N 10010
#define M 100010
vector<int> g[ N ] , rg[ N ];
vector<int> st , v2[ N ];
vector<PII> v[ N ] , vv[ N ];
int n , m , no[ N ] , nidx , indeg[ N ] , dst[ N ];
void build(){

}
bool vst[ N ];
void DFS1( int now ){
  vst[ now ] = true;
  for( int i = 0 ; i < (int)g[ now ].size() ; i ++ )
    if( !vst[ g[ now ][ i ] ] )
      DFS1( g[ now ][ i ] );
  st.PB( now );
}
void DFS2( int now ){
  vst[ now ] = true;
  no[ now ] = nidx;
  for( int i = 0 ; i < (int)rg[ now ].size() ; i ++ )
    if( !vst[ rg[ now ][ i ] ] )
      DFS2( rg[ now ][ i ] );
}
void kosaraju(){
  for( int i = 1 ; i <= n ; i ++ ) if( !vst[ i ] )
    DFS1( i );
  for( int i = 1 ; i <= n ; i ++ ) vst[ i ] = false;
  for( int i = n - 1 ; i >= 0 ; i -- ) if( !vst[ st[ i ] ] ){
    nidx ++;
    DFS2( st[ i ] );
  }
}
void init(){
  n = getint();
  m = getint();
  while( m -- ){
    int a = getint();
    int b = getint();
    int c = getint();
    v[ a ].PB( MP( b , -c ) );
    g[ a ].PB( b );
    rg[ b ].PB( a );
    v2[ a ].PB( b );
    v2[ b ].PB( a );
  }
}
queue<int> Q;
bool bn[ N ];
int tmn;
void DFS3( int now ){
  bn[ now ] = true;
  tmn = min( tmn , dst[ now ] );
  for( int i = 0 ; i < (int)vv[ now ].size() ; i ++ )
    if( !bn[ vv[ now ][ i ].FI ] )
      DFS3( vv[ now ][ i ].FI );
}
void solve(){
  kosaraju();
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 0 ; j < (int)v[ i ].size() ; j ++ )
      if( no[ i ] == no[ v[ i ][ j ].FI ] ){
        if( v[ i ][ j ].SE < 0 ){
          puts( "-1" );
          exit( 0 );
        }
      }else{
        vv[ no[ i ] ].PB( MP( no[ v[ i ][ j ].FI ] , v[ i ][ j ].SE ) );
        indeg[ no[ v[ i ][ j ].FI ] ] ++;
      }
  for( int i = 1 ; i <= nidx ; i ++ ) if( indeg[ i ] == 0 )
    Q.push( i );
  while( Q.size() ){
    int tn = Q.front(); Q.pop();
    for( int i = 0 ; i < (int)vv[ tn ].size() ; i ++ ){
      dst[ vv[ tn ][ i ].FI ] = min( dst[ vv[ tn ][ i ].FI ] ,
                                    dst[ tn ] + vv[ tn ][ i ].SE );
      indeg[ vv[ tn ][ i ].FI ] --;
      if( indeg[ vv[ tn ][ i ].FI ] == 0 )
        Q.push(  vv[ tn ][ i ].FI );
    }
  }
  for( int i = 1 ; i <= nidx ; i ++ )
    if( dst[ i ] < -20000 ){
      puts( "-1" );
      exit( 0 );
    }
  DFS3( no[ n ] );
  int dlt = -10000 - tmn;
  for( int i = 1 ; i <= n ; i ++ )
    if( bn[ no[ i ] ] )
      printf( "%d%c" , dst[ no[ i ] ] + dlt , " \n"[ i == n ] );
    else
      printf( "%d%c" , dst[ no[ i ] ] + 10000 , " \n"[ i == n ] );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
