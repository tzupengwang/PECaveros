#include <bits/stdc++.h>
using namespace std;
#define N 50505
int n , c[ N ] , cs;
void init(){
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%d" , &c[ i ] );
}
int dp[ N ];
inline int greedy( int x ){
  int cnt = 0;
  for( int i = n - 1 ; i >= 0 ; i -- ){
    if( x < c[ i ] ) continue;
    cnt += ( x / c[ i ] );
    x %= c[ i ];
  }
  return cnt;
}
inline bool okay(){
  for( int i = 1 ; i < N ; i ++ ){
    dp[ i ] = i;
    for( int j = 0 ; j < n ; j ++ ){
      if( c[ j ] > i ) break;
      dp[ i ] = min( dp[ i ] , dp[ i - c[ j ] ] + 1 );
    }
    if( dp[ i ] < greedy( i ) )
      return false;
  }
  return true;
}
void solve(){
  printf( "Case #%d: " , ++ cs );
  if( c[ 0 ] != 1 ) puts( "Cannot pay some amount" );
  else if( !okay() ) puts( "Cannot use greedy algorithm" );
  else puts( "OK" );
}
int main(){
  while( scanf( "%d" , &n ) == 1 && n ){
    init();
    solve();
  }
}
