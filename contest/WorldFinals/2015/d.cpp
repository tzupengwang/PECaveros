#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 10101
const double eps = 1e-9;
const double pi = acos( -1. );
int n;
double r[ N ] , x[ N ] , y[ N ] , z[ N ];
int s;
double F( int id , double lz , double rz ){
  double tlz = z[ id ] - r[ id ];
  double trz = z[ id ] + r[ id ];
  tlz = max( tlz , lz );
  trz = min( trz , rz );
  if( tlz > trz ) return 0;
  double z1[ 4 ] , z2[ 4 ];
  z1[ 0 ] = z2[ 0 ] = 1;
  for( int i = 1 ; i < 4 ; i ++ ){
    z1[ i ] = z1[ i - 1 ] * tlz;
    z2[ i ] = z2[ i - 1 ] * trz;
  }
  return pi * ( r[ id ] * r[ id ] * ( z2[ 1 ] - z1[ 1 ] ) +
                - ( z2[ 3 ] - z1[ 3 ] ) / 3. 
                - ( z[ id ] * z[ id ] ) * ( z2[ 1 ] - z1[ 1 ] )
                + z[ id ] * ( z2[ 2 ] - z1[ 2 ] ) );
}
double f( double lz , double rz ){
  double ret = (rz - lz) * 100. * 100.;
  for( int i = 0 ; i < n ; i ++ )
    ret -= F( i , lz , rz );
  return ret;
}
int main(){
  scanf( "%d%d" , &n , &s );
  double tot = 1e6;
  for( int i = 0 ; i < n ; i ++ ){
    scanf( "%lf%lf%lf%lf" , &r[ i ] , &x[ i ] , &y[ i ] , &z[ i ] );
    r[ i ] /= 1000.;
    x[ i ] /= 1000.;
    y[ i ] /= 1000.;
    z[ i ] /= 1000.;
    tot -= pi * r[ i ] * r[ i ] * r[ i ] * 4. / 3.;
  }
  double per = tot / s , lz = 0;
  for( int i = 0 ; i < s ; i ++ ){
    double bl = lz , br = 100;
    for( int j = 0 ; j < 40 ; j ++ ){
      double bmid = (bl + br) * .5;
      if( f( lz , bmid ) > per )
        br = bmid;
      else
        bl = bmid;
    }
    printf( "%.12f\n" , bl - lz );
    lz = bl;
  }
}
