#include <bits/stdc++.h>
using namespace std;
#define N 202020
typedef long long LL;
int n , x[ N ] , y[ N ];
void init(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ ){
    scanf( "%d%d" , &x[ i ] , &y[ i ] );
    x[ i ] %= 2;
    y[ i ] %= 2;
    if( x[ i ] < 0 ) x[ i ] = -x[ i ];
    if( y[ i ] < 0 ) y[ i ] = -y[ i ];
  }
  x[ n ] = x[ 0 ];
  y[ n ] = y[ 0 ];
}
int cnt[ 2 ][ 2 ][ 2 ];
void solve(){
  int sum = 0;
  for( int i = 0 ; i < n ; i ++ ){
    sum += ( x[ i ] * y[ i + 1 ] - x[ i + 1 ] * y[ i ] );
    sum %= 2;
    if( sum < 0 ) sum = -sum;
  }
  if( sum != 0 ){
    puts( "0" );
    return;
  }
  LL ans = 0;
  int nsum = 0;
  for( int i = 0 ; i < n ; i ++ ){
    if( i ){
      nsum += ( x[ i - 1 ] * y[ i ] - x[ i ] * y[ i - 1 ] );
      nsum %= 2;
      if( nsum < 0 ) nsum = -nsum;
    }
    for( int psum = 0 ; psum < 2 ; psum ++ )
      for( int px = 0 ; px < 2 ; px ++ )
        for( int py = 0 ; py < 2 ; py ++ ){
          int xsum = ( nsum - psum ) % 2;
          if( xsum < 0 ) xsum = -xsum;
          xsum += ( x[ i ] * py - y[ i ] * px );
          xsum = ( xsum % 2 + 2 ) % 2;
          if( xsum == 0 )
            ans += cnt[ psum ][ px ][ py ];
        }
    cnt[ nsum ][ x[ i ] ][ y[ i ] ] ++;
  }
  printf( "%lld\n" , ans - n );
}
int main(){
  freopen( "integral.in" , "r" , stdin );
  freopen( "integral.out" , "w" , stdout );
  init();
  solve();
}
