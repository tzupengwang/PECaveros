#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define lgN 22
#define N (1 << 20)
int n , k;
int nxt[ lgN ][ N << 2 ];
vector<int> to[ N ];
int main( ){
  scanf( "%d%d" , &n , &k );
  int bst = 0;
  for( int i = 0 ; i < k ; i ++ ){
    int li , ri;
    scanf( "%d%d" , &li , &ri );
    if( ri < li ){
      bst = max( bst , ri );
      ri += n;
    }
    to[ li ].push_back( ri );
  }
  for( int i = 1 ; i <= n ; i ++ ){
    for( int x : to[ i ] )
      bst = max( bst , x );
    if( bst < i ) continue;
    int mr = bst - i;
    for( int j = 0 ; j < 3 ; j ++ ){
      int nto = min( n + n + n + 1 , j * n + i + mr + 1 );
      nxt[ 0 ][ j * n + i ] = nto;
    }
  }
  for( int j = 0 ; j < lgN ; j ++ )
    nxt[ j ][ n + n + n + 1 ] = n + n + n + 1;
  for( int j = 1 ; j < lgN ; j ++ )
    for( int i = 1 ; i <= n + n + n ; i ++ )
      nxt[ j ][ i ] = nxt[ j - 1 ][ nxt[ j - 1 ][ i ] ];
  int ans = N + N;
  for( int i = 1 ; i <= n ; i ++ ){
    if( nxt[ lgN - 1 ][ i ] == 0 ) continue;
    int tans = 0 , cur = i , nd = i + n;
    for( int j = lgN - 1 ; j >= 0 ; j -- )
      if( nxt[ j ][ cur ] < nd ){
        tans |= (1 << j);
        cur = nxt[ j ][ cur ];
      }
    ans = min( ans , tans + 1 );
  }
  if( ans > n )
    puts( "impossible" );
  else
    printf( "%d\n" , ans );
}
