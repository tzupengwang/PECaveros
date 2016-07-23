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
#define K 101
#define N 20202
map< int , int > M;
int n , l , len[ K ];
char c[ K ][ N ];
vector< int > v[ K ];
void build(){

}
int sc[ K ];
void init(){
  n = getint();
  for( int i = 0 ; i < n ; i ++ ){
    gets( c[ i ] );
    len[ i ] = strlen( c[ i ] );
    l = max( l , len[ i ] );
  }
  while( l % 4 ) l ++;
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < l ; j ++ ){
      int tcnt = 0;
      for( int k = j ; k < j + 4 ; k ++ )
        if( k < len[ i ] && isalpha( c[ i ][ k ] ) )
          tcnt ++;
      sc[ i ] += tcnt * tcnt;
        // if( k >= len[ i ] || c[ i ][ k ] == ' ' ) vv.push_back( 0 );
        // else vv.push_back( (int)c[ i ][ k ] );
      // for( int k = 0 ; k < 4 ; k ++ )
        // hsh = ( hsh << 7 ) + vv[ k ];
      // // if( hsh == 0 ) continue;
      // M[ hsh ] ++;
      // v[ i ].push_back( hsh );
    }
}
bool ans[ N ];
void solve(){
  vector< PLL > vv;
  for( int i = 0 ; i < n ; i ++ ){
    vv.push_back( { sc[ i ] , i } );
    // sort( ALL( v[ i ] ) );
    // v[ i ].resize( unique( ALL( v[ i ] ) ) - v[ i ].begin() );
    // LL tcnt = 0;
    // for( int hsh : v[ i ] )
      // tcnt += M[ hsh ];
    // vv.push_back( { tcnt , i } );
  }
  sort( ALL( vv ) );
  for( int i = 0 ; i < n / 2 ; i ++ )
    ans[ vv[ i ].SE ] = true;
  for( int i = 0 ; i < n ; i ++ )
    puts( ans[ i ] ? "random" : "block" );
}
int main(){
  freopen( "detect.in" , "r" , stdin );
  freopen( "detect.out" , "w" , stdout );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
