#include <bits/stdc++.h>
using namespace std;
#define N 1021
char c[ N ];
int n;
bool tag[ N ];
int main(){
  freopen( "arrange.in" , "r" , stdin );
  freopen( "arrange.out" , "w" , stdout );
  scanf( "%d" , &n );
  while( n -- ){
    scanf( "%s" , c );
    if( 'A' <= c[ 0 ] && c[ 0 ] <= 'Z' )
      tag[ c[ 0 ] - 'A' ] = true;
  }
  int ans = 0;
  while( ans < 26 && tag[ ans ] ) ans ++;
  printf( "%d\n" , ans );
}
