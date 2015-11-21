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
#define N 1021
int n , dp[ N ][ N * 3 ];
char c[ N ];
void build(){

}
void init(){
  scanf( "%s" , c + 1 );
  n = strlen( c + 1 );
}
void solve(){
  for( int i = 0 ; i <= n ; i ++ )
    for( int j = 0 ; j <= n + n + n ; j ++ )
      dp[ i ][ j ] = INF;
  for( int i = 0 ; i <= n ; i ++ )
    dp[ 0 ][ i ] = i;
  for( int i = 1 ; i <= n + 1 ; i ++ ){
    for( int j = 1 ; j < 3 * n - 1 ; j ++ )
      dp[ i - 1 ][ j + 1 ] = min( dp[ i - 1 ][ j + 1 ],
                                  dp[ i - 1 ][ j ] + 1 );
    for( int j = 3 * n - 1 ; j > 1 ; j -- )
      dp[ i - 1 ][ j - 1 ] = min( dp[ i - 1 ][ j - 1 ],
                                  dp[ i - 1 ][ j ] + 1 );
    if( c[ i ] == '*' ){
      for( int j = 2 ; j < 3 * n ; j ++ )
        dp[ i ][ j - 1 ] = min( dp[ i ][ j - 1 ] ,
                                dp[ i - 1 ][ j ] );
    }else{
      for( int j = 3 * n - 2 ; j >= (i == 1 ? 0 : 1) ; j -- )
        dp[ i ][ j + 1 ] = min( dp[ i ][ j + 1 ] ,
                                dp[ i - 1 ][ j ] );
      if( c[ i - 1 ] >= '0' && c[ i - 1 ] <= '9' ){
        for( int j = 3 * n - 1 ; j >= 1 ; j -- )
          dp[ i ][ j ] = min( dp[ i ][ j ] ,
                              dp[ i - 1 ][ j ] );
      }
    }
    if( i > 1 && ( ( c[ i ] >= '0' && c[ i ] <= '9' ) ^
                   ( c[ i - 1 ] >= '0' && c[ i - 1 ] <= '9' ) ) ){
      // printf( "%d " , i );
      dp[ i ][ 1 ] = min( dp[ i ][ 1 ] , dp[ i - 2 ][ 1 ] + 1 );
      // printf( "%d %d\n" , dp[ i ][ 1 ] , dp[ i - 2 ][ 1 ] );
    }
  }
  int ans = dp[ n ][ 1 ];
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
