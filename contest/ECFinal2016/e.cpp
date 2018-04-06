#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 111
int n , _cs;
double ri[ N ];
double read(){
  double ai , bi;
  scanf( "%lf:%lf" , &ai , &bi );
  return ai / bi;
}
int main(){
  int t; scanf( "%d" , &t ); while( t -- ){
    scanf( "%d" , &n );
    for( int i = 0 ; i < n ; i ++ )
      ri[ i ] = 1. / ( 1. + read() );
    sort( ri , ri + n );
    int ans = 0;
    double sum = 0;
    for( int i = 0 ; i < n ; i ++ ){
      sum += ri[ i ];
      if( sum > 1 + 1e-10 ) break;
      ans ++;
    }
    printf( "Case #%d: %d\n" , ++ _cs , ans );
  }
}
