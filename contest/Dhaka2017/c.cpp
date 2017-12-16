#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 5050505
bool _p[ N ];
vector<int> pset;
const int mod = 100000007;
inline int sub( int a , int b ){
  a -= b;
  return a < 0 ? a + mod : a;
}
inline int add( int a , int b ){
  a += b;
  return a >= mod ? a - mod : a;
}
inline int mul( LL a , int b ){
  a *= b;
  return a >= mod ? a % mod : a;
}
inline int mpow( int a , int b ){
  if( !b ) return 1;
  int ret = mpow( mul( a , a ) , b >> 1 );
  if( b & 1 ) ret = mul( ret , a );
  return ret;
}
inline int inv( int x ){
  return mpow( x , mod - 2 );
}
inline int modit( LL x ){
  return (x % mod + mod) % mod;
}
int n;
int cal(){
  int ret = 0;
  ret = add( ret , mul( n , mpow( 2 , n - 1 ) ) );
  if( n >= 2 )
    ret = add( ret , mul( 7 , mul( n , mul( n - 1 , mpow( 2 , n - 2 ) ) ) ) );
  if( n >= 3 )
    ret = add( ret , mul( 6 , mul( n , mul( mul( n - 1 , n - 2 ) , mpow( 2 , n - 3 ) ) ) ) );
  if( n >= 4 )
    ret = add( ret , mul( n - 3 , mul( n , mul( mul( n - 1 , n - 2 ) , mpow( 2 , n - 4 ) ) ) ) );
  return ret;
}
int main(){
  while( scanf( "%d" , &n ) == 1 && n )
    printf( "%d\n" , cal() );
}
