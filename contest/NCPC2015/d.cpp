#include <stdio.h>
#include <algorithm>
#include <iostream>
using namespace std;
int __ = 1;
#define N 40
bool p[ N ];
typedef long long ll;
ll fib[ N ];
void build(){
  p[ 1 ] = true;
  for( int i = 2 ; i < N ; i ++ ) if( !p[ i ] )
    for( int j = i + i ; j < N ; j += i )
      p[ j ] = true;
  fib[ 1 ] = 1; fib[ 2 ] = 1;
  for( int i = 3 ; i < N ; i ++ )
    fib[ i ] = fib[ i - 1 ] + fib[ i - 2 ];
}
int n;
bool in[ N ];
void init(){
  scanf( "%d" , &n );
  for( int i = 1 ; i <= n ; i ++ )
    in[ i ] = true;
}
void solve(){
  int now = 1;
  int dir = 1;
  for( int i = 1 ; i < n ; i ++ ){
    int lf = n - i + 1;
    int tmp = fib[ i ] % lf;
    if( tmp == 0 ) tmp = lf;
    while( !in[ now ] ){
      now += dir;
      if( now > n ) now = 1;
      if( now < 1 ) now = n;
    }
    while( -- tmp ){
      now += dir;
      if( now > n ) now = 1;
      if( now < 1 ) now = n;
      while( !in[ now ] ){
        now += dir;
        if( now > n ) now = 1;
        if( now < 1 ) now = n;
      }
    }
    in[ now ] = false;
    if( !p[ now ] )
      dir = -dir;
  }
  int ans = 1;
  for( int i = 1 ; i <= n ; i ++ )
    if( in[ i ] )
      ans = i;
  cout << ans << endl;
}
int main(){
  build();
  int _;
  scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
