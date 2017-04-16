#include <bits/stdc++.h>
using namespace std;
#define N 101010
char c[ N ];
int main(){
  scanf( "%s" , c );
  int cnt[ 2 ] = {};
  for( int i = 0 ; c[ i ] ; i ++ )
    cnt[ c[ i ] == 'W' ] ++;
  printf( "%d\n" , cnt[ 0 ] == cnt[ 1 ] );
}
