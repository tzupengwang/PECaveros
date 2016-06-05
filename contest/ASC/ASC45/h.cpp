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
#define N 514
inline PLL operator-( const PLL& p1 , const PLL& p2 ){
  return { p1.X - p2.X , p1.Y - p2.Y };
}
inline LL operator^( const PLL& p1 , const PLL& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
int n;
PLL p[ N ];
void build(){
  
}
int dp[ N ][ N ];
vector<int> ans[ N ][ N ];
void init(){
  for( int i = 1 ; i <= n ; i ++ ){
    p[ i ].X = getint();
    p[ i ].Y = getint();
  }
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= n ; j ++ )
      dp[ i ][ j ] = 0;
}
void DP( int l , int r ){
  if( dp[ l ][ r ] ) return;
  if( l == r ){
    dp[ l ][ r ] = 1;
    ans[ l ][ r ].clear();
    ans[ l ][ r ].PB( l );
    return;
  }
  ans[ l ][ r ].clear();
  int nxt = l + 1 , pre = 0;
  for( int i = l + 2 ; i <= r ; i ++ )
    if( ( ( p[ i ] - p[ l ] ) ^ ( p[ nxt ] - p[ l ] ) ) <= 0 ){
      if( pre ){
        DP( pre , i - 1 );
        dp[ l ][ r ] += dp[ pre ][ i - 1 ];
        for( auto x : ans[ pre ][ i - 1 ] )
          ans[ l ][ r ].PB( x );
      }
      pre = 0; nxt = i;
    }else if( !pre ) pre = i;
  if( pre ){
    DP( pre , r );
    dp[ l ][ r ] += dp[ pre ][ r ];
    for( auto i : ans[ pre ][ r ] )
      ans[ l ][ r ].PB( i );
  }
  dp[ l ][ r ] ++;
  ans[ l ][ r ].PB( l );
  DP( l + 1 , r );
  if( dp[ l + 1 ][ r ] > dp[ l ][ r ] ){
    dp[ l ][ r ] = dp[ l + 1 ][ r ];
    ans[ l ][ r ] = ans[ l + 1 ][ r ];
  }
}
void solve(){
  DP( 2 , n );
  printf( "%d\n" , dp[ 2 ][ n ] );
  sort( ALL( ans[ 2 ][ n ] ) );
  for( size_t i = 0 ; i < ans[ 2 ][ n ].size() ; i ++ )
    printf( "%d%c" , ans[ 2 ][ n ][ i ] , " \n"[ i + 1 == ans[ 2 ][ n ].size() ] );
}
int main(){
  freopen( "hide.in" , "r" , stdin );
  freopen( "hide.out" , "w" , stdout );
  build();
  //__ = getint();
  // while( __ -- ){
  while( scanf( "%d" , &n ) == 1 ){
    if( n == 0 ) break;
    init();
    solve();
  }
}
