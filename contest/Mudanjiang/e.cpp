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
#define N 514
int n;
int ans[ N ][ N ];
void build(){

}
void init(){
  n = getint();
}
int now;
void go_e( int ln , int rn , int lm , int rm , int stp ){
  int len = rn - ln + 1;
  if( len == 2 ){
    if( !stp ){
      ans[ ln ][ rm ] = ++ now; ans[ ln ][ lm ] = ++ now;
      ans[ rn ][ lm ] = ++ now; ans[ rn ][ rm ] = ++ now;
    }else{
      ans[ rn ][ lm ] = ++ now; ans[ rn ][ rm ] = ++ now;
      ans[ ln ][ rm ] = ++ now; ans[ ln ][ lm ] = ++ now;
    }
    return;
  }
  if( !stp ){
    for( int i = ln , j = 0 ; i <= rn ; i ++ , j = 1 - j )
      if( !j ){
        ans[ i ][ lm + 1 ] = ++ now;
        ans[ i ][ lm ] = ++ now;
      }else{
        ans[ i ][ lm ] = ++ now;
        ans[ i ][ lm + 1 ] = ++ now;
      }
    for( int j = lm + 2 , i = 0 ; j <= rm - 2 ; j ++ , i = 1 - i )
      if( !i ){
        ans[ rn ][ j ] = ++ now;
        ans[ rn - 1 ][ j ] = ++ now;
      }else{
        ans[ rn - 1 ][ j ] = ++ now;
        ans[ rn ][ j ] = ++ now;
      }
    ans[ rn ][ rm - 1 ] = ++ now;
    ans[ rn ][ rm ] = ++ now;
    ans[ rn - 1 ][ rm ] = ++ now;
    ans[ rn - 1 ][ rm - 1 ] = ++ now;
    go_e( ln , rn - 2 , lm + 2 , rm , 1 - stp );
  }else{
    for( int i = rn , j = 0 ; i >= ln ; i -- , j = 1 - j )
      if( !j ){
        ans[ i ][ rm - 1 ] = ++ now;
        ans[ i ][ rm ] = ++ now;
      }else{
        ans[ i ][ rm ] = ++ now;
        ans[ i ][ rm - 1 ] = ++ now;
      }
    for( int j = rm - 2 , i = 0 ; j >= lm + 2 ; j -- , i = 1 - i )
      if( !i ){
        ans[ ln ][ j ] = ++ now;
        ans[ ln + 1 ][ j ] = ++ now;
      }else{
        ans[ ln + 1 ][ j ] = ++ now;
        ans[ ln ][ j ] = ++ now;
      }
    ans[ ln ][ lm + 1 ] = ++ now;
    ans[ ln ][ lm ] = ++ now;
    ans[ ln + 1 ][ lm ] = ++ now;
    ans[ ln + 1 ][ lm + 1 ] = ++ now;
    go_e( ln + 2 , rn , lm , rm - 2 , 1 - stp );
  }
}
void go_o( int ln , int rn , int lm , int rm , int stp ){
  int len = rn - ln + 1;
  if( len == 3 ){
    if( !stp ){
      ans[ ln ][ lm ] = ++ now;
      ans[ ln ][ lm + 1 ] = ++ now;
      ans[ ln + 1 ][ lm + 1 ] = ++ now;
      ans[ ln + 1 ][ lm ] = ++ now;
      ans[ ln + 2 ][ lm ] = ++ now;
      ans[ ln + 2 ][ lm + 1 ] = ++ now;
      ans[ ln + 2 ][ lm + 2 ] = ++ now;
      ans[ ln + 1 ][ lm + 2 ] = ++ now;
      ans[ ln ][ lm + 2 ] = ++ now;
    }else{
      ans[ rn ][ rm ] = ++ now;
      ans[ rn ][ rm - 1 ] = ++ now;
      ans[ rn - 1 ][ rm - 1 ] = ++ now;
      ans[ rn - 1 ][ rm ] = ++ now;
      ans[ rn - 2 ][ rm ] = ++ now;
      ans[ rn - 2 ][ rm - 1 ] = ++ now;
      ans[ rn - 2 ][ rm - 2 ] = ++ now;
      ans[ rn - 1 ][ rm - 2 ] = ++ now;
      ans[ rn ][ rm - 2 ] = ++ now;
    }
    return;
  }
  if( !stp ){
    for( int i = ln , j = 0 ; i <= rn ; i ++ , j = 1 - j )
      if( !j ){
        ans[ i ][ lm ] = ++ now;
        ans[ i ][ lm + 1 ] = ++ now;
      }else{
        ans[ i ][ lm + 1 ] = ++ now;
        ans[ i ][ lm ] = ++ now;
      }
    for( int j = lm + 2 , i = 0 ; j <= rm ; j ++ , i = 1 - i )
      if( !i ){
        ans[ rn ][ j ] = ++ now;
        ans[ rn - 1 ][ j ] = ++ now;
      }else{
        ans[ rn - 1 ][ j ] = ++ now;
        ans[ rn ][ j ] = ++ now;
      }
    go_o( ln , rn - 2 , lm + 2 , rm , 1 - stp );
  }else{
    for( int i = rn , j = 1 ; i >= ln ; i -- , j = 1 - j )
      if( !j ){
        ans[ i ][ rm - 1 ] = ++ now;
        ans[ i ][ rm ] = ++ now;
      }else{
        ans[ i ][ rm ] = ++ now;
        ans[ i ][ rm - 1 ] = ++ now;
      }
    for( int j = rm - 2 , i = 0 ; j >= lm ; j -- , i = 1 - i )
      if( !i ){
        ans[ ln ][ j ] = ++ now;
        ans[ ln + 1 ][ j ] = ++ now;
      }else{
        ans[ ln + 1 ][ j ] = ++ now;
        ans[ ln ][ j ] = ++ now;
      }
    go_o( ln + 2 , rn , lm , rm - 2 , 1 - stp );
  }
}
void solve(){
  now = 0;
  if( n & 1 ) go_o( 1 , n , 1 , n , 0 );
  else go_e( 1 , n , 1 , n , 0 );
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= n ; j ++ )
      printf( "%d%c" , ans[ i ][ j ] , " \n"[ j == n ] );
}
int main(){
  build();
  __ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
