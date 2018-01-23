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
#define N 20
D w , h;
int n;
D x[ N ] , y[ N ] , sx , sy;
D dp[ N ][ 1 << N ];
bool got[ N ][ 1 << N ];
void build(){

}
void init(){
  w = getint();
  h = getint();
  n = getint();
  for( int i = 0 ; i < n ; i ++ ){
    x[ i ] = getint();
    y[ i ] = getint();
  }
  sx = getint(); sy = getint();
}
D sqr( D _ ){
  return _ * _;
}
D dist( D ux , D uy , D vx , D vy ){
  return sqrt( sqr( ux - vx ) +
               sqr( uy - vy ) );
}
D mindist( D ux , D uy , D vx , D vy ){
  D tdist = 1e20;
  tdist = min( tdist , dist( ux , uy , vx , -vy ) );
  tdist = min( tdist , dist( ux , uy , vx , vy + 2.0 * ( h - vy ) ) );
  tdist = min( tdist , dist( ux , uy , -vx , vy ) );
  tdist = min( tdist , dist( ux , uy , vx + 2.0 * ( w - vx ) , vy ) );
  return tdist;
}
D DP( int lst , int msk , int res ){
  if( got[ lst ][ msk ] ) return dp[ lst ][ msk ];
  got[ lst ][ msk ] = true;
  if( res == 0 ){
    return dp[ lst ][ msk ] =
              dist( sx , sy , x[ lst ] , y[ lst ] );
  }else{
    D tans = 1e20;
    for( int i = 0 ; i < n ; i ++ )
      if( msk & ( 1 << i ) ){
        D dlt = mindist( x[ lst ] , y[ lst ] , x[ i ] , y[ i ] );
        tans = min( tans , dlt +
            DP( i , msk ^ ( 1 << i ) , res - 1 ) );
      }
    return dp[ lst ][ msk ] = tans;
  }
}
D tob( int idx ){
  return min( min( x[ idx ] , y[ idx ] ) ,
              min( w - x[ idx ] , h - y[ idx ] ) );
}
void solve(){
  D ans = 1e20;
  for( int i = 0 ; i < n ; i ++ )
    ans = min( ans , tob( i ) + DP( i , ( ( 1 << n ) - 1 ) ^
                              ( 1 << i ) , n - 1 ) );
  printf( "%.12f\n" , ans );
}
int main(){
  freopen( "kitchen.in" , "r" , stdin );
  freopen( "kitchen.out" , "w" , stdout );
    build();
//    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
