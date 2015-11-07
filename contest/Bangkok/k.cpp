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
#define N 110
int s , c , a[ N ][ N ] , cst[ N ][ N ]; 
void build(){

}
void init(){
  s = getint();
  c = getint();
  for( int i = 1 ; i <= s ; i ++ ){
    for( int j = 1 ; j <= c ; j ++ )
      a[ i ][ j ] = getint();
  }
  for( int i = 1 ; i <= s ; i ++ )
    for( int j = 1 ; j <= s ; j ++ )
      cst[ i ][ j ] = getint();
}
int dp[ N ][ N ];
void solve(){
  for( int j = 1 ; j <= s ; j ++ )
    for( int i = 1 ; i <= c ; i ++ )
      dp[ j ][ i ] = -INF;
  for( int i = 1 ; i <= s ; i ++ )
    dp[ i ][ 1 ] = a[ i ][ 1 ];
  for( int i = 1 ; i < c ; i ++ )
    for( int j = 1 ; j <= s ; j ++ ){
      for( int k = 1 ; k <= s ; k ++ ){
        int nxt = dp[ j ][ i ] - cst[ j ][ k ] + a[ k ][ i + 1 ];
        dp[ k ][ i + 1 ] = max( dp[ k ][ i + 1 ] , nxt );
      }
    }
  int ans = -INF;
  for( int i = 1 ; i <= s ; i ++ )
    ans = max( ans , dp[ i ][ c ] );
  printf( "%d\n" , ans );
}
int main(){
    build();
    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
