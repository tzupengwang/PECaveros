#include <bits/stdc++.h>
using namespace std;
#define N 303030
typedef long long LL;
const int mod = 1000000007;
int mul( LL a , LL b ){
  a *= b;
  return a >= mod ? a % mod : a;
}
int mypow( int a , int b ){
  if( b == 0 ) return 1;
  int ret = mypow( mul( a , a ) , b >> 1 );
  if( b & 1 ) ret = mul( ret , a );
  return ret;
}
int n , m;
char c[ N ];
int main(){
  while( scanf( "%d%d" , &n , &m ) == 2 ){
    scanf( "%s" , c );
    LL vl = 0 , cc = 0;
    for( int i = 0 ; i < n ; i ++ ){
      vl = ( vl * 10 + c[ i ] - '0' ) % m;
      if( vl == 0 ) cc ++;
    }
    if( vl ) puts( "0" );
    else printf( "%d\n" , mypow( 2 , cc - 1 ) );
  }
}
