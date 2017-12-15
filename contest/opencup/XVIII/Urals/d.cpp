#include <bits/stdc++.h>
using namespace std;
#define N 10000010
typedef long long LL;
const int mod = 1000000007;
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
int fac[ N ] , inv[ N ] , ifac[ N ];
void build(){
	inv[ 1 ] = 1;
	for( int i = 2 ; i < N ; i ++ )
		inv[ i ] = ((LL)(mod - mod / i) * inv[mod % i]) % mod;
  fac[ 0 ] = ifac[ 0 ] = 1;
  for( int i = 1 ; i < N ; i ++ ){
    fac[ i ] = mul( fac[ i - 1 ] , i );
    ifac[ i ] = mul( ifac[ i - 1 ] , inv[ i ] );
  }
}
int maxa;
inline int C( int a , int b ){
  if( a < b ) return 0;
  maxa = max( maxa , a );
  return mul( fac[ a ] , mul( ifac[ b ] , ifac[ a - b ] ) );
}
inline int H( int a , int b ){
  return C( a + b - 1 , b - 1 );
}
unordered_map< LL , int > dp;
inline int calc( int n , int c ){
  if( c < 0 ) return 0;
  LL hs = (((LL)n) << 32) | c;
  auto it = dp.find( hs );
  if( it != dp.end() ) return it->second;
  int ret = 0;
  for( int i = 0 ; c - i * 10 >= 0 and i <= n ; i ++ ){
    //cerr << n << " " << i << " " << c - i * 10 << " " << n << endl;
    int tmp = mul( C( n , i ) , H( c - i * 10 , n ) );
    if( i & 1 ) ret = sub( ret , tmp );
    else ret = add( ret , tmp );
  }
  //cerr << n << " " << c << " " << ret << endl;
  return dp[ hs ] = ret;
}
int n;
int main(){
  build();
  scanf( "%d" , &n );
  if( n & 1 ){
    int hf = n / 2 , n2 = hf / 2;
    int ans = 0;
    if( n % 4 == 3 ){
      for( int i = 0 ; i < 5 ; i ++ )
        ans = add( ans , calc( hf , 9 * n2 + i ) );
    }else{
      for( int i = 0 ; i < 5 ; i ++ )
        ans = add( ans , calc( hf , 9 * n2 - i ) );
    }
    printf( "%d\n" , ans );
  }else{
    int ans = 1;
    for( int i = 1 ; i <= n / 2 ; i ++ )
      ans = mul( ans , 10 );
    printf( "%d\n" , ans );
  }
  //cerr << maxa << endl;
}
