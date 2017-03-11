#include <bits/stdc++.h>
using namespace std;
typedef double D;
#define N 101010
int n , s[ N ] , x[ N ] , p[ N ];
double dp[ N ] , pp[ N ] , ss[ N ];
void init(){
  scanf( "%d" , &n );
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%d%d%d" , &s[ i ] , &x[ i ] , &p[ i ] );
    pp[ i ] = 1 + p[ i ] / 100.0;
    ss[ i ] = ss[ i - 1 ] + s[ i ] + x[ i ];
  }
}
void solve(){
  for( int i = 1 ; i <= n ; i ++ ){
    dp[ i ] = dp[ i - 1 ] + s[ i ] + x[ i ];
    double penalty = 1 , ff = s[ i ];
    for( int j = i - 1 ; j >= 1 ; j -- ){
      penalty *= pp[ j ];
      ff += penalty * s[ j ];
      if( ff > ss[ i ] ) break;
      dp[ i ] = min( dp[ i ] , dp[ j - 1 ] + x[ i ] + ff );
    }
  }
  printf( "%.12f\n" , dp[ n ] );
}
int main(){
#ifndef LOCAL
  freopen( "input.txt" , "r" , stdin );
  freopen( "output.txt" , "w" , stdout );
#endif
  init();
  solve();
}
