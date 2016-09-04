#include <bits/stdc++.h>
using namespace std;
#define N 15
int n , p[ N ];
void init(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%d" , &p[ i ] );
}
inline bool okay( int x ){
  for( int i = 0 ; i < n ; i ++ ){
    bool flag = false;
    for( int j = 0 ; j <= x ; j ++ ){
      double tmp = ( (double)j / (double)x ) * 100.0;
      int pi = ( tmp + 0.5 );
      if( pi == p[ i ] ){
        flag = true;
        break;
      }
    }
    if( !flag ) return false;
  }
  return true;
}
void solve(){
  for( int i = 1 ; i <= 100 ; i ++ )
    if( okay( i ) ){
      printf( "%d\n" , i );
      exit( 0 );
    }
  puts( "100" );
}
int main(){
  init();
  solve();
}
