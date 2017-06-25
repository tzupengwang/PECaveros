#include <bits/stdc++.h>
using namespace std;
#define N 101010
const int mod = 1000000007;
int add( int a , int b ){
  a += b;
  return a >= mod ? a - mod : a;
}
int n , dp[ N ];
int main(){
  cin >> n;
  dp[ 0 ] = 1;
  for( int i = 1 ; i <= n ; i ++ ){
    dp[ i ] = dp[ i / 2 ];
    if( i == n ) break;
    dp[ i ] = add( dp[ i ] , dp[ i - 1 ] );
  }
  printf( "%d\n" , dp[ n ] );
}
