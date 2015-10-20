// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long long ll;
typedef pair<int,int> PII;
#define mod9 1000000009ll
#define mod7 1000000007ll
#define INF  1023456789ll
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
bool equal( D _x ,  D _y ){
  return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , cs;
/*********default*********/
#define N 20010
#define M 20
int n , p , m , g , t;
int scst;
vector<int> pset;
vector<PII> v[ N ];
void build(){

}
void init(){
  n = getint();
  p = getint();
  m = getint();
  g = getint();
  t = getint();
  for( int i = 0 ; i < p ; i ++ ){
    int pi = getint();
    pset.PB( pi );
    scst += getint();
  }
  sort( ALL( pset ) );
  if( pset[ 0 ] != 0 )
    pset.PB( 0 );
  sort( ALL( pset ) );
  while( m -- ){
    int tu = getint();
    int tv = getint();
    int tk = getint();
    v[ tu ].PB( MP( tv , tk ) );
    v[ tv ].PB( MP( tu , tk ) );
  }
}
int dst[ N ];
int dp[ M ][ M ];
priority_queue< PII , vector<PII> , greater<PII> > heap;
void SP( int idx , int source ){
  static bool got[ N ];
  for( int i = 0 ; i < n ; i ++ )
    got[ i ] = false , dst[ i ] = g + 1;
  heap.push( MP( 0 , source ) );
  while( heap.size() ){
    PII tp = heap.top(); heap.pop();
    int tdst = tp.FI;
    int tn = tp.SE;
    if( got[ tn ] ) continue;
    dst[ tn ] = tdst;
    got[ tn ] = true;
    for( int i = 0 ; i < (int)v[ tn ].size() ; i ++ )
      if( !got[ v[ tn ][ i ].FI ] )
        heap.push( MP( tdst + v[ tn ][ i ].SE , v[ tn ][ i ].FI ) );
  }
  for( int i = 0 ; i < p ; i ++ )
    dp[ idx ][ i ] = dst[ pset[ i ] ];
}
int dp2[ 1 << M ][ M ][ 2 ];
bool got[ 1 << M ][ M ][ 2 ];
void solve(){
  p = (int)pset.size();
  for( int i = 0 ; i < p ; i ++ )
    SP( i , pset[ i ] );
  got[ 0 ][ 0 ][ 0 ] = true;
  for( int i = 0 ; i < ( 1 << p ) ; i ++ )
    for( int j = 0 ; j < p ; j ++ )
      for( int k = 0 ; k < 2 ; k ++ ) if( got[ i ][ j ][ k ] )
        for( int nxt = 0 ; nxt < p ; nxt ++ )
          if( ( ( i >> nxt ) & 1 ) == 0 ){
            int nxtst = i ^ ( 1 << nxt );
            int cst = dp2[ i ][ j ][ k ] + dp[ j ][ nxt ];
            int nxtk = max( 0 , k );
            if( !got[ nxtst ][ nxt ][ nxtk ] ||
                cst < dp2[ nxtst ][ nxt ][ nxtk ] ){
                dp2[ nxtst ][ nxt ][ nxtk ] = cst;
                got[ nxtst ][ nxt ][ nxtk ] = true;
            }
            cst = dp2[ i ][ j ][ k ] + t;
            if( !got[ nxtst ][ nxt ][ 1 ] ||
                cst < dp2[ nxtst ][ nxt ][ 1 ] ){
              if( k == 0 ){
                dp2[ nxtst ][ nxt ][ 1 ] = cst;
                got[ nxtst ][ nxt ][ 1 ] = true;
              }
            }
          }
  //printf( "%d\n" , dp2[ ( 1 << p ) - 1 ][ 0 ][ 0 ] + scst );
  //printf( "%d\n" , dp2[ ( 1 << p ) - 1 ][ 0 ][ 1 ] + scst );
  if( got[ ( 1 << p ) - 1 ][ 0 ][ 0 ] && 
      dp2[ ( 1 << p ) - 1 ][ 0 ][ 0 ] + scst <= g )
    puts( "possible without taxi" );
  else if( got[ ( 1 << p ) - 1 ][ 0 ][ 1 ] && 
           dp2[ ( 1 << p ) - 1 ][ 0 ][ 1 ] + scst <= g )
    puts( "possible with taxi" );
  else puts( "impossible" );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
