#include <bits/stdc++.h>
using namespace std;
#define N 402020
typedef long long LL;
const int mod = 1000003;
int mul( LL a , LL b ){
  a *= b;
  return a >= mod ? a % mod : a;
}
int add( int a , int b ){
  a += b;
  return a >= mod ? a - mod : a;
}
int sub( int a , int b ){
  a -= b;
  return a < 0 ? a + mod : a;
}
int mypow( int a , int b ){
  if( b == 0 ) return 1;
  int ret = mypow( mul( a , a ) , b >> 1 );
  if( b & 1 ) ret = mul( ret , a );
  return ret;
}
int n , a , b , c;
int row[ N ] , col[ N ];
int fac[ N ] , ifac[ N ];
void build(){
  fac[ 0 ] = ifac[ 0 ] = 1;
  for( int i = 1 ; i < N ; i ++ ){
    fac[ i ] = mul( fac[ i - 1 ] , i );
    ifac[ i ] = mypow( fac[ i ] , mod - 2 );
  }
}
inline int C( int x , int y ){
  return mul( fac[ x ] , mul( ifac[ y ] , ifac[ x - y ] ) );
}
int aa[ N ] , bb[ N ];
void solve1(){
  int ans = 0;
  for( int i = 1 ; i < n ; i ++ ){
    row[ i ] = sub( row[ i ] , mul( i , c ) );
    col[ i ] = sub( col[ i ] , mul( i , c ) );
    {
      int da = n - 1 - i , db = n - 2;
      int way = C( da + db , da );
      way = mul( way , aa[ da ] );
      way = mul( way , bb[ db ] );
      ans = add( ans , mul( mul( row[ i ] , b ) , way ) );
    }
    {
      int da = n - 2 , db = n - 1 - i;
      int way = C( da + db , da );
      way = mul( way , aa[ da ] );
      way = mul( way , bb[ db ] );
      ans = add( ans , mul( mul( col[ i ] , a ) , way ) );
    }
  }
  ans = add( ans , mul( n + n - 2 , c ) );
  printf( "%d\n" , ans );
}
void solve2(){
  int dlt = mul( c , mypow( sub( add( a , b ) , 1 ) , mod - 2 ) );
  int ans = 0;
  for( int i = 1 ; i < n ; i ++ ){
    row[ i ] = add( row[ i ] , dlt );
    col[ i ] = add( col[ i ] , dlt );
    {
      int da = n - 1 - i , db = n - 2;
      int way = C( da + db , da );
      way = mul( way , aa[ da ] );
      way = mul( way , bb[ db ] );
      ans = add( ans , mul( mul( row[ i ] , b ) , way ) );
    }
    {
      int da = n - 2 , db = n - 1 - i;
      int way = C( da + db , da );
      way = mul( way , aa[ da ] );
      way = mul( way , bb[ db ] );
      ans = add( ans , mul( mul( col[ i ] , a ) , way ) );
    }
  }
  ans = sub( ans , dlt );
  printf( "%d\n" , ans );
}
int main(){
  build();
  while( scanf( "%d%d%d%d" , &n , &a , &b , &c ) == 4 ){
    for( int i = 0 ; i < n ; i ++ )
      scanf( "%d" , &col[ i ] );
    for( int i = 0 ; i < n ; i ++ )
      scanf( "%d" , &row[ i ] );
    aa[ 0 ] = bb[ 0 ] = 1;
    for( int i = 1 ; i <= n ; i ++ ){
      aa[ i ] = mul( aa[ i - 1 ] , a );
      bb[ i ] = mul( bb[ i - 1 ] , b );
    }
    if( add( a , b ) == 1 )
      solve1();
    else
      solve2();
  }
}
