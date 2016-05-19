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
#define N 111
#define M 21
int n;
char c[ N ][ 8 ][ 30 ];
bool l[ 8 ][ 30 ];
bool d[ 8 ][ 30 ];
bool w[ 8 ][ 30 ];
int inn[]={0,0,1,2,1,2,3,3,4,5,4,5,6,6};
int inm[]={1,2,0,0,3,3,1,2,0,0,3,3,1,2};
vector<int> v[ 11 ];
#define con 10
// int sft[]={};
void build(){
  v[ 0 ].PB( 0 );
  v[ 0 ].PB( 1 );
  v[ 0 ].PB( 2 );
  v[ 0 ].PB( 4 );
  v[ 0 ].PB( 5 );
  v[ 0 ].PB( 6 );

  v[ 1 ].PB( 2 );
  v[ 1 ].PB( 5 );

  v[ 2 ].PB( 0 );
  v[ 2 ].PB( 2 );
  v[ 2 ].PB( 3 );
  v[ 2 ].PB( 4 );
  v[ 2 ].PB( 6 );
  
  v[ 3 ].PB( 0 );
  v[ 3 ].PB( 2 );
  v[ 3 ].PB( 3 );
  v[ 3 ].PB( 5 );
  v[ 3 ].PB( 6 );

  v[ 4 ].PB( 1 );
  v[ 4 ].PB( 2 );
  v[ 4 ].PB( 3 );
  v[ 4 ].PB( 5 );

  v[ 5 ].PB( 0 );
  v[ 5 ].PB( 1 );
  v[ 5 ].PB( 3 );
  v[ 5 ].PB( 5 );
  v[ 5 ].PB( 6 );

  v[ 6 ].PB( 0 );
  v[ 6 ].PB( 1 );
  v[ 6 ].PB( 3 );
  v[ 6 ].PB( 5 );
  v[ 6 ].PB( 4 );
  v[ 6 ].PB( 6 );

  v[ 7 ].PB( 0 );
  v[ 7 ].PB( 2 );
  v[ 7 ].PB( 5 );

  v[ 8 ].PB( 0 );
  v[ 8 ].PB( 1 );
  v[ 8 ].PB( 2 );
  v[ 8 ].PB( 3 );
  v[ 8 ].PB( 4 );
  v[ 8 ].PB( 5 );
  v[ 8 ].PB( 6 );

  v[ 9 ].PB( 0 );
  v[ 9 ].PB( 1 );
  v[ 9 ].PB( 2 );
  v[ 9 ].PB( 3 );
  v[ 9 ].PB( 5 );
  v[ 9 ].PB( 6 );
}
void init(){
  n = getint();
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < 7 ; j ++ ){
      scanf( "%s" , c[ i ][ j ] );
      for( int k = 0 ; k < M ; k ++ )
        if( c[ i ][ j ][ k ] == 'X' )
          l[ j ][ k ] = true;
        else
          d[ j ][ k ] = true;
    }
  for( int i = 0 ; i < 7 ; i ++ )
    for( int j = 0 ; j < M ; j ++ )
      if( l[ i ][ j ] && d[ i ][ j ] ){
        // printf( "%d %d\n" , i , j );
        w[ i ][ j ] = true;
      }
}
bool ndot[ 8 ][ 30 ];
char cc[ 8 ][ 30 ];
inline void draw( int hr , int mn ){
  int up = hr / 10;
  if( up == 0 ) up = con;
  for( int i = 0 ; i < 7 ; i ++ ){
    for( int j = 0 ; j < M ; j ++ )
      cc[ i ][ j ] = '.';
    cc[ i ][ M ] = '\0';
  }
  for( size_t i = 0 ; i < v[ up ].size() ; i ++ ){
    cc[ inn[ v[ up ][ i ] * 2 + 0 ] ][ inm[ v[ up ][ i ] * 2 + 0 ] ] = 'X';
    cc[ inn[ v[ up ][ i ] * 2 + 1 ] ][ inm[ v[ up ][ i ] * 2 + 1 ] ] = 'X';
  }
  int xn = hr % 10;
  for( size_t i = 0 ; i < v[ xn ].size() ; i ++ ){
    cc[ inn[ v[ xn ][ i ] * 2 + 0 ] ][ inm[ v[ xn ][ i ] * 2 + 0 ] + 5 ] = 'X';
    cc[ inn[ v[ xn ][ i ] * 2 + 1 ] ][ inm[ v[ xn ][ i ] * 2 + 1 ] + 5 ] = 'X';
  }
  xn = mn / 10;
  for( size_t i = 0 ; i < v[ xn ].size() ; i ++ ){
    cc[ inn[ v[ xn ][ i ] * 2 + 0 ] ][ inm[ v[ xn ][ i ] * 2 + 0 ] + 12 ] = 'X';
    cc[ inn[ v[ xn ][ i ] * 2 + 1 ] ][ inm[ v[ xn ][ i ] * 2 + 1 ] + 12 ] = 'X';
  }
  xn = mn % 10;
  for( size_t i = 0 ; i < v[ xn ].size() ; i ++ ){
    cc[ inn[ v[ xn ][ i ] * 2 + 0 ] ][ inm[ v[ xn ][ i ] * 2 + 0 ] + 17 ] = 'X';
    cc[ inn[ v[ xn ][ i ] * 2 + 1 ] ][ inm[ v[ xn ][ i ] * 2 + 1 ] + 17 ] = 'X';
  }
  for( size_t j = 0 ; j < v[ 8 ].size() ; j ++ ){
    int yy[]={0,5,12,17};
    for( int k = 0 ; k < 4 ; k ++ ){
      ndot[ inn[ v[ 8 ][ j ] * 2 + 0 ] ][ inm[ v[ 8 ][ j ] * 2 + 0 ] + yy[ k ] ] = true;
      ndot[ inn[ v[ 8 ][ j ] * 2 + 1 ] ][ inm[ v[ 8 ][ j ] * 2 + 1 ] + yy[ k ] ] = true;
    }
  }
  cc[ 2 ][ 10 ] = cc[ 4 ][ 10 ] = 'X';
  ndot[ 2 ][ 10 ] = ndot[ 4 ][ 10 ] = true;
}
inline bool okay( int hr , int mn ){
  int nhr = hr , nmn = mn;
  for( int i = 0 ; i < n ; i ++ ){
    draw( nhr , nmn );
    // printf( "%d %d\n" , nhr , nmn );
    // for( int j = 0 ; j < 7 ; j ++ )
      // puts( cc[ j ] );

    for( int j = 0 ; j < 7 ; j ++ )
      for( int k = 0 ; k < 21 ; k ++ ){
        if( !ndot[ j ][ k ] ) continue;
        if( w[ j ][ k ] && cc[ j ][ k ] !=
                           c[ i ][ j ][ k ] ){
          // printf( "%d %d\n" , j , k );
          return false;
        }
      }
    nmn ++;
    if( nmn == 60 ) nmn = 0 , nhr ++;
    if( nhr == 24 ) nhr = 0;
  }
  return true;
}
bool tag[ 8 ][ 30 ];
bool tag2[ 8 ][ 30 ];
inline void test( int hr , int mn ){
  // printf( "%d %d\n" , hr , mn );
  for( int i = 0 ; i < 7 ; i ++ )
    for( int j = 0 ; j < M ; j ++ )
      tag2[ i ][ j ] = true;
  int nhr = hr , nmn = mn;
  for( int i = 0 ; i < n ; i ++ ){
    draw( nhr , nmn );
    for( int j = 0 ; j < 7 ; j ++ )
      for( int k = 0 ; k < 21 ; k ++ ){
        if( !ndot[ j ][ k ] ) continue;
        if( !w[ j ][ k ] && cc[ j ][ k ] !=
                           c[ i ][ j ][ k ] )
          tag2[ j ][ k ] = false;
      }
    nmn ++;
    if( nmn == 60 ) nmn = 0 , nhr ++;
    if( nhr == 24 ) nhr = 0;
  }
  for( int i = 0 ; i < 7 ; i ++ )
    for( int j = 0 ; j < 21 ; j ++ )
      tag[ i ][ j ] = tag[ i ][ j ] || tag2[ i ][ j ];
}
void solve(){
  vector<PII> good;
  for( int hr = 0 ; hr < 24 ; hr ++ )
    for( int mn = 0 ; mn < 60 ; mn ++ )
      if( okay( hr , mn ) )
        good.PB( MP( hr , mn ) );
  if( good.empty() ) puts( "impossible" );
  else{
    for( size_t i = 0 ; i < good.size() ; i ++ )
      test( good[ i ].FI , good[ i ].SE );
    for( int i = 0 ; i < 7 ; i ++ ){
      for( int j = 0 ; j < 21 ; j ++ ){
        if( !ndot[ i ][ j ] ) putchar( '.' );
        else if( w[ i ][ j ] ) putchar( 'W' );
        else if( tag[ i ][ j ] ) putchar( '?' );
        else if( d[ i ][ j ] ) putchar( '0' );
        else  putchar( '1' );
      }
      puts( "" );
    }
  }
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
