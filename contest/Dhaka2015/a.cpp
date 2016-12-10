#include <bits/stdc++.h>
using namespace std;
int n;
int cnt[ 11 ] , cnt2[ 11 ];
void init(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < 11 ; i ++ )
    cnt[ i ] = cnt2[ i ] = 0;
  while( n -- ){
    int a , b; char c[ 9 ];
    scanf( "%d%d%s" , &a , &b , c );
    if( b == 0 && c[ 0 ] == 'i' ) cnt[ a ] ++;
    if( b == 1 && c[ 0 ] == 'c' ) cnt2[ a ] ++;
  }
  for( int i = 2 ; i < 11 ; i ++ )
   cnt[ i ] += cnt[ i - 1 ];
}
void solve(){
  int ans = 0;
  for( int i = 2 ; i < 11 ; i ++ )
    ans += cnt2[ i ] * cnt[ i - 1 ];
  printf( "%d\n" , ans );
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
