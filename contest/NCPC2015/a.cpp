#include <bits/stdc++.h>
using namespace std;
int __ = 1;
int x[ 3 ] , y[ 3 ];
void init(){
  for( int i = 0 ; i < 3 ; i ++ )
    scanf( "%d%d" , &x[ i ] , &y[ i ] );
}
void solve(){
  for( int a = -64 ; a <= 64 ; a ++ )
    for( int b = -64 ; b <= 64 ; b ++ )
      for( int c = -64 ; c <= 64 ; c ++ ){
        int cnt = 0;
        for( int i = 0 ; i < 3 ; i ++ )
          if( a * x[ i ] * x[ i ] + b * x[ i ] + c == y[ i ] ) cnt ++;
        if( cnt == 3 ){
          printf( "%d %d %d\n" , a , b , c );
          return;
        }
      }
}
int main(){
  scanf( "%d" , &__ ); while( __ -- ){
    init();
    solve();
  }
}
