#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = 1000000007;
#define N 111
int fac[ N ] , ifac[ N ];
int sub( int a , int b ){
  a -= b;
  return a < 0 ? a + mod : a;
}
int mul( LL a , int b ){
  a *= b;
  return a >= mod ? a % mod : a;
}
int mpow( int a , int b ){
  if( b == 0 ) return 1;
  int ret = mpow( mul( a , a ) , b >> 1 );
  if( b & 1 ) ret = mul( ret , a );
  return ret;
}
int n , a[ N ] , b[ N ] , c[ N ];
void init(){
  cin >> n;
  for( int i = 0 ; i < n ; i ++ )
    cin >> a[ i ] >> b[ i ] >> c[ i ];
}
int _cs;
void solve(){
  int ans = 1;
  for( int i = 0 ; i < n ; i ++ ){
    int tmp = mul( mpow( a[ i ] , b[ i ] ) , sub( mpow( a[ i ] , c[ i ] - b[ i ] + 1 ) , 1 ) );
    tmp = mul( tmp , mpow( sub( a[ i ] , 1 ) , mod - 2 ) );
    if( a[ i ] == 1 ) tmp = c[ i ] - b[ i ] + 1;
    ans = mul( ans , tmp );
  }
  printf( "Case #%d: %d\n" , ++ _cs , ans );
}
int main(){
  int t; cin >> t; while( t -- ){
    init();
    solve();
  }
}
