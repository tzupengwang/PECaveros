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
ll add( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x + _y;
  if( _ >= _mod ) _ -= _mod;
  return _;
}
ll sub( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x - _y;
  if( _ < 0 ) _ += _mod;
  return _;
}
ll mul( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x * _y;
  if( _ >= _mod ) _ %= _mod;
  return _;
}
bool equal( D _x ,  D _y ){
  return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , cs;
/*********default*********/
#define N 110
void build(){

}
D ans;
int n , type , x[ N ];
char c[ N ];
void init(){
  n = getint();
  scanf( "%s" , c );
  if( c[ 0 ] == 'b' ) type = 2;
  if( c[ 0 ] == 'n' ) type = 0;
  if( c[ 0 ] == 'd' ) type = 10;
  for( int i = 0 ; i < n ; i ++ )
    x[ i ] = getint();
}
void solve(){
  ans = 0;
  for( int i = 0 ; i < n ; i ++ ){
    D dlt = 0.0; 
    if( x[ i ] == 0 ) dlt = 0.0;
    else if( type ) dlt = ( (D)x[ i ] / 100.0 ) * ( log( (D)x[ i ] / 100.0 ) / log( type ) );
    else dlt = ( (D)x[ i ] / 100.0 ) * ( log( (D)x[ i ] / 100.0 ) );
    ans -= dlt;
  }
  printf( "%.12f\n" , ans );
}
int main(){
  build();
  __ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
