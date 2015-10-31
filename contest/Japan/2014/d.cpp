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
#define N 11
int d , n , b;
int x[ N ], h[ N ];
void build(){

}
void init(){
  d = getint();
  n = getint();
  b = getint();
  for( int i = 1 ; i <= n ; i ++ ){
    x[ i ] = getint();
    h[ i ] = getint();
  }
}
bool test( int nb , D Viy ){
  D Vix = (D)d / ( ( 2.0 * (D)( nb + 1 ) ) * Viy );
  for( int i = 1 ; i <= n ; i ++ ){
    int bns = (D)x[ i ] / ( (D)d / (D)( nb + 1 ) );
    D nx = x[ i ] - (D)bns * ( (D)d / (D)( nb + 1 ) );
    D ny = -( nx * nx / ( 2.0 * Vix * Vix ) ) + nx * Viy / Vix;
    if( ny - eps < (D)h[ i ] ) return false;
  }
  return true;
}
void solve(){
  D ans = 1e30;
  for( int i = 0 ; i <= b ; i ++ ){
    D l = sqrt( (D)d / ( 2.0 * (D)( i + 1 ) ) ), r = 1e20 , mid;
    for( int j = 0 ; j < 1000 ; j ++ ){
      mid = ( l + r ) * 0.5;
      if( test( i , mid ) ) r = mid;
      else l = mid;
    }
    D Vix = (D)d / ( ( 2.0 * (D)( i + 1 ) ) * mid );
    D tans = hypot( Vix , mid );
    ans = min( ans , tans );
  }
  printf( "%.8f\n" , ans );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
