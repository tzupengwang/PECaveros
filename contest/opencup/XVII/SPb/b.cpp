#include <bits/stdc++.h>
using namespace std;
#define N 101010
int n , p[ N ] , pp[ N ];
void init(){
  scanf( "%d" , &n );
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%d" , &p[ i ] );
    pp[ i ] = p[ i ] / 100;
  }
}
int dp[ 101 ][ N ];
int bk[ 101 ][ N ];
void go( int pn , int pb ){
  if( pn == 0 ) return;
  go( pn - 1 , bk[ pn ][ pb ] );
  int dlt = pb - bk[ pn ][ pb ];
  printf( "%d + %d\n" , p[ pn ] - dlt , dlt );
}
void solve(){
  for( int i = 0 ; i <= n ; i ++ )
    for( int j = 0 ; j < N ; j ++ )
      dp[ i ][ j ] = -1;
  dp[ 0 ][ 0 ] = 0;
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < N ; j ++ ){
      if( dp[ i ][ j ] == -1 ) continue;
      {
        int bns = dp[ i ][ j ] + pp[ i + 1 ];
        if( bns > dp[ i + 1 ][ j ] ){
          dp[ i + 1 ][ j ] = bns;
          bk[ i + 1 ][ j ] = j;
        }
      }
      {
        int pay = min( dp[ i ][ j ] , p[ i + 1 ] );
        int nxtj = j + pay;
        int res = dp[ i ][ j ] - pay;
        if( res > dp[ i + 1 ][ nxtj ] ){
          dp[ i + 1 ][ nxtj ] = res;
          bk[ i + 1 ][ nxtj ] = j;
        }
      }
    }
  int bst = -1;
  for( int i = 0 ; i < N ; i ++ ){
    if( dp[ n ][ i ] == -1 ) continue;
    bst = i;
  }
  int sum = accumulate( p + 1 , p + n + 1 , 0 );
  printf( "%d\n" , sum - bst );
  go( n , bst );
}
int main(){
  init();
  solve();
}
