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
#define N 2010
int n , m , k;
int dp[ N ][ N ] , ds[ N ][ N ];
char c[ N ];
void build(){

}
void init(){
  n = getint();
  m = getint();
  k = getint();
  scanf( "%s" , c + 1 );
}
void solve(){
  n *= 2;
  dp[ n ][ 0 ] = 0;
  for( int i = 1 ; i <= k ; i ++ ) dp[ n ][ i ] = 1;
  for( int i = k + 1 ; i <= m ; i ++ ) dp[ n ][ i ] = 0;
  ds[ n ][ 0 ] = 0;
  for( int i = 1 ; i <= m ; i ++ )
    ds[ n ][ i ] = ds[ n ][ i - 1 ] + dp[ n ][ i ];
  for( int i = n - 1 ; i >= 1 ; i -- ){
    dp[ i ][ 0 ] = 0;
    if( c[ i ] != c[ i + 1 ] ){
      for( int j = 1 ; j <= m ; j ++ ){
        int tl = max( 0 , j - k ), tr = j - 1;
        int tmp = ds[ i + 1 ][ tr ];
        if( tl ) tmp -= ds[ i + 1 ][ tl - 1 ];
        if( ( tr - tl + 1 ) == tmp ) dp[ i ][ j ] = 0;
        else dp[ i ][ j ] = 1;
      }
    }else{
      for( int j = 1 ; j <= m ; j ++ ){
        int tl = max( 0 , j - k ), tr = j - 1;
        int tmp = ds[ i + 1 ][ tr ];
        if( tl ) tmp -= ds[ i + 1 ][ tl - 1 ];
        if( tmp == 0 ) dp[ i ][ j ] = 0;
        else dp[ i ][ j ] = 1;
      }
    }
    for( int j = 1 ; j <= k ; j ++ ) dp[ i ][ j ] = 1;
    ds[ i ][ 0 ] = dp[ i ][ 0 ];
    for( int j = 1 ; j <= m ; j ++ )
      ds[ i ][ j ] = ds[ i ][ j - 1 ] + dp[ i ][ j ];
  }
  char winc = 'A';
  if( (  dp[ 1 ][ m ] && c[ 1 ] == 'B' ) ||
      ( !dp[ 1 ][ m ] && c[ 1 ] == 'A' ) ) winc = 'B';
  // for( int i = 1 ; i <= n ; i ++ )
    // for( int j = 0 ; j <= m ; j ++ )
      // printf( "%d%c" , dp[ i ][ j ] , " \n"[ j == m ] );
  printf( "Case #%d: %c\n" , ++ cs , winc );
}
int main(){
    build();
    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
