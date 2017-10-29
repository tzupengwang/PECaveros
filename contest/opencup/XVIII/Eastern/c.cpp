#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 111
char c[ 4 ][ N ];
#define X 1010101
int cnt[ X ] , ord[ 4 ] , len[ 4 ];
long long ans;
void cal(){
  fill( cnt , cnt + X , 0 );
  int a1 = ord[ 0 ] , a2 = ord[ 1 ];
  int b1 = ord[ 2 ] , b2 = ord[ 3 ];
  for( int i = 0 ; i < len[ a1 ] ; i ++ )
    for( int j = i + 2 ; j < len[ a1 ] ; j ++ ){
      int dlt = j - i;
      for( int k = 0 ; k + dlt < len[ a2 ] ; k ++ ){
        int cc[ 4 ];
        cc[ 0 ] = c[ a1 ][ i ] - 'a';
        cc[ 1 ] = c[ a1 ][ j ] - 'a';
        cc[ 2 ] = c[ a2 ][ k ] - 'a';
        cc[ 3 ] = c[ a2 ][ k + dlt ] - 'a';
        int hs = 0;
        for( int u = 0 ; u < 4 ; u ++ )
          hs = hs* 26 + cc[ u ];
        cnt[ hs ] ++;
      }
    }
  for( int i = 0 ; i < len[ b1 ] ; i ++ )
    for( int j = i + 2 ; j < len[ b1 ] ; j ++ ){
      int dlt = j - i;
      for( int k = 0 ; k + dlt < len[ b2 ] ; k ++ ){
        int cc[ 4 ];
        cc[ 0 ] = c[ b1 ][ i ] - 'a';
        cc[ 2 ] = c[ b1 ][ j ] - 'a';
        cc[ 1 ] = c[ b2 ][ k ] - 'a';
        cc[ 3 ] = c[ b2 ][ k + dlt ] - 'a';
        int hs = 0;
        for( int u = 0 ; u < 4 ; u ++ )
          hs = hs* 26 + cc[ u ];
        ans += cnt[ hs ];
      }
    }
}
int main(){
  for( int i = 0 ; i < 4 ; i ++ ){
    scanf( "%s" , c[ i ] );
    len[ i ] = strlen( c[ i ] );
    ord[ i ] = i;
  }
  do cal();
  while( next_permutation( ord , ord + 4 ) );
  printf( "%lld\n" , ans );
}
