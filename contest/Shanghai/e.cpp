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
ll c[ N ][ N ] , p[ N + N ] , ten[ N ];
vector<ll> vv;
int m;
void build(){
  ten[ 0 ] = 1ll;
  for( int i = 1 ; i < N ; i ++ )
    ten[ i ] = mul( ten[ i - 1 ] , 10 );
  for( int i = 0 ; i < N ; i ++ )
    c[ i ][ i ] = c[ i ][ 0 ] = 1ll;
  for( int i = 2 ; i < N ; i ++ )
    for( int j = 1 ; j < i ; j ++ )
      c[ i ][ j ] = add( c[ i - 1 ][ j - 1 ] ,
                         c[ i - 1 ][ j ] );
  for( int i = 0 ; i < 10 ; i ++ )
    for( int j = 0 ; j < 10 ; j ++ )
      vv.PB( i * j );
  sort( ALL( vv ) );
  vv.resize( unique( ALL( vv ) ) - vv.begin() );
  for( size_t i = 0 ; i < vv.size() ; i ++ )
    p[ vv[ i ] ] = i;
  m = (int)vv.size();
}
int K , l , s;
char n[ N ];
ll dp[ 2 ][ N ][ N ][ N ][ N ];
ll ps[ 2 ][ 3 ][ N ][ N ][ N ][ N ];
void init(){
  K = getint();
  scanf( "%s" , n );
  l = strlen( n );
  for( int u = 0 ; u < l ; u ++ )
    for( int i = 0 ; i < l ; i ++ )
      for( int j = 0 ; j < l ; j ++ )
        for( int k = 0 ; k < m ; k ++ )
          ps[ 0 ][ 0 ][ u ][ i ][ j ][ k ] =
          ps[ 0 ][ 1 ][ u ][ i ][ j ][ k ] =
          ps[ 0 ][ 2 ][ u ][ i ][ j ][ k ] =
          dp[ 0 ][ u ][ i ][ j ][ k ] = 0;
  for( int i = 0 ; i < l ; i ++ )
    if( n[ i ] == '*' )
      s = i;
  for( int i = 0 ; i < l ; i ++ ) if( i != s )
    for( int j = i + 1 ; j < l ; j ++ ) if( j != s )
      dp[ 0 ][ s ][ i ][ j ][ p[ ( n[ i ] - '0' ) *
                                 ( n[ j ] - '0' ) ] ] ++;
  for( int u = 0 ; u < l ; u ++ )
    for( int i = 0 ; i < l ; i ++ )
      for( int j = 0 ; j < l ; j ++ )
        for( int k = 0 ; k < m ; k ++ ){
          if( u ){
            ps[ 0 ][ u ][ i ][ j ][ k ] = add( ps[ 0 ][ u - 1 ][ i ][ j ][ k ],
                                               dp[ 0 ][ u ][ i ][ j ][ k ] );
          }else
            ps[ 0 ][ u ][ i ][ j ][ k ] = dp[ 0 ][ u ][ i ][ j ][ k ];
          if( i ){
            ps[ 1 ][ u ][ i ][ j ][ k ] = add( ps[ 1 ][ u ][ i - 1 ][ j ][ k ],
                                               dp[ 0 ][ u ][ i ][ j ][ k ] );
          }else
            ps[ 1 ][ u ][ i ][ j ][ k ] = dp[ 0 ][ u ][ i ][ j ][ k ];
          if( j ){
            ps[ 2 ][ u ][ i ][ j ][ k ] = add( ps[ 2 ][ u ][ i ][ j - 1 ][ k ],
                                               dp[ 0 ][ u ][ i ][ j ][ k ] );
          }else
            ps[ 2 ][ u ][ i ][ j ][ k ] = dp[ 0 ][ u ][ i ][ j ][ k ];
        }
}
void solve(){
  for( int nn = 1 ; nn <= K ; nn ++ ){
    int now = nn & 1;
    int pre = 1 - now;
    for( int u = 0 ; u < l ; u ++ )
      for( int i = 0 ; i < l ; i ++ )
        for( int j = 0 ; j < l ; j ++ )
          for( int k = 0 ; k < m ; k ++ )
            ps[ now ][ 0 ][ u ][ i ][ j ][ k ] =
            ps[ now ][ 1 ][ u ][ i ][ j ][ k ] =
            ps[ now ][ 2 ][ u ][ i ][ j ][ k ] =
            dp[ now ][ u ][ i ][ j ][ k ] = 0;
    for( int u = 0 ; u < l ; u ++ )
      for( int i = 0 ; i < l ; i ++ )
        for( int j = 0 ; j < l ; j ++ )
          for( int k = 0 ; k < m ; k ++ )
            if( dp[ pre ][ u ][ i ][ j ][ k ] ){
              dp[ now ][ u ][ i ][ j ][ k ] = add( dp[ now ][ u ][ i ][ j ][ k ] , 
                                              mul( dp[ pre ][ u ][ i ][ j ][ k ] , c[ l - 3 ][ 2 ] ) );
              for( int y = 0 ; y < l ; y ++ )
                if( y != u && y != i && y != j ){
                  dp[ now ][ y ][ i ][ j ][ k ] = add( dp[ now ][ y ][ i ][ j ][ k ],
                                                       dp[ pre ][ u ][ i ][ j ][ k ] );
                  dp[ now ][ u ][ y ][ j ][ k ] = add( dp[ now ][ u ][ y ][ j ][ k ],
                                                       dp[ pre ][ u ][ i ][ j ][ k ] );
                  dp[ now ][ u ][ i ][ y ][ k ] = add( dp[ now ][ u ][ i ][ y ][ k ],
                                                       dp[ pre ][ u ][ i ][ j ][ k ] );
                }
              dp[ now ][ i ][ u ][ j ][ k ] = add( dp[ now ][ i ][ u ][ j ][ k ],
                                                   dp[ pre ][ u ][ i ][ j ][ k ] );
              dp[ now ][ j ][ i ][ u ][ k ] = add( dp[ now ][ j ][ i ][ u ][ k ],
                                                   dp[ pre ][ u ][ i ][ j ][ k ] );
              dp[ now ][ u ][ j ][ i ][ k ] = add( dp[ now ][ u ][ j ][ i ][ k ],
                                                   dp[ pre ][ u ][ i ][ j ][ k ] );
            }
    for( int u = 0 ; u < l ; u ++ )
      for( int i = 0 ; i < l ; i ++ )
        for( int j = 0 ; j < l ; j ++ )
          for( int k = 0 ; k < m ; k ++ ){
            if( u ){
              ps[ now ][ 0 ][ u ][ i ][ j ][ k ] = add( ps[ now ][ 0 ][ u - 1 ][ i ][ j ][ k ],
                                                        dp[ now ][ u ][ i ][ j ][ k ] );
            }else
              ps[ now ][ 0 ][ u ][ i ][ j ][ k ] = dp[ now ][ 0 ][ u ][ i ][ j ][ k ];
            if( i ){
              ps[ now ][ 1 ][ u ][ i ][ j ][ k ] = add( ps[ now ][ 1 ][ u ][ i - 1 ][ j ][ k ],
                                                 dp[ now ][ u ][ i ][ j ][ k ] );
            }else
              ps[ now ][ 1 ][ u ][ i ][ j ][ k ] = dp[ now ][ u ][ i ][ j ][ k ];
            if( j ){
              ps[ now ][ 2 ][ u ][ i ][ j ][ k ] = add( ps[ now ][ 2 ][ u ][ i ][ j - 1 ][ k ],
                                                 dp[ now ][ u ][ i ][ j ][ k ] );
            }else
              ps[ now ][ 2 ][ u ][ i ][ j ][ k ] = dp[ now ][ u ][ i ][ j ][ k ];
          }
  }
  ll ans = 0;
  int now = K & 1;
  for( int u = 0 ; u < l ; u ++ )
    for( int i = 0 ; i < l ; i ++ )
      for( int j = 0 ; j < l ; j ++ )
        for( int k = 0 ; k < m ; k ++ )
          if( ( i > u && j < u ) ||
              ( i < u && j > u ) ){
            if( dp[ now ][ u ][ i ][ j ][ k ] ){
              ans = add( ans , mul( dp[ now ][ u ][ i ][ j ][ k ] ,
                                    mul( vv[ k ] , ten[ l - i - 1 + u - j - 1 ] ) ) );
            }
          }
  printf( "Case #%d: %lld\n" , ++ _cs , ans );
}
int main(){
  build();
  __ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
