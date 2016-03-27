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
#define N 52
int m , n , r;
void build(){

}
vector< vector<int> > vv;
vector<int> ccc;
vector<int> vmx;
vector<int> dp[ N ];
vector<int> tv;
void DFS( int now , int mx , int cnt ){
  if( now + 2 >= m && mx <= 1 ) return;
  if( now == m ){
    bool flag = false;
    for( size_t i = 0 ; i < tv.size() && !flag ; i ++ )
      for( size_t j = i + 1 ; j < tv.size() && !flag ; j ++ )
        for( size_t k = j + 1 ; k < tv.size() && !flag ; k ++ )
          for( size_t l = k + 1 ; l < tv.size() && !flag ; l ++ )
            if( tv[ i ] == tv[ k ] && tv[ j ] == tv[ l ] && tv[ i ] != tv[ j ] )
              flag = true;
    if( flag ){
      vv.PB( tv );
      vmx.PB( mx );
      ccc.PB( cnt );
      // for( size_t i = 0 ; i < tv.size() ; i ++ )
        // printf( "%d " , tv[ i ] );
      // printf( " : %d %d\n" , mx , cnt );
    }
    return;
  }
  for( int i = 1 ; i <= mx + 1 ; i ++ ){
    tv[ now ] = i;
    if( i <= mx )
      DFS( now + 1 , max( mx , i ) , cnt );
    else
      DFS( now + 1 , max( mx , i ) , mul( cnt , r - mx ) );
  }
}
void pre_build(){
  tv.resize( m );
  DFS( 0 , 0 , 1 );
}
vector< vector<int> > nxt;
void init(){
  m = getint();
  n = getint();
  r = getint();
  pre_build();
}
int got[ N ];
void solve(){
  int k = (int)vv.size();
  nxt.resize( k );
  for( int i = 0 ; i < k ; i ++ ){
    nxt[ i ].resize( vmx[ i ] + 2 );
    for( int j = 1 ; j <= vmx[ i ] + 1 ; j ++ ){
      for( size_t u = 1 ; u < vv[ i ].size() ; u ++ )
        got[ vv[ i ][ u ] ] = 0;
      got[ j ] = 0;
      int tgot = 0;
      for( size_t u = 1 ; u < vv[ i ].size() ; u ++ )
        if( got[ vv[ i ][ u ] ] == 0 )
          got[ vv[ i ][ u ] ] = ++ tgot;
      if( got[ j ] == 0 )
        got[ j ] = ++ tgot;
      vector<int> ttt;
      for( size_t u = 1 ; u < vv[ i ].size() ; u ++ )
        ttt.PB( got[ vv[ i ][ u ] ] );
      ttt.PB( got[ j ] );
      if( lower_bound( ALL( vv ) , ttt ) == upper_bound( ALL( vv ) , ttt ) )
        nxt[ i ][ j ] = -1;
      else nxt[ i ][ j ] = lower_bound( ALL( vv ) , ttt ) - vv.begin();
    }
  }
  //
  for( int i = m ; i <= n ; i ++ )
    dp[ i ].resize( k );
  for( int i = 0 ; i < k ; i ++ )
    dp[ m ][ i ] = ccc[ i ];
  for( int i = m ; i < n ; i ++ )
    for( int j = 0 ; j < k ; j ++ ){
      if( dp[ i ][ j ] == 0 ) continue;
      for( int l = 1 ; l <= vmx[ j ] ; l ++ )
        if( nxt[ j ][ l ] != -1 )
          dp[ i + 1 ][ nxt[ j ][ l ] ] = add( dp[ i + 1 ][ nxt[ j ][ l ] ] , dp[ i ][ j ] );
      if( nxt[ j ][ vmx[ j ] + 1 ] != -1 )
        dp[ i + 1 ][ nxt[ j ][ vmx[ j ] + 1 ] ] = add( dp[ i + 1 ][ nxt[ j ][ vmx[ j ] + 1 ] ] ,
                                                       mul( dp[ i ][ j ] , r - vmx[ j ] ) );
    }
  int ans = 0;
  for( int i = 0 ; i < k ; i ++ )
    ans = add( ans , dp[ n ][ i ] );
  printf( "%d\n" , ans );
}
int main(){
  freopen( "linked.in" , "r" , stdin );
  freopen( "linked.out" , "w" , stdout );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
