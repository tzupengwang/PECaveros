#include <bits/stdc++.h>
using namespace std;
#define N 514
#define MSK (1 << 6)
#define INF (N * MSK)
int cb[ MSK ];
int n , bst[ N ];
char buf[ 9 ];
int dp[ 2 ][ MSK ] , vl[ MSK ];
inline int cost( int from , int to ){
  return cb[ to & (~from) ];
}
int main(){
  for( int i = 0 ; i < MSK ; i ++ )
    cb[ i ] = __builtin_popcount( i );
  for( int i = 0 ; i < MSK ; i ++ )
    for( int j = 0 ; j < 6 ; j ++ )
      if( (i >> j) & 1 )
        vl[ i ] += j + 1;
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ ){
    scanf( "%s" , buf );
    int mx = 0;
    for( int j = 0 ; j < 7 ; j ++ )
      mx = max( mx , (int)( buf[ j ] - '0' ) );
    for( int j = 0 ; j < 7 ; j ++ )
      if( mx == (int)( buf[ j ] - '0' ) )
        bst[ i ] |= (1 << j);
  }
  for( int j = 0 ; j < MSK ; j ++ )
    dp[ 0 ][ j ] = INF;
  dp[ 0 ][ 0 ] = 0;
  for( int i = 0 ; i < n ; i ++ ){
    int now = i & 1 , nxt = 1 - now;
    for( int j = 0 ; j < MSK ; j ++ )
      dp[ nxt ][ j ] = INF;
    for( int j = 0 ; j < MSK ; j ++ ){
      if( dp[ now ][ j ] == INF ) continue;
      for( int k = 0 ; k < MSK ; k ++ ){
        int s = vl[ k ] % 7;
        if( ( bst[ i ] >> s ) & 1 )
          dp[ nxt ][ k ] = min( dp[ nxt ][ k ] ,
                                dp[ now ][ j ] + cost( j , k ) );
      }
    }
  }
  int ans = INF;
  for( int i = 0 ; i < MSK ; i ++ )
    ans = min( ans , dp[ n & 1 ][ i ] );
  cout << ans << endl;
}
