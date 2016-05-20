#include <bits/stdc++.h>

using namespace std;

const int MAXN = 110;

int n;
int in[ MAXN ];

bool chk( int k ) {
  static int arr[ MAXN ];

  if( k == 1 ) {
    if( n == 1 ) return in[ 1 ] == 2;
    if( n == 2 ) return in[ 1 ] == 1 && in[ 2 ] == 1;
    return 0;
  }

  for( int i = 1 ; i <= n ; i++ )
    arr[ i ] = in[ i ];

  for( int i = k , j = 1 ; i > 0 ; i-- ) {
    if( arr[ j ] < i ) return 0;
    arr[ j ] -= i;
    if( arr[ j ] == 0 ) j++;
    if( j > n ) return 0;
  }

  for( int i = k , j = n ; i > 0 ; i-- ) {
    if( arr[ j ] < i ) return 0;
    arr[ j ] -= i;
    if( arr[ j ] == 0 ) j--;
    if( j < 0 ) return 0;
  }

  int sum = 0;
  for( int i = 1 ; i <= n ; i++ ) {
    if( arr[ i ] < 0 ) return 0;
    sum += arr[ i ];
  }

  return sum % 2 == 0;
}

int main() {

  scanf( "%d" , &n );
  for( int i = 1 ; i <= n ; i++ )
    scanf( "%d" , in+i );


  for( int k = in[ 1 ] ; k > 0 ; k-- ) {
    if( chk( k ) ) {
      printf( "%d\n" , k );
      return 0;
    }
  }
  puts( "no quotation" );

}
