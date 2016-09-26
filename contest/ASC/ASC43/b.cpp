#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long LL;
#define N 101010
const LL inf = 5000000000000000050LL;
LL dp[ N ] , ps[ N ];
void build(){
  dp[ 0 ] = 0;
  ps[ 0 ] = 0;
  dp[ 1 ] = 1;
  ps[ 1 ] = 1;
  // dp[ n ] = sum dp[ n - 1 ] .. dp[ 0 ];
  LL psum = 2;
  for( LL i = 2 ; i < N ; i ++ ){
    dp[ i ] = psum;
    psum += dp[ i ];
    if( psum > inf ) psum = inf;
    ps[ i ] = ps[ i - 1 ] + dp[ i ];
    if( ps[ i ] > inf ) ps[ i ] = inf;
  }
}
LL n , k , ans[ N ];
void solve(){
  for( LL i = 1 ; i <= n ; ){
    if( ps[ n - i ] >= inf ){
      ans[ i ] = i;
      i ++;
      continue;
    }
    LL bl = i , br = n , ba = i;
    while( bl <= br ){
      LL bmid = ( bl + br ) >> 1;
      LL lft = n - bmid;
      LL rgt = n - i;
      LL tans = ps[ rgt ] - ps[ lft ];
      if( tans < k ) ba = bmid , bl = bmid + 1;
      else br = bmid - 1;
    }
    LL lft = n - ba;
    LL rgt = n - i;
    LL tans = ps[ rgt ] - ps[ lft ];
    k -= tans;
    ans[ i ] = ba;
    for( LL j = i + 1 ; j <= ba ; j ++ )
      ans[ j ] = j - 1;
    i = ba + 1;
  }
  for( LL i = 1 ; i <= n ; i ++ )
    printf( "%llu%c" , ans[ i ] , " \n"[ i == n ] );
}
int main(){
  freopen( "bubble.in" , "r" , stdin );
  freopen( "bubble.out" , "w" , stdout );
  build();
  while( scanf( "%llu%llu" , &n , &k ) == 2 && n )
    solve();
}
