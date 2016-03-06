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
#define N 333
void build(){

}
ll n , a[ N ][ N ] , ans[ N ];
void init(){
  n = getint();
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= n ; j ++ )
      a[ i ][ j ] = getint();
}
vector<int> v[ N ];
ll dst[ N ] , from[ N ];
bool got[ N ];
int vc[ N ] , vt;
void DFS( int root , int now , int prt , int dep , ll tdst ){
  vc[ vt ++ ] = now;
  if( dep != 1 ){
    if( a[ root ][ now ] != -1 )
      ans[ root ] = min( ans[ root ] , tdst + a[ root ][ now ] );
  }
  for( size_t i = 0 ; i < v[ now ].size() ; i ++ )
    if( v[ now ][ i ] != prt )
      DFS( root , v[ now ][ i ] , now , dep + 1 , tdst + a[ now ][ v[ now ][ i ] ] );
}
void gogogo( int root ){
  vt = 0; ans[ root ] = INF16;
  int pre = 0;
  for( size_t u = 0 ; u < v[ root ].size() ; u ++ ){
    DFS( root , v[ root ][ u ] , root , 1 , a[ root ][ v[ root ][ u ] ] );
    for( int i = pre ; i < vt ; i ++ ){
      int aa = vc[ i ];
      for( int j = 0 ; j < pre ; j ++ ){
        int bb = vc[ j ];
        if( a[ aa ][ bb ] != -1 )
          ans[ root ] = min( ans[ root ] , dst[ aa ] + dst[ bb ] + a[ aa ][ bb ] );
      }
    }
    pre = vt;
  }
}
void find_ans( int root ){
  for( int i = 1 ; i <= n ; i ++ ){
    v[ i ].clear();
    dst[ i ] = INF16;
    got[ i ] = false;
  }
  dst[ root ] = 0;
  from[ root ] = root;
  for( int i = 0 ; i < n ; i ++ ){
    ll bst = -1 , bstd = INF16;
    for( int j = 1 ; j <= n ; j ++ )
      if( !got[ j ] &&
          dst[ j ] < bstd ){
        bst = j; bstd = dst[ j ];
      }
    if( bst == -1 ) break;
    got[ bst ] = true;
    if( bst != from[ bst ] ){
      v[ bst ].PB( from[ bst ] );
      v[ from[ bst ] ].PB( bst );
    }
    for( int j = 1 ; j <= n ; j ++ )
      if( a[ bst ][ j ] != -1 ){
        if( dst[ bst ] + a[ bst ][ j ] < dst[ j ] ){
          dst[ j ] = dst[ bst ] + a[ bst ][ j ];
          from[ j ] = bst;
        }
      }
  }
  gogogo( root );
}
void solve(){
  for( int i = 1 ; i <= n ; i ++ ){
    find_ans( i );
    if( ans[ i ] == INF16 ) ans[ i ] = -1;
  }
  for( int i = 1 ; i <= n ; i ++ )
    printf( "%lld\n" , ans[ i ] );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
