#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long double LD;
#define N 201010
LD cans;
int n , d[ N ];
inline LD sqr( LD x ){
  return x * x;
}
inline LD cal( LD s ){
  LD ret = 0;
  for( int i = 0 ; i < n ; i ++ )
    ret += sqrtl( 1. + sqr( s + i - d[ i ] ) );
  return ret;
}
int main(){
  scanf( "%d" , &n );
  //n = 100000;
  n <<= 1;
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%d" , &d[ i ] );
    //d[ i ] = (long long)rand() * rand() % 2000000;
  sort( d , d + n );
  LD bl = -3e6 , br = 3e6;
  cans = 1e20;
  for( int i = 0 ; i < 150 ; i ++ ){
    LD mid1 = (bl + bl + br) / 3; 
    LD mid2 = (bl + br + br) / 3; 
    LD lc = cal( mid1 );
    LD rc = cal( mid2 );
    if( lc < rc ){
      cans = min( cans , lc );
      br = mid2;
    }else{
      cans = min( cans , rc );
      bl = mid1;
    }
  }
  printf( "%.12f\n" , (double)cans );
}
