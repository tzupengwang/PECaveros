#include <bits/stdc++.h>
using namespace std;
#define N 1010101
bool p[ N ];
int n , f[ N ] , pp[ N ];
int main(){
  srand( 514514 );
  scanf( "%d" , &n );
  f[ 1 ] = 1;
  for( int i = 2 ; i <= n ; i ++ ) if( !p[ i ] ){
    //if ( i == 293 || i == 443 || i == 659 || i == 661 ) f[ i ] = 1 ;
    //else f[ i ] = -1 ;
    //f[ i ] = ( i == 2 ) ? 1 : -1;
    f[ i ] = rand() % 2 ? 1 : -1;
    for( int j = i + i ; j <= n ; j += i ){
      pp[ j ] = i;
      p[ j ] = true;
    }
  }
  int mx = 0 , pre = 0;
  for( int i = 1 ; i <= n ; i ++ ){
    if( f[ i ] == 0 ){
      f[ i ] = f[ pp[ i ] ] * f[ i / pp[ i ] ];
    }
    //int npre = pre + f[ i ] ;
    //int nmx = max( mx , abs( npre ) ) ;
    pre += f[ i ];
    mx = max( mx , abs( pre ) );
    if ( mx > 20 ) {
      //assert( p[ i ] == false ) ;
      //f[ i ] = -f[ i ] ;
      printf( "failed at %d\n" , i ) ;
      exit(0);
      //i -- ;
      //continue ;
    }
  }
  for( int i = 1 ; i <= 10 ; i ++ )
    printf( "%d %d\n" , i , f[ i ] );
  puts( "" );
  printf( "%d\n" , mx );
}
