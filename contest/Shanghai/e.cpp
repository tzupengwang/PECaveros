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
#define N 55
ll ten[ N ] , C[ N ][ N ];
void build(){
  ten[ 0 ] = 1ll;
  for( int i = 1 ; i < N ; i ++ )
    ten[ i ] = mul( ten[ i - 1 ] , 10ll );
  for( int i = 0 ; i < N ; i ++ )
    C[ i ][ 0 ] = C[ i ][ i ] = 1;
  for( int i = 2 ; i < N ; i ++ )
    for( int j = 1 ; j < i ; j ++ )
      C[ i ][ j ] = add( C[ i - 1 ][ j ] ,
                         C[ i - 1 ][ j - 1 ] );
}
int K , s , l;
char c[ N ];
ll dp[ 2 ][ N ][ N ][ N ];
ll ps[ 2 ][ 3 ][ N ][ N ][ N ];
void init(){
  K = getint();
  scanf( "%s" , c );
  l = strlen( c );
  for( int i = 0 ; i < l ; i ++ )
    if( c[ i ] == '*' )
      s = i;
  for( int i = 0 ; i < l ; i ++ )
    for( int j = 0 ; j < l ; j ++ )
      for( int k = 0 ; k < l ; k ++ )
        ps[ 0 ][ 0 ][ i ][ j ][ k ] = 
        ps[ 0 ][ 1 ][ i ][ j ][ k ] = 
        ps[ 0 ][ 2 ][ i ][ j ][ k ] = 
        dp[ 0 ][ i ][ j ][ k ] = 0;
  for( int i = 0 ; i < l ; i ++ ) if( s != i )
    for( int j = i + 1 ; j < l ; j ++ ) if( s != j )
      dp[ 0 ][ i ][ j ][ s ] = add( dp[ 0 ][ i ][ j ][ s ] ,
                                    ( c[ i ] - '0' ) * ( c[ j ] - '0' ) );
  for( int i = 0 ; i < l ; i ++ )
    for( int j = 0 ; j < l ; j ++ )
      for( int k = 0 ; k < l ; k ++ ){
        if( i == 0 ) ps[ 0 ][ 0 ][ i ][ j ][ k ] = dp[ 0 ][ i ][ j ][ k ];
        else ps[ 0 ][ 0 ][ i ][ j ][ k ] = add( ps[ 0 ][ 0 ][ i - 1 ][ j ][ k ],
                                                dp[ 0 ][ i ][ j ][ k ] );
        if( j == 0 ) ps[ 0 ][ 1 ][ i ][ j ][ k ] = dp[ 0 ][ i ][ j ][ k ];
        else ps[ 0 ][ 1 ][ i ][ j ][ k ] = add( ps[ 0 ][ 1 ][ i ][ j - 1 ][ k ],
                                                dp[ 0 ][ i ][ j ][ k ] );
        if( k == 0 ) ps[ 0 ][ 2 ][ i ][ j ][ k ] = dp[ 0 ][ i ][ j ][ k ];
        else ps[ 0 ][ 2 ][ i ][ j ][ k ] = add( ps[ 0 ][ 2 ][ i ][ j ][ k - 1 ],
                                                dp[ 0 ][ i ][ j ][ k ] );
      }
}
void solve(){
  for( int ii = 1 ; ii <= K ; ii ++ ){
    int now = ii & 1;
    int pre = 1 - now;
    for( int i = 0 ; i < l ; i ++ )
      for( int j = 0 ; j < l ; j ++ )
        for( int k = 0 ; k < l ; k ++ )
          ps[ now ][ 0 ][ i ][ j ][ k ] =
          ps[ now ][ 1 ][ i ][ j ][ k ] =
          ps[ now ][ 2 ][ i ][ j ][ k ] =
          dp[ now ][ i ][ j ][ k ] = 0;
    for( int i = 0 ; i < l ; i ++ )
      for( int j = 0 ; j < l ; j ++ )
        for( int k = 0 ; k < l ; k ++ ){
          if( i == j || j == k || i == k ) continue;
          dp[ now ][ i ][ j ][ k ] = mul( dp[ pre ][ i ][ j ][ k ] , C[ l - 3 ][ 2 ] );
          ll dlt = sub( ps[ pre ][ 0 ][ l - 1 ][ j ][ k ] , dp[ pre ][ i ][ j ][ k ] );
          dp[ now ][ i ][ j ][ k ] = add( dp[ now ][ i ][ j ][ k ] , dlt );
             dlt = sub( ps[ pre ][ 1 ][ i ][ l - 1 ][ k ] , dp[ pre ][ i ][ j ][ k ] );
          dp[ now ][ i ][ j ][ k ] = add( dp[ now ][ i ][ j ][ k ] , dlt );
             dlt = sub( ps[ pre ][ 2 ][ i ][ j ][ l - 1 ] , dp[ pre ][ i ][ j ][ k ] );
          dp[ now ][ i ][ j ][ k ] = add( dp[ now ][ i ][ j ][ k ] , dlt );
          dp[ now ][ i ][ j ][ k ] = add( dp[ now ][ i ][ j ][ k ],
                                          dp[ pre ][ j ][ i ][ k ] );
          dp[ now ][ i ][ j ][ k ] = add( dp[ now ][ i ][ j ][ k ],
                                          dp[ pre ][ k ][ j ][ i ] );
          dp[ now ][ i ][ j ][ k ] = add( dp[ now ][ i ][ j ][ k ],
                                          dp[ pre ][ i ][ k ][ j ] );
        }
    for( int i = 0 ; i < l ; i ++ )
      for( int j = 0 ; j < l ; j ++ )
        for( int k = 0 ; k < l ; k ++ ){
          if( i == 0 ) ps[ now ][ 0 ][ i ][ j ][ k ] = dp[ now ][ i ][ j ][ k ];
          else ps[ now ][ 0 ][ i ][ j ][ k ] = add( ps[ now ][ 0 ][ i - 1 ][ j ][ k ],
                                                  dp[ now ][ i ][ j ][ k ] );
          if( j == 0 ) ps[ now ][ 1 ][ i ][ j ][ k ] = dp[ now ][ i ][ j ][ k ];
          else ps[ now ][ 1 ][ i ][ j ][ k ] = add( ps[ now ][ 1 ][ i ][ j - 1 ][ k ],
                                                  dp[ now ][ i ][ j ][ k ] );
          if( k == 0 ) ps[ now ][ 2 ][ i ][ j ][ k ] = dp[ now ][ i ][ j ][ k ];
          else ps[ now ][ 2 ][ i ][ j ][ k ] = add( ps[ now ][ 2 ][ i ][ j ][ k - 1 ],
                                                  dp[ now ][ i ][ j ][ k ] );
        }
  }
  int lst = K & 1;
  ll ans = 0ll;
  for( int i = 0 ; i < l ; i ++ )
    for( int j = 0 ; j < l ; j ++ )
      for( int k = 0 ; k < l ; k ++ )
        if( dp[ lst ][ i ][ j ][ k ] ){
          if( ( i < k && k < j ) ||
              ( i > k && k > j ) )
            ans = add( ans , mul( dp[ lst ][ i ][ j ][ k ] , ten[ l - i - 1 + k - j - 1 ] ) );
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
