#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 61
int dp[ N ][ N ];
int fi[ N ][ N ] , fj[ N ][ N ];
int h , w;
void init(){
  scanf( "%d%d" , &h , &w );
}
void print( int nh , int nw , int dx , int dy ){
  if( nh == 0 || nw == 0 ) return;
  if( dp[ nh ][ nw ] == 1 ){
    printf( "%d %d %d\n" , dx , dy , nh );
    return;
  }
  print( fi[ nh ][ nw ] , fj[ nh ][ nw ] , dx , dy );
  if( fi[ nh ][ nw ] == nh )
    print( fi[ nh ][ nw ] , nw - fj[ nh ][ nw ] , dx , dy + fj[ nh ][ nw ] );
  else
    print( nh - fi[ nh ][ nw ] , fj[ nh ][ nw ] , dx + fi[ nh ][ nw ] , dy );
}
int dp2[ N ][ N ][ N ][ N ];
void solve(){
  go_dp( h , w , 0 , 0 );
}
int main(){
  for( int i = 1 ; i < N ; i ++ )
    for( int j = 1 ; j < N ; j ++ ){
      if( i == j ){
        dp[ i ][ j ] = 1;
        continue;
      }
      dp[ i ][ j ] = i * j + 10;
      fi[ i ][ j ] = 0;
      fj[ i ][ j ] = 0;
      for( int i1 = 1 ; i1 < i ; i1 ++ )
        if( dp[ i1 ][ j ] + dp[ i - i1 ][ j ] < dp[ i ][ j ] ){
          dp[ i ][ j ] = dp[ i1 ][ j ] + dp[ i - i1 ][ j ];
          fi[ i ][ j ] = i1;
          fj[ i ][ j ] = j;
        }
      for( int j1 = 1 ; j1 < j ; j1 ++ )
        if( dp[ i ][ j1 ] + dp[ i ][ j - j1 ] < dp[ i ][ j ] ){
          dp[ i ][ j ] = dp[ i ][ j1 ] + dp[ i ][ j - j1 ];
          fi[ i ][ j ] = i;
          fj[ i ][ j ] = j1;
        }
    }
#ifdef ONLINE_JUDGE
  freopen( "hard.in" , "r" , stdin );
  freopen( "hard.out" , "w" , stdout );
#endif
  build();
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
