#include <bits/stdc++.h>
using namespace std;
#define N 10101
char c[ N ];
int n;
void init(){
  scanf( "%s" , c + 1 );
  n = strlen( c + 1 );
}
int dp[ N ] , fl[ N ];
void solve(){
  for( int i = 1 ; i <= n ; i ++ )
    dp[ i ] = n;
  for( int i = 0 ; i < n ; i ++ ){
    dp[ i + 1 ] = min( dp[ i + 1 ] , dp[ i ] + 1 );
    fl[ i + 1 ] = i;
    for( int j = i + 2 , pre = i ; j <= n ; j ++ ){
      while( pre > i and c[ pre + 1 ] != c[ j ] )
        pre = fl[ pre ];
      if( c[ pre + 1 ] == c[ j ] ) pre ++;
      fl[ j ] = pre;
      int tmp = j - pre;
      int cst = j - i;
      if( (j - i) % tmp == 0 ) cst = tmp;
      dp[ j ] = min( dp[ j ] , dp[ i ] + cst );
    }
  }
  printf( "%d\n" , dp[ n ] );
}
int main(){
  int t; scanf( "%d" , &t ); while( t -- ){
    init();
    solve();
  }
}
