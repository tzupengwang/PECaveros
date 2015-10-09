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
#define N 4010
int n , nn;
int x[ N ] , y[ N ] , psum[ N ];
void build(){

}
void init(){
  n = getint();
  for( int i = 0 ; i < n ; i ++ ){
    int tx = getint();
    int ty = getint();
    if( nn >= 2 ){
      if( x[ nn - 1 ] == tx && x[ nn - 2 ] == tx ) nn --;
      if( y[ nn - 1 ] == ty && y[ nn - 2 ] == ty ) nn --;
    }
    x[ nn ] = tx;
    y[ nn ++ ] = ty;
  }
  n = nn;
//  for( int i = 0 ; i < n ; i ++ )
//    printf( "%d %d\n" , x[ i ] , y[ i ] );
  for( int i = 1 ; i < n ; i ++ )
    psum[ i ] = psum[ i - 1 ] + abs( x[ i ] - x[ i - 1 ] ) +
                                abs( y[ i ] - y[ i - 1 ] );
}
bool jiou( int ti , int tj ){
  if( x[ ti ] == x[ ti - 1 ] && y[ tj ] == y[ tj - 1 ] ){
    bool okay1 = ( x[ tj - 1 ] <= x[ ti ] && x[ ti ] <= x[ tj ] ) ||
                 ( x[ tj - 1 ] >= x[ ti ] && x[ ti ] >= x[ tj ] );
    bool okay2 = ( y[ ti - 1 ] <= y[ tj ] && y[ tj ] <= y[ ti ] ) ||
                 ( y[ ti - 1 ] >= y[ tj ] && y[ tj ] >= y[ ti ] );
    return okay1 && okay2;
  }
  return false;
}
int ans;
void test( int ti , int tj ){
  if( jiou( ti , tj ) ){
    int jx = x[ ti ];
    int jy = y[ tj ];
    int tans = psum[ ti ] - psum[ tj - 1 ] -
                abs( jx - x[ tj - 1 ] ) -
                abs( y[ ti ] - jy );
    ans = min( ans , tans );
  }
  if( jiou( tj , ti ) ){
    int jy = y[ ti ];
    int jx = x[ tj ];
    int tans = psum[ ti ] - psum[ tj - 1 ] -
                abs( jy - y[ tj - 1 ] ) -
                abs( x[ ti ] - jx );
    ans = min( ans , tans );
  }
}
void solve(){
  ans = psum[ n - 1 ];
  for( int i = 2 ; i < n ; i ++ )
    for( int j = 1 ; j < i - 1 ; j ++ )
      test( i , j );
  printf( "%d\n" , ans );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
