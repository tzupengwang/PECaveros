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
void build(){

}
int n , a[ N ][ N ];
void init(){
  n = getint();
}
int now;
void st( int x , int y ){
  a[ x ][ y ] = ++ now;
}
int go_o( int ln , int rn , int lm , int rm ){
  int len = ( rn - ln + 1 );
  if( len == 3 ){
    st( ln , rm );
    st( ln + 1 , rm );
    st( ln + 1 , rm - 1 );
    st( ln , rm - 1 );
    st( ln , rm - 2 );
    st( ln + 1 , rm - 2 );
    st( ln + 2 , rm - 2 );
    st( ln + 2 , rm - 1 );
    st( ln + 2 , rm  );
    return 0;
  }
  int stp = 1 - go_o( ln , rn - 2 , lm + 2 , rm );
  if( stp ){
    for( int i = rm , j = 1 ; i >= lm + 2 ; i -- , j = 1 - j )
      if( j ){
        st( rn - 1 , i );
        st( rn , i );
      }else{
        st( rn , i );
        st( rn - 1 , i );
      }
    for( int i = rn , j = 1 ; i >= ln ; i -- , j = 1 - j )
      if( j ){
        st( i , lm + 1 );
        st( i , lm );
      }else{
        st( i , lm );
        st( i , lm + 1 );
      }
  }else{
    for( int i = ln , j = 1 ; i <= rn - 2 ; i ++ , j = 1 - j )
      if( j ){
        st( i , lm + 1 );
        st( i , lm );
      }else{
        st( i , lm );
        st( i , lm + 1 );
      }
    st( rn - 1 , lm );
    st( rn , lm );
    st( rn , lm + 1 );
    st( rn - 1 , lm + 1 );
    for( int i = lm + 2 , j = 1 ; i <= rm ; i ++ , j = 1 - j )
      if( j ){
        st( rn - 1 , i );
        st( rn , i );
      }else{
        st( rn , i );
        st( rn - 1 , i );
      }
  }
  return stp;
}
int go_e( int ln , int rn , int lm , int rm ){
  int len = ( rn - ln + 1 );
  if( len == 2 ){
    st( ln , rm );
    st( ln , lm );
    st( rn , lm );
    st( rn , rm );
    return 0;
  }
  int stp = 1 - go_e( ln , rn - 2 , lm + 2 , rm );
  if( stp ){
    for( int i = rm , j = 1 ; i >= lm ; i -- , j = 1 - j )
      if( j ){
        st( rn - 1 , i );
        st( rn , i );
      }else{
        st( rn , i );
        st( rn - 1 , i );
      }
    for( int i = rn - 2 , j = 1 ; i >= ln ; i -- , j = 1 - j )
      if( j ){
        st( i , lm );
        st( i , lm + 1 );
      }else{
        st( i , lm + 1 );
        st( i , lm );
      }
  }else{
    for( int i = ln , j = 1 ; i <= rn ; i ++ , j = 1 - j )
      if( j ){
        st( i , lm + 1 );
        st( i , lm );
      }else{
        st( i , lm );
        st( i , lm + 1 );
      }
    for( int i = lm + 2 , j = 1 ; i <= rm ; i ++ , j = 1 - j )
      if( j ){
        st( rn , i );
        st( rn - 1 , i );
      }else{
        st( rn - 1 , i );
        st( rn , i );
      }
  }
  return stp;
}
void go_e( int lm , int rm ){
  if( lm > rm ) return;
  if( rm - lm + 1 == 2 ){
    for( int i = 1 , j = 1 ; i <= n ; i ++ , j = 1 - j )
      if( j ){
        st( i , lm );
        st( i , rm );
      }else{
        st( i , rm );
        st( i , lm );
      }
    return;
  }
  for( int i = 1 , j = 1 ; i <= n - 2 ; i ++ , j = 1 - j )
    if( j ){
      st( i , lm );
      st( i , lm + 1 );
    }else{
      st( i , lm + 1 );
      st( i , lm );
    }
  st( n - 1 , lm ); st( n , lm );
  st( n , lm + 1 ); st( n - 1 , lm + 1 );
  st( n - 1 , lm + 2 ); st( n , lm + 2 );
  st( n , lm + 3 ); st( n - 1 , lm + 3 );
  for( int i = n - 2 , j = 1 ; i >= 1 ; i -- , j = 1 - j )
    if( j ){
      st( i , lm + 3 );
      st( i , lm + 2 );
    }else{
      st( i , lm + 2 );
      st( i , lm + 3 );
    }
  go_e( lm + 4 , rm );
}
void solve(){
  now = 0;
  if( n & 1 ) go_o( 1 , n , 1 , n );
  else go_e( 1 , n );
  printf( "%d\n" , n );
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= n ; j ++ )
      printf( "%d%c" , a[ i ][ j ] , " \n"[ j == n ] );
}
int main(){
  build();
  __ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
