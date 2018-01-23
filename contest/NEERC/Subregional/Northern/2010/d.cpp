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
#define N 40010
int w , h , n;
vector<int> x , y;
void build(){

}
void init(){
  w = getint();
  h = getint();
  n = getint();
  for( int i = 0 ; i < n ; i ++ ){
    int tx = getint();
    int ty = getint();
    x.PB( tx );
    y.PB( ty );
  }
  x.PB( 0 );
  x.PB( w + 1 );
  y.PB( 0 );
  y.PB( h + 1 );
  sort( ALL( x ) );
  sort( ALL( y ) );
}
void solve(){
  int maxw = 0 , maxh = 0;
  for( int i = 1 ; i < (int)x.size() ; i ++ )
    maxw = max( maxw , x[ i ] - x[ i - 1 ] - 1 );
  for( int i = 1 ; i < (int)y.size() ; i ++ )
    maxh = max( maxh , y[ i ] - y[ i - 1 ] - 1 );
  cout << maxw * maxh << endl;
}
int main(){
  freopen( "defense.in" , "r" , stdin );
  freopen( "defense.out" , "w" , stdout );
    build();
//    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
