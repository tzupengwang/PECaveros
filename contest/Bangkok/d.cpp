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
#define N 1000010
vector<PII> v[ N ];
vector<PII> vv[ N ];
int n , m , st[ N ] , deg[ N ];
int a[ N ], b[ N ], c[ N ];
map<int,int> M[ N ];
void build(){

}
void init(){
  n = getint(); m = getint();
  for( int i = 0 ; i < m ; i ++ ){
    a[ i ] = getint();
    b[ i ] = getint();
    c[ i ] = getint();
    deg[ a[ i ] ] ++;
    deg[ b[ i ] ] ++;
    v[ a[ i ] ].PB( MP( c[ i ] , b[ i ] ) );
    v[ b[ i ] ].PB( MP( c[ i ] , a[ i ] ) );
  }
  for( int i = 2 ; i <= n ; i ++ )
    st[ i ] = st[ i - 1 ] + 2 * deg[ i - 1 ];
  for( int i = 1 ; i <= n ; i ++ ){
    sort( ALL( v[ i ] ) );
    for( int j = 0 ; j < deg[ i ] ; j ++ )
      M[ i ][ v[ i ][ j ].SE ] = j;
  }
  for( int i = 1 ; i <= n ; i ++ ){
    for( int j = 0 ; j < deg[ i ] ; j ++ ){
      vv[ st[ i ] + j ].PB(
          MP( st[ i ] + j + deg[ i ] , v[ i ][ j ].FI ) );
    }
    for( int j = 0 ; j < deg[ i ] - 1 ; j ++ ){
      int now = st[ i ] + j + deg[ i ];
      int nxt = now + 1;
      vv[ now ].PB( MP( nxt , v[ i ][ j + 1 ].FI -
                              v[ i ][ j ].FI ) );
      vv[ nxt ].PB( MP( now , 0 ) );
    }
    for( int j = 0 ; j < (int)v[ i ].size() ; j ++ ){
      int now = st[ i ] + j + deg[ i ];
      int nxt = st[ v[ i ][ j ].SE ] + M[ v[ i ][ j ].SE ][ i ];
      vv[ now ].PB( MP( nxt , 0 ) );
    }
  }
}
ll dst[ N ];
bool got[ N ];
typedef pair<ll,int> PLI;
priority_queue< PLI , vector<PLI> , greater<PLI> > heap;
void SP(){
  for( int i = 0 ; i < deg[ 1 ] ; i ++ )
    heap.push( MP( 0 , i ) );
  while( heap.size() ){
    PLI tp = heap.top(); heap.pop();
    ll tcst = tp.FI;
    int tnow = tp.SE;
    if( got[ tnow ] ) continue;
    got[ tnow ] = true;
    dst[ tnow ] = tcst;
    for( int i = 0 ; i < (int)vv[ tnow ].size() ; i ++ ){
      int tnxt = vv[ tnow ][ i ].FI;
      if( !got[ tnxt ] )
        heap.push( MP( tcst + vv[ tnow ][ i ].SE , tnxt ) );
    }
  }
}
void solve(){
  SP();
  ll ans = INF16;
  for( int i = 0 ; i < deg[ n ] ; i ++ )
    ans = min( ans , dst[ st[ n ] + i + deg[ n ] ] );
  printf( "%lld\n" , ans );
}
int main(){
    build();
//    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
