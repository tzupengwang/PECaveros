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
void build(){

}
D w , h , x , nx , ny;
D mu;
void init(){
  w = getint();
  h = getint();
  x = getint();
  nx = getint();
  ny = getint();
  scanf( "%lf" , &mu );
}
D theta2;
D f( D mid ){
  D tx = nx - ( ny - mid ) / ( ny - h ) * ( nx - w );
  D tx2 = tx - mid * tan( theta2 );
  return tx2;
}
void solve(){
  D theta = atan2( nx - w , ny - h );
  theta2 = asin( sin( theta ) / mu );
  D l = 0.0 , r = h + h , mid;
  for( int i = 0 ; i < 100 ; i ++ ){
    mid = ( l + r ) * 0.5;
    if( f( mid ) > x ) r = mid;
    else l = mid;
  }
  if( mid > h ) puts( "Impossible" );
  else printf( "%.4f\n" , mid );
}
int main(){
    build();
    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
