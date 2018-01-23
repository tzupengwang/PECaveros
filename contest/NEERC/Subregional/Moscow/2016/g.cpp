#include <bits/stdc++.h>
using namespace std;
#define N 111
int n;
void move( int from , int to , int who ){
  printf( "%d %d %d\n" , from , who , to );
}
int main(){
  scanf( "%d" , &n );
  move( 1 , 0 , 1 );
  for( int i = 2 ; i <= n ; i ++ ){
    move( i , 1 , i );
    if( i != n )
      move( 1 , i , 1 );
  }
  for( int i = 2 ; i < n ; i ++ ){
    move( i , n , i );
    for( int j = i + 1 ; j <= n ; j ++ ){
      move( j , i , j );
      if( j != n )
        move( i , j , i );
    }
  }
  move( 0 , n , 1 );
}
