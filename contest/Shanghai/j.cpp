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
#define N 303030
void build(){

}
#define K 20
int n , M , k , ncnt , nxt[ N ][ K ] , o[ N ];
vector<PII> v[ N ] , v2[ N ];
vector<int> idx[ N ];
map<int,int> m[ N ];
inline int Nxt( int now , int tk ){
  for( int i = K - 1 ; i >= 0 ; i -- )
    if( ( tk >> i ) & 1 )
      now = nxt[ now ][ i ];
  return o[ now ];
}
void init(){
  n = getint();
  M = getint();
  k = getint();
  ncnt = n;
  for( int i = 1 ; i <= n ; i ++ ){
    v[ i ].clear();
    m[ i ].clear();
    idx[ i ].clear();
  }
  for( int i = 0 ; i <= n + M + M ; i ++ )
    v2[ i ].clear();
  for( int i = 0 ; i < M ; i ++ ){
    int tu = getint();
    int tv = getint();
    int tw = getint();
    v[ tu ].PB( MP( tw , tv ) );
    v[ tv ].PB( MP( tw , tu ) );
    idx[ tu ].PB( -1 );
    idx[ tv ].PB( -1 );
  }
  if( k == 0 ) return;
  for( int i = 1 ; i <= n ; i ++ )
    sort( ALL( v[ i ] ) );
  for( int i = 1 ; i <= n ; i ++ )
    for( size_t j = 0 ; j < v[ i ].size() ; j ++ ){
      idx[ i ][ j ] = ++ ncnt;
      o[ ncnt ] = i;
      m[ i ][ v[ i ][ j ].SE ] = ncnt;
    }
  for( int i = 1 ; i <= n ; i ++ )
    if( (int)v[ i ].size() == 1 )
      v2[ idx[ i ][ 0 ] ].PB( MP( m[ v[ i ][ 0 ].SE ][ i ] , 1 ) );
    else if( (int)v[ i ].size() > 1 ){
      for( size_t j = 0 ; j < v[ i ].size() ; j ++ ){
        int bst = -1;
        if( j == 0 ) bst = 1;
        else if( j + 1 == v[ i ].size() ) bst = j - 1;
        else if( ( v[ i ][ j ].FI - v[ i ][ j - 1 ].FI <
                   v[ i ][ j + 1 ].FI - v[ i ][ j ].FI ) ||
                 ( v[ i ][ j ].FI - v[ i ][ j - 1 ].FI ==
                   v[ i ][ j + 1 ].FI - v[ i ][ j ].FI &&
                   v[ i ][ j - 1 ].SE < v[ i ][ j + 1 ].SE ) )
          bst = j - 1;
        else bst = j + 1;
        v2[ idx[ i ][ j ] ].PB( MP( m[ v[ i ][ bst ].SE ][ i ] , 1 ) );
      }
    }
  for( int i = n + 1 ; i <= ncnt ; i ++ )
    if( v2[ i ].size() )
      nxt[ i ][ 0 ] = v2[ i ][ 0 ].FI;
    else{
      assert( false );
      nxt[ i ][ 0 ] = -1;
    }
  for( int i = 1 ; i < K ; i ++ )
    for( int j = n + 1 ; j <= ncnt ; j ++ )
      nxt[ j ][ i ] = nxt[ nxt[ j ][ i - 1 ] ][ i - 1 ];
  for( int i = n + 1 ; i <= ncnt ; i ++ )
    v2[ i ].PB( MP( Nxt( i , k ) , k ) );
  for( int i = 1 ; i <= n ; i ++ )
    for( size_t j = 0 ; j < v[ i ].size() ; j ++ )
      v2[ i ].PB( MP( m[ v[ i ][ j ].SE ][ i ] , 1 ) );
}
ll dst[ N ];
bool got[ N ];
queue<int> Q;
void solve2(){
  for( int i = 1 ; i <= n ; i ++ ){
    got[ i ] = false;
    dst[ i ] = INF16;
  }
  got[ 1 ] = true; dst[ 1 ] = 0;
  while( Q.size() ) Q.pop();
  Q.push( 1 );
  while( Q.size() ){
    int tn = Q.front(); Q.pop();
    for( size_t i = 0 ; i < v[ tn ].size() ; i ++ )
      if( !got[ v[ tn ][ i ].SE ] ){
        got[ v[ tn ][ i ].SE ] = true;
        dst[ v[ tn ][ i ].SE ] = dst[ tn ] + 1;
        Q.push( v[ tn ][ i ].SE );
      }
  }
  printf( "Case #%d: %lld\n" , ++ _cs , dst[ n ] == INF16 ? -1 : dst[ n ] );
}
typedef pair<ll,int> PLI;
priority_queue< PLI,vector<PLI>,greater<PLI> > heap;
void solve(){
  if( k == 0 ){
    solve2();
    return;
  }
  for( int i = 1 ; i <= ncnt ; i ++ ){
    got[ i ] = false;
    dst[ i ] = INF16;
  }
  heap.push( MP( 1 , m[ v[ 1 ][ 0 ].SE ][ 1 ] ) );
  heap.push( MP( 0 , 1 ) );
  int now = m[ v[ 1 ][ 0 ].SE ][ 1 ];
  for( int i = 1 ; i <= k ; i ++ ){
    heap.push( MP( i , o[ now ] ) );
    now = nxt[ now ][ 0 ];
  }
  while( heap.size() ){
    PLI tp = heap.top(); heap.pop();
    if( got[ tp.SE ] ) continue;
    got[ tp.SE ] = true;
    dst[ tp.SE ] = tp.FI;
    for( size_t i = 0 ; i < v2[ tp.SE ].size() ; i ++ )
      if( !got[ v2[ tp.SE ][ i ].FI ] )
        heap.push( MP( tp.FI + v2[ tp.SE ][ i ].SE , v2[ tp.SE ][ i ].FI ) );
  }
  ll ans = dst[ n ];
  for( size_t i = 0 ; i < v[ n ].size() ; i ++ )
    ans = min( ans , dst[ idx[ n ][ i ] ] );
  printf( "Case #%d: %lld\n" , ++ _cs , ans == INF16 ? -1 : ans );
}
int main(){
  build();
  __ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
