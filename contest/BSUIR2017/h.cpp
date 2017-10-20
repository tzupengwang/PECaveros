#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 111
char s[ N ] , t[ N ];
int k , lens , lent;
inline void better( int& x , int y ){
  if( x < 0 or y < x ) x = y;
}
int dp[ 2 ][ N ][ N ][ N ];
int main(){
  scanf( "%d" , &k );
  scanf( "%s" , s + 1 );
  lens = strlen( s + 1 );
  scanf( "%s" , t + 1 );
  lent = strlen( t + 1 );
  memset( dp , -1 , sizeof dp );
  dp[ 0 ][ 0 ][ 0 ][ 0 ] = 0;
  int ans = -1;
  for( int i = 0 ; i <= lens ; i ++ ){
    int now = i & 1 , nxt = 1 - now;
    memset( dp[ nxt ] , -1 , sizeof dp[ nxt ] );
    for( int li = i ; li >= 0 ; li -- )
      for( int j = 0 ; j <= lent ; j ++ )
        for( int lj = 0 ; lj <= j ; lj ++ ){
          if( dp[ now ][ li ][ j ][ lj ] < 0 ) continue;
          //printf( "%d %d %d %d -> %d\n" , i , li , j , lj ,
                  //dp[ now ][ li ][ j ][ lj ] );
          if( i < lens and j < lent and s[ i + 1 ] == t[ j + 1 ] ){
            better( dp[ nxt ][ li + 1 ][ j + 1 ][ lj + 1 ] ,
                    dp[ now ][ li ][ j ][ lj ] + 1 );
          }
          if( ( li >= k or li == 0 ) and j < lent ){
            better( dp[ now ][ 0 ][ j + 1 ][ lj + 1 ] ,
                    dp[ now ][ li ][ j ][ lj ] + 1 );
          }
          if( ( lj >= k or lj == 0 ) and i < lens ){
            better( dp[ nxt ][ li + 1 ][ j ][ 0 ] ,
                    dp[ now ][ li ][ j ][ lj ] + 1 );
          }
          if( i == lens and j == lent and
              ( li >= k or li == 0 ) and
              ( lj >= k or lj == 0 ) )
            better( ans , dp[ now ][ li ][ j ][ lj ] );
        }
  }
  printf( "%d\n" , ans );
}
