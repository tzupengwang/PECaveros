// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long double LD;
typedef long long ll;
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<ll,ll> PLL;
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
int __ = 1 , cs;
/*********default*********/
#define K 111
#define N 9
int k , n[ 2 ];
int a[ 2 ][ N ];
void build(){

}
vector<PII> v[ 256 ][ 256 ];
int sum[ 2 ][ 1 << N ];
void init(){
  k = getint();
  for( int i = 0 ; i < 2 ; i ++ ){
    n[ i ] = getint();
    for( int j = 0 ; j < n[ i ] ; j ++ )
      a[ i ][ j ] = getint();
  }
  for( int i = 0 ; i < 2 ; i ++ ){
    for( int j = 1 ; j < ( 1 << n[ i ] ) ; j ++ ){
      int tsum = 0;
      for( int tk = 0 ; tk < n[ i ] ; tk ++ )
        if( ( j >> tk ) & 1 )
          tsum += a[ i ][ tk ];
      sum[ i ][ j ] = tsum;
    }
  }
}
char c[ K ];
void over(){
  puts( "Inconsistent" );
  exit( 0 );
}
// A B
void build_edge( int h1 , int seg1 , int h2 , int seg2 ){
  for( int i = 0 ; i < ( 1 << n[ 0 ] ) ; i ++ )
    for( int j = 0 ; j < ( 1 << n[ 1 ] ) ; j ++ ){
      int sum1 = sum[ 0 ][ i ];
      int sum2 = sum[ 1 ][ i ];
      if( i & ( 1 << seg1 ) ) sum1 -= a[ 0 ][ seg1 ];
      if( j & ( 1 << seg2 ) ) sum2 -= a[ 1 ][ seg2 ];
      if( sum1 + h1 == sum2 + h2 )
        v[ i ][ j ].PB( MP( i | ( 1 << seg1 ) , j | ( 1 << seg2 ) ) );
    }
}
bool got[ 10 ][ 10 ];
int dlt[ 10 ][ 10 ];
void build_edge2( int h1 , int seg1 , int h2 , int seg2 ){
  for( int i = 0 ; i < ( 1 << n[ 0 ] ) ; i ++ ) if( i & ( 1 << seg1 ) )
    for( int j = 0 ; j < ( 1 << n[ 1 ] ) ; j ++ ) if( j & ( 1 << seg2 ) )
      for( int ii = 0 ; ii < n[ 0 ] ; ii ++ ) if( ( ( 1 << ii ) & i ) == 0 )
        for( int jj = 0 ; jj < n[ 1 ] ; jj ++ ) if( ( ( 1 << jj ) & j ) == 0 )
          if( !got[ ii ][ jj ] || sum[ 0 ][ i ] + dlt[ ii ][ jj ] == sum[ 1 ][ j ] )
            v[ i ][ j ].PB( MP( i | ( 1 << ii ) , j | ( 1 << jj ) ) );

}
int dp[ 256 ][ 256 ];
int bi[ 256 ][ 256 ];
int bj[ 256 ][ 256 ];
queue<PII> Q;
bool inq[ 256 ][ 256 ];
bool nice[ 10 ][ 10 ];
int sh1[ 111 ];
int sh2[ 111 ];
int sseg1[ 111 ];
int sseg2[ 111 ];
void find_ans(){
  for( int i = 0 ; i < n[ 0 ] ; i ++ )
    for( int j = 0 ; j < n[ 1 ] ; j ++ )
      if( nice[ i ][ j ] && ( i || j ) )
        v[ 0 ][ 0 ].PB( MP( ( 1 << i ) , ( 1 << j ) ) );
  for( int i = 0 ; i < n[ 0 ] ; i ++ )
    v[ 0 ][ 0 ].PB( MP( ( 1 << i ) , 0 ) );
  for( int i = 0 ; i < n[ 1 ] ; i ++ )
    v[ 0 ][ 0 ].PB( MP( 0 , ( 1 << i ) ) );
  for( int i = 0 ; i < ( 1 << n[ 0 ] ) ; i ++ )
    for( int j = 0 ; j < ( 1 << n[ 1 ] ) ; j ++ ){
      sort( ALL( v[ i ][ j ] ) );
      v[ i ][ j ].resize( unique( ALL( v[ i ][ j ] ) ) - v[ i ][ j ].begin() ); 
    }
  dp[ 0 ][ 0 ] = 1;
  Q.push( MP( 0 , 0 ) );
  while( Q.size() ){
    PII tp = Q.front(); Q.pop();
    int ni = tp.FI;
    int nj = tp.SE;
    for( int i = 0 ; i < (int)v[ ni ][ nj ].size() ; i ++ ){
      int nxti = v[ ni ][ nj ][ i ].FI;
      int nxtj = v[ ni ][ nj ][ i ].SE;
      if( nxti == ni && nxtj == nj ) continue;
      dp[ nxti ][ nxtj ] = min( dp[ nxti ][ nxtj ] + dp[ ni ][ nj ] , 2 );
      bi[ nxti ][ nxtj ] = ni;
      bj[ nxti ][ nxtj ] = nj;
      if( !inq[ nxti ][ nxtj ] ){
        inq[ nxti ][ nxtj ] = true;
        Q.push( MP( nxti , nxtj ) );
      }
    }
  }
  int cans = dp[ ( 1 << n[ 0 ] ) - 1 ][ ( 1 << n[ 1 ] ) - 1 ];
  if( cans == 0 ) over();
  if( cans > 1 ){
    puts( "Ambiguous" );
    exit( 0 );
  }
  vector<int> A , B;
  int ni = ( 1 << n[ 0 ] ) - 1;
  int nj = ( 1 << n[ 1 ] ) - 1;
  while( ni || nj ){
    int nxti = bi[ ni ][ nj ];
    int nxtj = bj[ ni ][ nj ];
    if( ni != nxti ) A.PB( round( log( ni ^ nxti ) ) );
    if( nj != nxtj ) B.PB( round( log( nj ^ nxtj ) ) );
    ni = nxti;
    nj = nxtj;
  }
  reverse( ALL( A ) );
  reverse( ALL( B ) );
  printf( "Alde system: " );
  for( int i = 0 ; i < (int)A.size() ; i ++ )
    printf( "%d%c" , A[ i ] + 1 , " \n"[ i == (int)A.size() - 1 ] );
  printf( "Baran system: " );
  for( int i = 0 ; i < (int)B.size() ; i ++ )
    printf( "%d%c" , B[ i ] + 1 , " \n"[ i == (int)B.size() - 1 ] );
}
void solve(){
  int _ = getint();
  for( int i = 0 ; i < n[ 0 ] ; i ++ )
    for( int j = 0 ; j < n[ 1 ] ; j ++ )
      nice[ i ][ j ] = true;
  for( int o = 0 ; o < _ ; o ++ ){
    scanf( "%s" , c );
    int h1 , m1 , h2 , m2;
    int ty1 , seg1 , ty2 , seg2;
    h1 = ( c[ 0 ] - '0' ) * 10 + ( c[ 1 ] - '0' );
    m1 = ( c[ 3 ] - '0' ) * 10 + ( c[ 4 ] - '0' );
    ty1 = c[ 5 ] - 'A';
    seg1 = c[ 6 ] - 'A';
    h2 = ( c[ 8 ] - '0' ) * 10 + ( c[ 9 ] - '0' );
    m2 = ( c[ 11 ] - '0' ) * 10 + ( c[ 12 ] - '0' );
    ty2 = c[ 13 ] - 'A';
    seg2 = c[ 14 ] - 'A';
    if( ty1 == ty2 && ( seg1 != seg2 || h1 != h2 ) ) over();
    if( m1 != m2 ) over();
    if( ty1 != ty2 ){
      if( ty1 == 1 ){
        swap( h1 , h2 );
        swap( seg1 , seg2 );
      }
      if( got[ ty1 ][ ty2 ] && h1 - h2 != dlt[ ty1 ][ ty2 ] ) over();
      got[ ty1 ][ ty2 ] = true;
      dlt[ ty1 ][ ty2 ] = h1 - h2;
      sh1[ o ] = h1;
      sh2[ o ] = h2;
      sseg1[ o ] = seg1;
      sseg2[ o ] = seg2;
      if( h1 != h2 ) nice[ seg1 ][ seg2 ] = false;
      build_edge( h1 , seg1 , h2 , seg2 );
    }
  }
  for( int o = 0 ; o < _ ; o ++ )
    build_edge2( sh1[ o ] , sseg1[ o ] , sh2[ o ] , sseg2[ o ] );
  find_ans();
}
int main(){
  freopen( "ampm.in" , "r" , stdin );
  freopen( "ampm.out" , "w" , stdout );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
