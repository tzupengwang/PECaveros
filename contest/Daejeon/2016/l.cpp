#include <bits/stdc++.h>
using namespace std;
#define N (1 << 20)
int n , lc[ N ] , rc[ N ] , dp[ N ];
int cal_sz( int now ){
  if( now == 0 ) return 0;
  int ldp = cal_sz( lc[ now ] );
  int rdp = cal_sz( rc[ now ] );
  return dp[ now ] = min( ldp , rdp ) + 1;
}
int main(){
  while( scanf( "%d" , &n ) == 1 ){
    for( int i = 1 ; i <= n ; i ++ )
      scanf( "%d%d" , &lc[ i ] , &rc[ i ] );
    printf( "%d\n" , cal_sz( 1 ) );
    for( int i = 1 ; i <= n ; i ++ )
      lc[ i ] = rc[ i ] = 0;
  }
}
