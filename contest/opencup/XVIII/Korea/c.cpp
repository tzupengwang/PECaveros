#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 1021
int n , id[ N ];
double p[ N ][ N ] , fail[ N ] , e[ N ] , fok[ N ];
bool cmp( int id1 , int id2 ){
  return e[ id1 ] + fail[ id1 ] * e[ id2 ] <
         e[ id2 ] + fail[ id2 ] * e[ id1 ];
}
int main(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ ){
    int ki; scanf( "%d" , &ki );
    for( int j = 0 , x ; j < ki ; j ++ ){
      scanf( "%d" , &x );
      p[ i ][ j ] = (double)x / 1000.;
    }
    sort( p[ i ] , p[ i ] + ki );
    double ok = 1.;
    for( int j = 0 ; j < ki ; j ++ ){
      e[ i ] += ok;
      fail[ i ] += ok * (1. - p[ i ][ j ]);
      ok *= p[ i ][ j ];
    }
    fok[ i ] = ok;
    id[ i ] = i;
  }
  sort( id , id + n , cmp );
  //sort( vv.begin() , vv.end() );
  double ans = 0. , keep = 1.;
  for( int _ = 0 ; _ < n ; _ ++ ){
    int i = id[ _ ];
    //printf( "%d\n" , i );
    ans += keep * e[ i ];
    keep *= fail[ i ];
  }
  printf( "%.12f\n" , ans );
}
