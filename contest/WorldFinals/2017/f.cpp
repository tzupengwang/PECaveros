#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 256
LL d , k , cnt[ N ];
bool gt[ N ][ N ];
LL cst[ N ][ N ];
LL sqr( LL _ ){ return _ * _; }
LL lcst[ N ] , rcst[ N ];
LL cost( LL l , LL r ){
  if( gt[ l ][ r ] ) return cst[ l ][ r ];
  gt[ l ][ r ] = true;
  LL ret = 0;
  for( LL i = l + 1 ; i <= r ; i ++ )
    ret += cnt[ i ] * sqr( min( i - l , r - i ) );
  return cst[ l ][ r ] = ret;
}
void init(){
  cin >> d >> k;
  while( d -- ){
    LL ai , bi;
    cin >> ai >> bi;
    cnt[ ai ] += bi;
  }
  for( LL i = 0 ; i < N ; i ++ )
    for( LL j = 0 ; j <= i ; j ++ )
      lcst[ i ] += cnt[ j ] * sqr( i - j );
  for( LL i = 0 ; i < N ; i ++ )
    for( LL j = i + 1 ; j < N ; j ++ )
      rcst[ i ] += cnt[ j ] * sqr( j - i );
}
LL dp[ N ][ N ];
void solve(){
  for( LL i = 0 ; i < N ; i ++ )
    for( LL j = 1 ; j <= min( i + 1 , k ) ; j ++ ){
      if( j == 1 )
        dp[ i ][ j ] = lcst[ i ];
      else{
        dp[ i ][ j ] = -1;
        for( LL p = 0 ; p < i ; p ++ ){
          LL tdp = dp[ p ][ j - 1 ] + cost( p , i );
          if( dp[ i ][ j ] == -1 or tdp < dp[ i ][ j ] )
            dp[ i ][ j ] = tdp;
        }
      }
    }
  LL ans = -1;
  for( int i = k - 1 ; i < N ; i ++ ){
    LL tans = dp[ i ][ k ] + rcst[ i ];
    if( ans == -1 or tans < ans )
      ans = tans;
  }
  printf( "%lld\n" , ans );
}
int main(){
  init();
  solve();
}
