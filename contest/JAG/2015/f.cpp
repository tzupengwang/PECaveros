// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long long ll;
typedef pair<int,int> PII;
#define mod9 1000000009ll
#define mod7 1000000007ll
#define INF  123456789ll
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
ll add( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x + _y;
  if( _ >= _mod ) _ -= _mod;
  return _;
}
ll sub( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x - _y;
  if( _ < 0 ) _ += _mod;
  return _;
}
ll mul( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x * _y;
  if( _ >= _mod ) _ %= _mod;
  return _;
}
bool equal( D _x ,  D _y ){
  return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , cs;
/*********default*********/
#define N 10010
int n , idx[ N ];
int mdist[ 9 ][ N ] , x[ 9 ];
int midx[ 9 ][ N ];
int mnidx[ 9 ];
vector<int> v[ N ];
void build(){

}
void init(){
  n = getint();
  for( int i = 1 ; i <= 3 ; i ++ ) x[ i ] = getint();
  mnidx[ 1 ] = mnidx[ 2 ] = mnidx[ 3 ] = INF;
  for( int i = 1 ; i <= 3 ; i ++ ){
    for( int j = 0 ; j < x[ i ] ; j ++ ){
      int _ = getint();
      idx[ _ ] = i;
      mnidx[ i ] = min( mnidx[ i ] , _ );
    }
  }
  int m = getint(); while( m -- ){
    int ui = getint();
    int vi = getint();
    v[ ui ].PB( vi );
    v[ vi ].PB( ui );
    // printf( "%d -> %d\n" , ui , vi );
  }
  for( int i = 1 ; i <= n ; i ++ )
    mdist[ 1 ][ i ] =
    mdist[ 2 ][ i ] =
    mdist[ 3 ][ i ] = INF;
}
bool got[ 4 ][ N ];
typedef tuple<int,int,int> tiii;
priority_queue< tiii , vector<tiii> , greater<tiii> > heap;
void BFS( int now ){
  for( int i = 1 ; i <= n ; i ++ )
    if( idx[ i ] == now )
      heap.push( MT( 0 , mnidx[ now ] , i ) );
  bool done[ 4 ] = {};
  while( heap.size() ){
    tiii tp = heap.top(); heap.pop();
    int dist = get<0>( tp );
    int mini = get<1>( tp );
    int tnow  = get<2>( tp );
    if( got[ now ][ tnow ] ) continue;
    // printf( "%d %d %d %d\n" , now , tnow , dist , mini );
    got[ now ][ tnow ] = true;
    mdist[ now ][ tnow ] = dist;
    midx[ now ][ tnow ]  = mini;
    for( int i = 0 ; i < (int)v[ tnow ].size() ; i ++ )
      if( !got[ now ][ v[ tnow ][ i ] ] ){
        // if( idx[ v[ tnow ][ i ] ] == idx[ tnow ] ) continue;
        heap.push( MT( dist + 1 , min( mini , v[ tnow ][ i ] ) , v[ tnow ][ i ] ) );
        if( idx[ v[ tnow ][ i ] ] && !done[ idx[ v[ tnow ][ i ] ] ] ){
          done[ idx[ v[ tnow ][ i ] ] ] = true;
          for( int j = 1 ; j <= n ; j ++ )
            if( idx[ j ] == idx[ v[ tnow ][ i ] ] )
              heap.push( MT( dist + 1 , min( mini , mnidx[ idx[ v[ tnow ][ i ] ] ] ) , j ) );
        }
      }
  }
}
void solve(){
  for( int i = 1 ; i <= 3 ; i ++ )
    BFS( i );
  // for( int i = 1 ; i <= n ; i ++ )
    // printf( "%d\n" , idx[ i ] );
  // for( int i = 1 ; i <= 3 ; i ++ )
    // for( int j = 1 ; j <= n ; j ++ )
      // printf( "%d %d : %d %d\n" , i , j , mdist[ i ][ j ] , midx[ i ][ j ] );
  int ans = INF, aidx = n;
  for( int i = 1 ; i <= n ; i ++ ){
    int cst = mdist[ 1 ][ i ] + mdist[ 2 ][ i ] + mdist[ 3 ][ i ];
    int mn = min( midx[ 1 ][ i ] , min( midx[ 2 ][ i ] , midx[ 3 ][ i ] ) );
    // if( idx[ i ] > 0 ) mn = min( mn , mnidx[ idx[ i ] ] );
    if( cst < ans || ( cst == ans && mn < aidx ) )
      ans = cst, aidx = mn;
  }
  printf( "%d %d\n" , ans , aidx );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
