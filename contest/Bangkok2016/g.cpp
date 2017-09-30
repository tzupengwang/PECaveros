#include <bits/stdc++.h>
using namespace std;
//#define N 222
//int dp[ N ][ 2 ];
typedef long long LL;
const int mod = 1000000007;
int add( int a , int b ){
  a += b;
  return a >= mod ? a - mod : a;
}
int mul( LL a , int b ){
  a *= b;
  return a >= mod ? a % mod : a;
}
int sub( int a , int b ){
  a -= b;
  return a < 0 ? a + mod : a;
}
struct Mat{
  int n , v[ 10 ][ 10 ];
  Mat( int _n , int _i = 0 ){
    n = _n;
    for( int i = 0 ; i < n ; i ++ ){
      for( int j = 0 ; j < n ; j ++ )
        v[ i ][ j ] = 0;
      v[ i ][ i ] = _i;
    }
  }
  Mat operator*( const Mat& he ) const{
    assert( n == he.n );
    Mat ret( n );
    for( int i = 0 ; i < n ; i ++ )
      for( int j = 0 ; j < n ; j ++ )
        for( int k = 0 ; k < n ; k ++ )
          ret.v[ i ][ j ] = add( ret.v[ i ][ j ] ,
                                 mul( v[ i ][ k ] , he.v[ k ][ j ] ) );
    return ret;
  }
  Mat operator^( LL tk ) const{
    Mat ret( n , 1 ) , a( n );
    for( int i = 0 ; i < n ; i ++ )
      for( int j = 0 ; j < n ; j ++ )
        a.v[ i ][ j ] = v[ i ][ j ];
    while( tk ){
      if( tk & 1 ) ret = ret * a;
      a = a * a; tk >>= 1;
    }
    return ret;
  }
};
LL cal( LL nk , LL k ){
  if( nk <= 0 ) return 0;
  Mat a( 2 );
  a.v[ 0 ][ 0 ] = 1; a.v[ 0 ][ 1 ] = 1;
  a.v[ 1 ][ 0 ] = 1; a.v[ 1 ][ 1 ] = 0;
  a = a ^ k;
  LL t = nk / k;
  Mat b( 4 ) , b2( 4 );
  for( int i = 0 ; i < 2 ; i ++ )
    for( int j = 0 ; j < 2 ; j ++ ){
      b.v[ i ][ j ] = a.v[ i ][ j ];
      b.v[ i ][ j + 2 ] = a.v[ i ][ j ];
    }
  b.v[ 2 ][ 2 ] = b.v[ 3 ][ 3 ] = 1;
  for( int i = 0 ; i < 2 ; i ++ )
    for( int j = 0 ; j < 2 ; j ++ )
      b2.v[ i ][ j ] = a.v[ i ][ j ];
  b2.v[ 2 ][ 0 ] = b2.v[ 3 ][ 1 ] = 1;
  b = b ^ ( t - 1 );
  Mat r( 2 );
  for( int i = 0 ; i < 2 ; i ++ )
    for( int j = 0 ; j < 2 ; j ++ )
      for( int kk = 0 ; kk < 4 ; kk ++ )
        r.v[ i ][ j ] = add( r.v[ i ][ j ] ,
                             mul( b.v[ i ][ kk ] , b2.v[ kk ][ j ] ) );
  return add( r.v[ 0 ][ 0 ] , r.v[ 0 ][ 1 ] );
}
LL dp[ 1021 ];
int main(){
  LL l , r , k;
  int _cs = 0;
  //dp[ 0 ] = 1; dp[ 1 ] = 2;
  //for( int i = 2 ; i < 1021 ; i ++ )
    //dp[ i ] = add( dp[ i - 1 ] , dp[ i - 2 ] );
  int t; scanf( "%d" , &t ); while( t -- ){
    scanf( "%lld%lld%lld" , &l , &r , &k );
    LL ql = l / k * k;
    if( ql == l ) ql -= k;
    printf( "Case %d: %d\n" , ++ _cs , sub( cal( r / k * k , k ) , cal( ql , k ) ) );
  }
  //dp[ 1 ][ 0 ] = 1;
  //dp[ 1 ][ 1 ] = 1;
  //for( int i = 2 ; i <= 100 ; i ++ ){
    //dp[ i ][ 0 ] = dp[ i - 1 ][ 0 ] + dp[ i - 1 ][ 1 ];
    //dp[ i ][ 1 ] = dp[ i - 1 ][ 0 ];
    //printf( "%d %d\n" , i ,dp[ i ][ 0 ] + dp[ i ][ 1 ] );
  //}
}

