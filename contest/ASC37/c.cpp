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
#define N 410
int cnt[ N ];
int dp[ N ][ N ];
D ans[ N ];
char c[ N ];
int len;
void build(){
  freopen( "blind.in" , "r" , stdin );
  freopen( "blind.out" , "w" , stdout );
}
void init(){
  scanf( "%s" , c );
  len = strlen( c );
}
void tsolve( int k ){
  memset( cnt , 0 , sizeof( cnt ) );
  memset( dp , 0 , sizeof( dp ) );
  for( int i = 0 ; i < k * len ; i ++ )
    cnt[ i % k ] += ( c[ i % len ] - '0' );
  for( int i = 1 ; i <= k ; i ++ )
    for( int j = 0 , u = i ; u >= 0 ; j ++ , u -- ){
      if( j && dp[ j - 1 ][ u ] + len - cnt[ k - i ] > dp[ j ][ u ] )
        dp[ j ][ u ] = dp[ j - 1 ][ u ] + len - cnt[ k - i ];
      if( u && dp[ j ][ u - 1 ] + cnt[ k - i ] > dp[ j ][ u ] )
        dp[ j ][ u ] = dp[ j ][ u - 1 ] + cnt[ k - i ];
    }
  for( int i = 1 ; i <= len ; i ++ )
    if( k <= i * 2 )
      for( int j = max( 0 , k - i ) ; j <= k && j <= i ; j ++ )
        ans[ i ] = max( ans[ i ] , (D)dp[ j ][ k - j ] / (D)( k * len ) );
}
void solve(){
  for( int tlen = 1 ; tlen <= len * 2 ; tlen ++ )
    tsolve( tlen );
  for( int i = 1 ; i <= len ; i ++ )
    printf( "%.12f\n" , ans[ i ] );
}
int main(){
    build();
//    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
