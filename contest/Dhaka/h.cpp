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
#define N 10010
int n , a[ 170 ] , s[ 170 ];
void build(){

}
void init(){
  n = getint();
  for( int i = 0 ; i <= 160 ; i ++ )
    s[ i ] = a[ i ] = 0;
  for( int i = 0 ; i < n ; i ++ )
    a[ getint() ] ++;
  for( int i = 160 ; i >= 0 ; i -- )
    s[ i ] = s[ i + 1 ] + a[ i ];
}
D dp[ 9 ][ 170 ];
int bk[ 9 ][ 170 ];
void solve(){
  D qr = (D)n / 4.0;
  for( int i = 160 ; i >= 0 ; i -- )
    dp[ 1 ][ i ] = fabs( qr - s[ i ] );
  for( int i = 2 ; i <= 4 ; i ++ )
    for( int j = 160 - i + 1 ; j >= 0 ; j -- ){
      dp[ i ][ j ] = n * n;
      int bst = -1;
      for( int k = j + 1 ; k <= 160 - ( i - 2 ) ; k ++ ){
        D tmp = fabs( qr - ( s[ j ] - s[ k ] ) ) + dp[ i - 1 ][ k ];
        if( tmp < dp[ i ][ j ] ){
          dp[ i ][ j ] = tmp;
          bst = k;
        }
      }
      bk[ i ][ j ] = bst;
    }
  printf( "Case %d:" , ++ cs );
  int now = 4, np = 0;
  while( now >= 2 ){
    printf( " %d" , bk[ now ][ np ] - 1 );
    np = bk[ now ][ np ];
    now --;
  }
  puts( "" );
}
int main(){
    build();
    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
