#include <bits/stdc++.h>
using namespace std;
#define N 55
int mod;
int add( int a , int b ){
  a += b;
  return a >= mod ? a - mod : a;
}
int mul( int a , int b ){
  a *= b;
  return a >= mod ? a % mod : a;
}
struct Mat{
  int d , a[ N ][ N ];
  Mat( int _d ){
    d = _d;
    for( int i = 0 ; i < d ; i ++ )
      for( int j = 0 ; j < d ; j ++ )
        a[ i ][ j ] = 0;
  }
  Mat operator*( const Mat& he ) const{
    Mat ret( d );
    for( int i = 0 ; i < d ; i ++ )
      for( int j = 0 ; j < d ; j ++ )
        for( int k = 0 ; k < d ; k ++ )
          ret.a[ i ][ j ] = add( ret.a[ i ][ j ] , 
                                 mul( a[ i ][ k ] , he.a[ k ][ j ] ) );
    return ret;
  }
  Mat operator^( int tms ) const{
    Mat I( d ) , A( d );
    for( int i = 0 ; i < d ; i ++ ){
      I.a[ i ][ i ] = 1;
      for( int j = 0 ; j < d ; j ++ )
        A.a[ i ][ j ] = a[ i ][ j ];
    }
    while( tms ){
      if( tms & 1 ) I = I * A;
      A = A * A;
      tms >>= 1;
    }
    return I;
  }
};
int n , a , b , c , T;
int s[ N ] , v[ 3 ] , ans[ N ];
bool solve(){
  cin >> n >> mod >> a >> b >> c >> T;
  int sum = n + mod + a + b + c + T;
  if( sum == 0  ) return false;
  for( int i = 0 ; i < n ; i ++ )
    cin >> s[ i ];
  v[ 0 ] = a;
  v[ 1 ] = b;
  v[ 2 ] = c;
  Mat tmp( n );
  for( int i = 0 ; i < n ; i ++ )
    for( int j = -1 ; j <= 1 ; j ++ ){
      int ss = i + j;
      if( ss < 0 or ss >= n ) continue;
      tmp.a[ i ][ ss ] = v[ j + 1 ];
    }
  tmp = tmp ^ T;
  for( int i = 0 ; i < n ; i ++ )
    ans[ i ] = 0;
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      ans[ i ] = add( ans[ i ] , mul( tmp.a[ i ][ j ] , s[ j ] ) );
  for( int i = 0 ; i < n ; i ++ )
    printf( "%d%c" , ans[ i ] , " \n"[ i + 1 == n ] );
  return true;
}
int main(){
  while( solve() );
}
