#include <bits/stdc++.h>
using namespace std;
#define N 50
int n , a[ N ] , b[ N ];
int main(){
  cin >> n;
  if( n == 1 ){
    puts( "1\n1" );
    exit(0);
  }
  if( n <= 3 ){
    puts( "-1" );
    exit(0);
  }
  int iter = 2;
  for( int i = 0 ; i < n / 2 ; i ++ ){
    a[ i ] = iter;
    iter += 2;
  }
  iter = 1;
  for( int i = n / 2 ; i < n ; i ++ ){
    a[ i ] = iter;
    iter += 2;
  }
  iter = 1;
  for( int i = 0 ; i < n / 2 ; i ++ ){
    b[ i ] = iter * n;
    iter += 2;
  }
  iter = 0;
  for( int i = n / 2 ; i < n ; i ++ ){
    b[ i ] = iter * n;
    iter += 2;
  }
  printf( "%d\n" , n );
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      printf( "%d%c" , b[ i ] + a[ j ] , " \n"[ j + 1 == n ] );
}
