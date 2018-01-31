#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = 1000000009;
#define N 333
int n , k;
int dp[ N ][ N ][ 2 ];
int main(){
  cin >> n >> k;
  if( k == 0 )
    dp[ 0 ][ 0 ][ 1 ] = 1;
  else
    dp[ 0 ][ 0 ][ 0 ] = 1;
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j <= i ; j ++ )
      for( int g = 0 ; g < 2 ; g ++ ){
        if( dp[ i ][ j ][ g ] == 0 ) continue;
        dp[ i + 1 ][ j ][ g ] = (dp[ i + 1 ][ j ][ g ] + dp[ i ][ j ][ g ]) % mod;
        if( j + 1 <= k ){
          int ng = g;
          if( j + 1 == k ) ng = 1;
          dp[ i + 1 ][ j + 1 ][ ng ] = (dp[ i + 1 ][ j + 1 ][ ng ] + dp[ i ][ j ][ g ]) % mod;
        }
        if( j )
          dp[ i + 1 ][ j - 1 ][ g ] = (dp[ i + 1 ][ j - 1 ][ g ] + dp[ i ][ j ][ g ]) % mod;
      }
  cout << dp[ n ][ 0 ][ 1 ] << endl;
}
