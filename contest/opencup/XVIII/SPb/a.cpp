#include <bits/stdc++.h>
using namespace std;
#define N 1010101
char a[ N ];
int v[ N ];
__int128 x;
int main(){
  for( int i = 0 ; i < 2 ; i ++ ){
    scanf( "%s" , a );
    int len = strlen( a );
    for( int j = 0 ; j < len ; j ++ )
      v[ j ] += a[ len - j - 1 ] - '0';
  }
  for( int i = 0 ; i + 4 < N ; i ++ ){
    while (v[i] >= 2 && v[i + 1] >= 2 && v[i + 2] >= 1) {
      v[i] -= 2;
      v[i + 1] -= 2;
      v[i + 2] -= 1;
    }
    if( v[ i ] > 1 ){
      v[ i + 2 ] += v[ i ] / 2;
      v[ i + 3 ] += v[ i ] / 2;
    }
    v[ i ] &= 1;
  }
  int lst = N - 1;
  while( lst > 0 and !v[ lst ] ) lst --;
  for( int i = lst ; i >= 0 ; i -- )
    printf( "%d" , v[ i ] );
  puts( "" );
}
