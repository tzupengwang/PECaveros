#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 101010
const int mod = 998244353;
inline int add( int a , int b ){
  a += b;
  return a >= mod ? a - mod : a;
}
inline int sub( int a , int b ){
  a -= b;
  return a < 0 ? a + mod : a;
}
inline int mul( LL a , int b ){
  a *= b;
  return a >= mod ? a % mod : a;
}
#define sN 345
int n , h0 , a[ N ] , dp[ N ];
void init(){
  scanf( "%d%d" , &n , &h0 );
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%d" , &a[ i ] );
  dp[ n ] = 1;
}
void solve(){
  for( int i = n - 1 ; i >= 1 ; i -- )
    for( int j = i + a[ i ] ; j <= n ; j += a[ i ] ){
      dp[ i ] = add( dp[ i ] , dp[ j ] );
      if( a[ j ] == a[ i ] ) break;
    }
  int ans = 0;
  if( h0 == a[ 1 ] ) ans = dp[ 1 ];
  else{
    for( int i = 1 ; i <= n ; i += h0 ){
      ans = add( ans , dp[ i ] );
      if( i > 1 and a[ i ] == h0 ) break;
    }
  }
  cout << ans << endl;
}
int main(){
  init();
  solve();
}
