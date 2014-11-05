#include <bits/stdc++.h>
using namespace std;
#define N 100010
char T[ N ];
int n , RA[ N ], tempRA[ N ] , SA[ N ], tempSA[ N ] , c[ N ];
void countingSort( int k ){
	int i , sum , maxi = max( 300 , n ) ;
	memset( c , 0 , sizeof c ) ;
	for ( i = 0 ; i < n ; i ++ ) c[ ( i + k < n ) ? RA[i + k] : 0 ] ++ ;
	for ( i = sum = 0 ; i < maxi ; i ++ ) { int t = c[i] ; c[i] = sum ; sum += t ; }
	for ( i = 0 ; i < n ; i ++ )
		tempSA[ c[ ( SA[ i ] + k < n ) ? RA[ SA[ i ] + k ] : 0 ] ++ ] = SA[ i ] ;
	for ( i = 0 ; i < n ; i ++ ) SA[ i ] = tempSA[ i ] ;
}
void constructSA(){
	int r;
	for ( int i = 0 ; i < n ; i ++ ) RA[ i ] = T[ i ] - '.' ;
	for ( int i = 0 ; i < n ; i ++ ) SA[ i ] = i ;
	for ( int k = 1 ; k < n ; k <<= 1 ) {
		countingSort( k ) ; countingSort( 0 ) ;
		tempRA[ SA[ 0 ] ] = r = 0;
		for ( int i = 1 ; i < n ; i ++ )
			tempRA[ SA[ i ] ] = ( RA[ SA[ i ] ] == RA[ SA[ i - 1 ] ] && RA[ SA[ i ] + k ] == RA[ SA[ i - 1 ] + k ] ) ? r : ++ r ;
		for ( int i = 0 ; i < n ; i ++ ) RA[ i ] = tempRA[ i ] ;
	}
}
int main() {
  n = (int)strlen( gets( T ) ) ;
  T[ n ++ ] = '.' ; // important bug fix!
  constructSA() ;
  return 0;
}
