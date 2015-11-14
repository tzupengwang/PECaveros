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
#define N 1000010
char c[ N ];
char ch[ 26 ];
void build(){

}
void init(){
  scanf( "%s" , c );
  for( int i = 0 ; i < 26 ; i ++ )
    ch[ i ] = i;
}
char find_c( char ctmp ){
  if( ctmp >= 'A' && ctmp <= 'Z' ){
    printf( "%c %d\n" , ctmp , (int)ch[ ctmp - 'A' ] );
    if( (int)ch[ ctmp - 'A' ] == (int)ctmp - (int)'A' )
      return ctmp;
    return ch[ ctmp - 'A' ] = find_c( ch[ ctmp - 'A' ] + 'A' );
  }
  return ctmp;
}
void solve(){
  int m = getint();
  while( m -- ){
    char ta[ 3 ];
    char tb[ 3 ];
    scanf( "%s%s" , ta , tb );
    for( int i = 0 ; i < 26 ; i ++ )
      if( ch[ i ] == tb[ 0 ] - 'A' )
        ch[ i ] = ta[ 0 ] - 'A';
    // ch[ tb[ 0 ] - 'A' ] = ta[ 0 ] - 'A';
  }
  int len = strlen( c );
  for( int i = 0 ; i < len ; i ++ )
    if( c[ i ] >= 'A' && c[ i ] <= 'Z' )
      putchar( ch[ c[ i ] - 'A' ] + 'A' );
    else putchar( c[ i ] );
    // putchar( find_c( c[ i ] ) );
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
