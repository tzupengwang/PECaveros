#include <bits/stdc++.h>
using namespace std;
#define N 101010
int n;
vector< int > v[ N ];
void init(){
  scanf( "%d" , &n );
  for( int i = 1 ; i < n ; i ++ ){
    int ui , vi;
    scanf( "%d%d" , &ui , &vi );
    v[ ui ].push_back( vi );
    v[ vi ].push_back( ui );
  }
}
int dp[ N ][ 2 ];
// 0 no path 1 one path
void go( int now , int prt ){
  int sum = 0;
  for( int son : v[ now ] ){
    if( son == prt ) continue;
    go( son , now );
    sum += min( dp[ son ][ 0 ] , dp[ son ][ 1 ] );
  }
  dp[ now ][ 0 ] = dp[ now ][ 1 ] = sum + 1;
  int bst = n;
  for( int son : v[ now ] ){
    if( son == prt ) continue;
    int tsum = sum - min( dp[ son ][ 0 ] , dp[ son ][ 1 ] ) + dp[ son ][ 1 ];
    dp[ now ][ 0 ] = min( dp[ now ][ 0 ] , tsum );
    dp[ now ][ 1 ] = min( dp[ now ][ 1 ] , tsum );
    dp[ now ][ 0 ] = min( dp[ now ][ 0 ] , tsum + bst );
    bst = min( bst , dp[ son ][ 1 ] - 1 - min( dp[ son ][ 0 ] , dp[ son ][ 1 ] ) );
  }
  //printf( "%d : %d %d\n" , now , dp[ now ][ 0 ] , dp[ now ][ 1 ] );
}
void solve(){
  go( 1 , 1 );
  printf( "%d\n" , min( dp[ 1 ][ 0 ] , dp[ 1 ][ 1 ] ) );
}
int main(){
  freopen( "tour.in" , "r" , stdin );
  freopen( "tour.out" , "w" , stdout );
  init();
  solve();
}
