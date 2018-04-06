#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = 1000000007;
inline int add( int ai , int bi ){
  ai += bi;
  return ai >= mod ? ai - mod : ai;
}
inline int sub( int ai , int bi ){
  ai -= bi;
  return ai < 0 ? ai + mod : ai;
}
inline int mul( LL ai , int bi ){
  ai *= bi;
  return ai >= mod ? ai % mod : ai;
}
inline int mpow( int ai , int bi ){
  int ret = 1;
  while( bi ){
    if( bi & 1 ) ret = mul( ret , ai );
    ai = mul( ai , ai );
    bi >>= 1;
  }
  return ret;
}
struct Mat{
  int n , a[ N ][ N ];
  Mat( int _n ){
    n = _n;
    for( int i = 0 ; i < n ; i ++ )
      for( int j = 0 ; j < n ; j ++ )
        a[ i ][ j ] = 0;
  }
  Mat operator*( const Mat& he ) const{
    Mat ret( n );
    for( int i = 0 ; i < n ; i ++ )
      for( int j = 0 ; j < n ; j ++ )
        for( int k = 0 ; k < n ; k ++ )
          ret.a[ i ][ j ] = add( ret.a[ i ][ j ] ,
              mul( a[ i ][ k ] , he.a[ k ][ j ] ) );
    return ret;
  }
  Mat operator^( LL tk ) const{
    Mat A , I;
    for( int i = 0 ; i < n ; i ++ ){
      for( int j = 0 ; j < n ; j ++ )
        A.a[ i ][ j ] = a[ i ][ j ];
      I.a[ i ][ i ] = 1;
    }
    while( tk ){
      if( tk & 1LL ) I = I * A;
      A = A * A;
      tk >>= 1;
    }
    return I;
  }
};
#define M 111
#define K 10001
int fac[ K ] , ifac[ K ] , inv[ K ];
void build(){
  fac[ 0 ] = ifac[ 0 ] = 1;
  for( int i = 1 ; i < K - 1 ; i ++ )
    fac[ i ] = mul( fac[ i - 1 ] , i );
  ifac[ K - 1 ] = mpow( fac[ K - 1 ] , mod - 2 );
  for( int i = K - 2 ; i >= 1 ; i -- )
    ifac[ i ] = mul( ifac[ i + 1 ] , i + 1 );
  inv[ 0 ] = 1;
  for( int i = 1 ; i < K ; i ++ )
    inv[ i ] = mpow( i , mod - 2 );
}
inline int C( int a , int b ){
  if( a < b ) return 0;
  return mul( fac[ a ] , mul( ifac[ b ] , ifac[ a - b ] ) );
}
int n , m , p;
int c[ M ];
void init(){
  scanf( "%d%d%d" , &n , &m , &p );
  for( int i = 0 ; i < m ; i ++ )
    scanf( "%d" , &c[ i ] );
}
int dp[ N ] , way[ N ];
bitset<K> can;
void solve(){
  go_dp();
  int g = c[ 0 ];
  for( int i = 0 ; i < m ; i ++ )
    g = __gcd( g , c[ i ] );
  if( m > 1 ){
    can.reset();
    can[ 0 ] = 1;
    for( int i = 0 ; i < m ; i ++ )
      can = can | (can << c[ i ]);
    Mat a( g );
    for( int i = 0 ; i < g ; i ++ ){
      a[ i ][ i ] = 100 - p;
      a[ i ][ (i + 1) % g ] = p;
    }
    a = a ^ n;
    for( int i = 0 ; i < g ; i ++ )
      way[ i ] = a[ 0 ][ i ];
    int cni = 1;
    int ans = 0;
    for( int i = 1 ; i < 10000 ; i ++ ){
      cni = mul( cni , n - i + 1 );
      cni = mul( cni , inv[ i ] );
      int tway = mul( cni , mpow( p , i ) );
      tway = mul( tway , mpow( 100 - p , n - i ) );
      way[ i ] = sub( way[ i ] , tway );
      if( not can[ i ] )
        ans = add( ans , mul( g - i % g , tway ) );
    }
    for( int i = 1 ; i < g ; i ++ )
      ans = add( ans , mul( g - i , way[ i ] ) );
    printf( "%d\n" , ans );
  }
}
int main(){
  build();
  int t; scanf( "%d" , &t ); while( t -- ){
    init();
    solve();
  }
}
