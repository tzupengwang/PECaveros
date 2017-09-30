#include <bits/stdc++.h>
using namespace std;
const int mod = 1000000007;
typedef long long LL;
int add( int a , int b ){
  a += b;
  return a >= mod ? a - mod : a;
}
int sub( int a , int b ){
  a -= b;
  return a < 0 ? a + mod : a;
}
int mul( LL a , int b ){
  a *= b;
  return a >= mod ? a % mod : a;
}
int n , s;
#define N 66
#define X 222
int dp[ N ][ N * X ];
int pdp[ N ][ N * X ];
int main(){
  while( scanf( "%d%d" , &n , &s ) == 2 && n ){
    for( int j = 0 ; j <= n * s ; j ++ )
      dp[ 0 ][ j ] = 0;
    dp[ 0 ][ 0 ] = 1;
    for( int j = 0 ; j <= n * s ; j ++ ){
      pdp[ 0 ][ j ] = dp[ 0 ][ j ];
      if( j )
        pdp[ 0 ][ j ] = add( pdp[ 0 ][ j ] , pdp[ 0 ][ j - 1 ] );
    }
    for( int i = 1 ; i <= n - 1 ; i ++ ){
      for( int j = 0 ; j <= n * s ; j ++ ){
        dp[ i ][ j ] = pdp[ i - 1 ][ j ];
        if( j - s > 0 )
          dp[ i ][ j ] = sub( dp[ i ][ j ] , pdp[ i - 1 ][ j - s - 1 ] );
        pdp[ i ][ j ] = dp[ i ][ j ];
        if( j )
          pdp[ i ][ j ] = add( pdp[ i ][ j ] , pdp[ i ][ j - 1 ] );
      }
    }
    int ans = 0;
    for( int i = 0 ; i <= s ; i ++ )
      ans = add( ans , dp[ n - 1 ][ i * n - i ] );
    ans = mul( ans , n );
    printf( "%d\n" , ans );
  }
}
