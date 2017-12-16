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
void build(){
  for( int i = 2 ; i < N ; i ++ ) if( !_p[ i ] ){
    pset.push_back( i );
    for( int j = i ; j < N ; j += i )
      _p[ j ] = true;
  }
}
int n , inv2 , inv6;
int cal(){
  int ret = 1;
  for( int prm : pset ){
    if( prm > n ) break;
    int tans = 0;
    for( LL p = prm ; p <= n ; p *= prm ){
      LL k = n / p;
      int tmp = mul( n , k );
      int a1 = mul( mul( p , mul( k , k + 1 ) ) , inv2 );
      int a3 = k;
      tmp = sub( tmp , sub( a1 , a3 ) );
      tans = add( tans , tmp );
    }
    ret = mul( ret , add( tans , 1 ) );
  }
  return ret;
}
int main(){
  build();
  inv2 = inv( 2 );
  inv6 = inv( 6 );
  while( scanf( "%d" , &n ) == 1 && n )
    printf( "%d\n" , cal() );
}
