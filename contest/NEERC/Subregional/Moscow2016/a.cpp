#include <bits/stdc++.h>
using namespace std;
#define N 101010
int n , a[ N ];
void init(){
  scanf( "%d" , &n );
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%d" , &a[ i ] );
}
void solve(){
  for( int i = 1 ; i <= n ; i ++ ){
    int nxti = i + 1;
    int nxtj = i + 2;
    if( nxti > n ) nxti -= n;
    if( nxtj > n ) nxtj -= n;
    if( a[ i ] < a[ nxti ] && a[ nxti ] > a[ nxtj ] ){
      printf( "%d %d %d\n" , i , nxti , nxtj );
      exit( 0 );
    }
  }
}
int main(){
  init();
  solve();
}
