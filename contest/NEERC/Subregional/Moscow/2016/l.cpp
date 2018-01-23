#include<bits/stdc++.h>
using namespace std ;

int n ;
char c[ 200005 ][ 5 ] ;
int s[ 200005 ] ;
double pp[ 200005 ] ;
double ans[ 200005 ] ;

int main() {
  scanf( "%d" , &n ) ;
  n *= 2;
  for ( int i = 0 ; i < n ; i ++ ) {
    scanf( "%s%d" , c[ i ] , &s[ i ] ) ;
  }
  int in = 0 ;
  for ( int i = 0 ; i < n ; i ++ ) {
    if ( c[ i ][ 0 ] == '+' ) {
      in ++ ;
    } else {
      pp[ i ] = (double)1 / in ;
      in -- ;
    }
  }
  double p = 0 ;
  for ( int i = n - 1 ; i >= 0 ; i -- ) {
    if ( c[ i ][ 0 ] == '+' ) {
      ans[ i ] = p - s[ i ] ;
    } else {
      p = p * ( 1 - pp[ i ] ) + pp[ i ] * s[ i ] ;
      //printf( "p = %.5f\n" , p ) ;
    }
  }
  for ( int i = 0 ; i < n ; i ++ ) {
    if ( c[ i ][ 0 ] == '+' ) {
      printf( "%.10f\n" , ans[ i ] ) ;
    }
  }
}
