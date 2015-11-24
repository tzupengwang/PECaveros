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
#define N 10010
int a , b;
void build(){

}
void init(){
  a = getint();
  b = getint();
}
char c[ 2 ][ N ];
void solve(){
  int x = max( a , b );
  for( int i = 1 ; i <= x ; i ++ ){
    c[ 0 ][ i * 2 - 1 ] = '@'; c[ 1 ][ i * 2 - 1 ] = '@';
    c[ 0 ][ i * 2 ] = '.';     c[ 1 ][ i * 2 ] = '.';
  }
  int lsa = x - a;
  for( int i = 1 ; i <= lsa ; i ++ )
    c[ 1 ][ i * 2 ] = '@';
  int lsb = x - b;
  for( int i = 1 ; i <= lsb ; i ++ )
    c[ 1 ][ i * 2 + 1 ] = '.';
  c[ 0 ][ x * 2 + 1 ] =
  c[ 1 ][ x * 2 + 1 ] = '\0';
  printf( "%d %d\n" , 2 , x * 2 );
  puts( c[ 0 ] + 1 );
  puts( c[ 1 ] + 1 );
}
int main(){
  freopen( "black.in" , "r" , stdin );
  freopen( "black.out" , "w" , stdout );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
