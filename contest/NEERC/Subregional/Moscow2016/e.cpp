#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 202020
int leng( int x ){
  int cnt = 0;
  while( x )
    cnt ++ , x /= 10;
  return cnt;
}
int n , a[ N ];
void init(){
  scanf( "%d" , &n );
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%d" , &a[ i ] );
  sort( a + 1 , a + n + 1 );
}
inline int Cost( const pair<int,int>& pp ){
  if( pp.first == pp.second )
    return leng( pp.first );
  return leng( pp.first ) + leng( pp.second ) + 1;
}
vector< pair<pair<int,int>,int> > dp[ N ][ 3 ][ 3 ];
int tlen[ N ][ 3 ][ 3 ];
void solve(){
  for( int i = 0 ; i < 3 ; i ++ )
    for( int j = 0 ; j < 3 ; j ++ )
      if( i || j )
        tlen[ 0 ][ i ][ j ] = N * 20;
  for( int i = 1 ; i <= n ; i ++ ){
    for( int j = 0 ; j < 3 ; j ++ )
      for( int k = 0 ; k < 3 ; k ++ )
        tlen[ i ][ j ][ k ] = N * 20;
    for( int j = 0 ; j < 3 ; j ++ )
      for( int k = 0 ; k < 3 ; k ++ ){
        if( tlen[ i - 1 ][ j ][ k ] == N * 20 )
          continue;
        int xlen = tlen[ i - 1 ][ j ][ k ] + 1 +
                   Cost( { a[ i ] , a[ i ] } );
        //printf( "%d %d %d -> %d\n" , i - 1 , j , k , tlen[ i - 1 ][ j ][ k ] );
        if( xlen < tlen[ i ][ k ][ 0 ] ){
          tlen[ i ][ k ][ 0 ] = xlen;
          dp[ i ][ k ][ 0 ] = dp[ i - 1 ][ j ][ k ];
          dp[ i ][ k ][ 0 ].push_back( { { a[ i ] , a[ i ] } , 0 } );
        }
        if( i > 1 && a[ i ] == a[ i - 1 ] + 1 && ( k == 0 || k == 1 ) ){
          xlen = tlen[ i - 1 ][ j ][ k ] -
                      Cost( dp[ i - 1 ][ j ][ k ].back().first );
          int lft = dp[ i - 1 ][ j ][ k ].back().first.first;
          int rgt = a[ i ];
          xlen += Cost( { lft , rgt } );
          if( xlen <= tlen[ i ][ k ][ 1 ] ){
            tlen[ i ][ k ][ 1 ] = xlen;
            dp[ i ][ k ][ 1 ] = dp[ i - 1 ][ j ][ k ];
            dp[ i ][ k ][ 1 ].back().first.second = a[ i ];
          }
        }
        if( i > 1 && a[ i ] == a[ i - 1 ] + 2 && ( k == 0 || k == 2 ) ){
          xlen = tlen[ i - 1 ][ j ][ k ] -
                      Cost( dp[ i - 1 ][ j ][ k ].back().first );
          int lft = dp[ i - 1 ][ j ][ k ].back().first.first;
          int rgt = a[ i ];
          xlen += Cost( { lft , rgt } );
          if( xlen <= tlen[ i ][ k ][ 2 ] ){
            tlen[ i ][ k ][ 2 ] = xlen;
            dp[ i ][ k ][ 2 ] = dp[ i - 1 ][ j ][ k ];
            dp[ i ][ k ][ 2 ].back().first.second = a[ i ];
            dp[ i ][ k ][ 2 ].back().second = 2;
          }
        }
        if( i > 2 && a[ i ] == a[ i - 2 ] + 2 && ( j == 0 || j == 2 ) && ( k == 0 || k == 2 ) ){
          int sz = (int)dp[ i - 1 ][ j ][ k ].size();
          xlen = tlen[ i - 1 ][ j ][ k ] -
                      Cost( dp[ i - 1 ][ j ][ k ][ sz - 2 ].first );
          int lft = dp[ i - 1 ][ j ][ k ][ sz - 2 ].first.first;
          int rgt = a[ i ];
          xlen += Cost( { lft , rgt } );
          if( xlen <= tlen[ i ][ k ][ 2 ] ){
            tlen[ i ][ k ][ 2 ] = xlen;
            dp[ i ][ k ][ 2 ] = dp[ i - 1 ][ j ][ k ];
            swap( dp[ i ][ k ][ 2 ][ sz - 2 ] , dp[ i ][ k ][ 2 ][ sz - 1 ] );
            dp[ i ][ k ][ 2 ].back().first.second = a[ i ];
            dp[ i ][ k ][ 2 ].back().second = 1;
          }
        }
      }
    for( int j = 0 ; j < 3 ; j ++ )
      for( int k = 0 ; k < 3 ; k ++ )
        dp[ i - 1 ][ j ][ k ].clear();
  }
  int bsti = 0 , bstj = 0;
  for( int i = 0 ; i < 3 ; i ++ )
    for( int j = 0 ; j < 3 ; j ++ )
      if( tlen[ n ][ i ][ j ] < tlen[ n ][ bsti ][ bstj ] )
        bsti = i , bstj = j;
  for( size_t i = 0 ; i < dp[ n ][ bsti ][ bstj ].size() ; i ++ ){
    if( i ) putchar( ',' );
    auto pp = dp[ n ][ bsti ][ bstj ][ i ].first;
    auto qq = dp[ n ][ bsti ][ bstj ][ i ].second;
    if( pp.first == pp.second )
      printf( "%d" , pp.first );
    else{
      printf( "%d" , pp.first );
      if( qq ) printf( "%c" , "%#"[ pp.first % 2 ] );
      else putchar( '-' );
      printf( "%d" , pp.second );
    }
  }
  puts( "" );
}
int main(){
  init();
  solve();
}
