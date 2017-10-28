#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = 1000000007;
#define N 2020202
int fac[ N ] , ifac[ N ];
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
inline int C( int a , int b ){
  if( a < b ) return 0;
  return mul( fac[ a ] , mul( ifac[ b ] , ifac[ a - b ] ) );
}
int main(){
  fac[ 0 ] = ifac[ 0 ] = 1;
  for( int i = 1 ; i < N ; i ++ ){
    fac[ i ] = mul( fac[ i - 1 ] , i );
    ifac[ i ] = mpow( fac[ i ] , mod - 2 );
  }
  int _cs = 0;
  int t; cin >> t; while( t -- ){
    int n , m;
    cin >> n >> m;
    for( int i = 0 , x ; i < n ; i ++ ){
      int s; cin >> s; while( s -- ) cin >> x;
    }
    printf( "Case #%d: %d\n" , ++ _cs , C( m - 1 , n - 1 ) );
  }
}
