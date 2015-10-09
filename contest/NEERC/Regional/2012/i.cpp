#include <bits/stdc++.h>
using namespace std;
#define N 52
int n , a[ N ] , pos[ N ] , ta[ N ] , ba[ N ];
void init(){
  scanf( "%d" , &n );
  for( int i = 1 ; i <= n ; i ++ )
    a[ i ] = i;
  random_shuffle( a + 1 , a + n + 1 );
  for( int i = 1 ; i <= n ; i ++ )
    pos[ a[ i ] ] = i;
}
void output( int* oa ){
  for( int i = 1 ; i <= n ; i ++ )
    printf( "%d%c" , oa[ i ] , i == n ? '\n' : ' ' );
  fflush( stdout );
}
void solve(){
  while( true ){
    for( int i = 1 ; i <= n ; i ++ ){
      int npos = pos[ i ];
      int bst = -1 , bi = -1;
      int idx = 0;
      for( int j = 1 ; j <= n ; j ++ ){
        idx = 0;
        for( int k = 1 ; k <= n ; k ++ )
          if( k != npos )
            ba[ ++ idx ] = a[ k ];
        idx = 0;
        for( int k = 1 ; k < j ; k ++ )
          ta[ ++ idx ] = ba[ k ];
        ta[ ++ idx ] = i;
        for( int k = j ; k < n ; k ++ )
          ta[ ++ idx ] = ba[ k ];
        output( ta );
        int lcs; scanf( "%d" , &lcs );
        if( lcs == n ) exit( 0 );
        if( lcs > bst ) bst = lcs, bi = j;
      }
      idx = 0;
      for( int k = 1 ; k <= n ; k ++ )
        if( k != npos )
          ba[ ++ idx ] = a[ k ];
      idx = 0;
      for( int k = 1 ; k < bi ; k ++ )
        ta[ ++ idx ] = ba[ k ];
      ta[ ++ idx ] = i;
      for( int k = bi ; k < n ; k ++ )
        ta[ ++ idx ] = ba[ k ];
      for( int j = 1 ; j <= n ; j ++ )
        a[ j ] = ta[ j ];
      for( int j = 1 ; j <= n ; j ++ )
        pos[ a[ j ] ] = j;
    }
  }
}
int main(){
  srand( 514514 );
  init();
  solve();
}
