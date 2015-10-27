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
#define N 510
int n , m , a , b;
char c[ N ][ N ];
bool in( int xn , int xm ){
  return 1 <= xn && xn <= n &&
         1 <= xm && xm <= m;
}
int dn[]={0,0,1,-1};
int dm[]={1,-1,0,0};
void build(){

}
void init(){
  m = getint();
  n = getint();
  a = getint();
  b = getint();
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%s" , c[ i ] + 1 );
}
int dst[ N ][ N ];
bool got[ N ][ N ];
priority_queue< pair<int,PII> , vector< pair<int,PII> >,
                                greater< pair<int,PII> > > heap;
void solve(){
  heap.push( MP( 0 , MP( 1 , 1 ) ) );
  while( heap.size() ){
    int cst = heap.top().FI;
    int xn = heap.top().SE.FI;
    int xm = heap.top().SE.SE;
    heap.pop();
    if( got[ xn ][ xm ] ) continue;
    got[ xn ][ xm ] = true;
    dst[ xn ][ xm ] = cst;
 //   printf( "%d %d %d\n" , xn , xm , cst );
    int ncst = cst;
    if( ( xn % 2 ) ^ ( xm % 2 ) ) ncst += a;
    else ncst += b;
    for( int i = 0 ; i < 4 ; i ++ ){
      int nxtn = xn + dn[ i ];
      int nxtm = xm + dm[ i ];
      if( in( nxtn , nxtm ) && c[ nxtn ][ nxtm ] != '#' &&
          !got[ nxtn ][ nxtm ] )
        heap.push( MP( ncst , MP( nxtn , nxtm ) ) );
    }
  }
  if( !got[ n ][ m ] ) puts( "IMPOSSIBLE" );
  else printf( "%d\n" , dst[ n ][ m ] );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
