#include <bits/stdc++.h>
using namespace std;
#define N 514
const int mod = 1000000007;
int n;
int dp[ 2 ][ N ][ N ];
int tdp[ N ][ N ];
int tdp2[ N ][ N ];
inline int add( int _ , int _2 ){
  _ += _2;
  return _ >= mod ? _ - mod : _;
}
inline int sub( int _ , int _2 ){
  _ -= _2;
  return _ < 0 ? _ + mod : _;
}
void solve(){
  dp[ 0 ][ 2 ][ 2 ] = 1;
  for( int i = 1 ; i <= n ; i ++ ){
    int now = i & 1 , pre = 1 - now;
    for( int j = 2 ; j <= i + 2 ; j ++ )
      for( int k = j + 1 ; k <= i + 2 ; k ++ ){
        tdp[ j ][ k ] =
        tdp2[ j ][ k ] =
        dp[ now ][ j ][ k ] = 0;
      }
    for( int j = 2 ; j <= i + 1 ; j ++ )
      for( int k = j ; k <= i + 1 ; k ++ ){
        dp[ now ][ j + 1 ][ k + 1 ] = add( dp[ now ][ j + 1 ][ k + 1 ] ,
                                           dp[ pre ][ j ][ k ] );
        tdp[ 2 ][ k + 1 ] = add( tdp[ 2 ][ k + 1 ] ,
                                        dp[ pre ][ j ][ k ] );
        tdp[ j + 1 ][ k + 1 ] = sub( tdp[ j + 1 ][ k + 1 ] ,
                                        dp[ pre ][ j ][ k ] );
        tdp2[ j ][ j + 1 ] = add( tdp2[ j ][ j + 1 ] ,
                                        dp[ pre ][ j ][ k ] );
        tdp2[ j ][ k + 1 ] = sub( tdp2[ j ][ k + 1 ] ,
                                        dp[ pre ][ j ][ k ] );
      }
    for( int j = 3 ; j <= i + 2 ; j ++ )
      for( int k = j ; k <= i + 1 ; k ++ )
        tdp[ j ][ k ] = add( tdp[ j ][ k ] , tdp[ j - 1 ][ k ] );
    for( int j = 2 ; j <= i + 1 ; j ++ )
      for( int k = j + 1 ; k < N ; k ++ )
        tdp2[ j ][ k ] = add( tdp2[ j ][ k ] , tdp2[ j ][ k - 1 ] );
    for( int j = 2 ; j <= i + 2 ; j ++ )
      for( int k = j + 1 ; k <= i + 2 ; k ++ ){
        dp[ now ][ j ][ k ] = add( dp[ now ][ j ][ k ] ,
                                   tdp[ j ][ k ] );
        dp[ now ][ j ][ k ] = add( dp[ now ][ j ][ k ] ,
                                   tdp2[ j ][ k ] );
      }
  }
  int ans = 0;
  for( int j = 2 ; j <= n + 2 ; j ++ )
    for( int k = j + 1 ; k <= n + 2 ; k ++ )
      ans = add( ans , dp[ n & 1 ][ j ][ k ] );
  printf( "%d\n" , ans );
}
int main(){
  scanf( "%d" , &n );
  solve();
}
