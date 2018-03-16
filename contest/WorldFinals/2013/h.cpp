#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 514
int n , a[ N ] , cnt[ N ];
bool ok[ N ][ N ];
int mn[ N ][ N ];
int con[ N ][ N ];
int dp[ N ][ N ];
bool gt[ N ][ N ];
int Con( int vl , int l , int r ){
  return con[ vl ][ r ] - con[ vl ][ l - 1 ];
}
int DP( int l , int r ){
  if( l == r ) return 0;
  if( gt[ l ][ r ] ) return dp[ l ][ r ];
  gt[ l ][ r ] = true;
  int bst = -1;
  for( int i = l ; i < r ; i ++ ){
    int ldp = DP( l , i );
    int rdp = DP( i + 1 , r );
    int cur = ldp + rdp;
    if( mn[ l ][ i ] < mn[ i + 1 ][ r ] )
      cur += r - l + 1 - Con( mn[ i + 1 ][ r ] - 1 , l , i );
    else
      cur += r - l + 1 - Con( mn[ l ][ i ] - 1 , i + 1 , r );
    if( bst == -1 or cur < bst )
      bst = cur;
  }
  return dp[ l ][ r ] = bst;
}
int dp2[ N ];
int main(){
  cin >> n;
  for( int i = 1 ; i <= n ; i ++ )
    cin >> a[ i ];
  for( int i = 1 ; i <= n ; i ++ ){
    con[ a[ i ] ][ i ] ++;
    for( int j = 0 ; j < N ; j ++ )
      cnt[ j ] = 0;
    for( int j = i , mx = 0 , tmn = N ; j <= n ; j ++ ){
      if( cnt[ a[ j ] ] ) break;
      cnt[ a[ j ] ] = 1;
      mx = max( mx , a[ j ] );
      tmn = min( tmn , a[ j ] );
      mn[ i ][ j ] = tmn;
      if( mx == j - i + 1 )
        ok[ i ][ j ] = true;
    }
  }
  for( int i = 0 ; i < N ; i ++ )
    for( int j = 0 ; j < N ; j ++ ){
      if( i ) con[ i ][ j ] += con[ i - 1 ][ j ];
      if( j ) con[ i ][ j ] += con[ i ][ j - 1 ];
      if( i and j )
        con[ i ][ j ] -= con[ i - 1 ][ j - 1 ];
    }
  for( int i = 1 ; i <= n ; i ++ )
    dp2[ i ] = -1;
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= i ; j ++ )
      if( ok[ j ][ i ] and dp2[ j - 1 ] != -1 ){
        int ret = DP( j , i ) + dp2[ j - 1 ];
        if( dp2[ i ] == -1 or ret < dp2[ i ] )
          dp2[ i ] = ret;
      }
  if( dp2[ n ] == -1 )
    puts( "impossible" );
  else
    printf( "%d\n" , dp2[ n ] );
}
