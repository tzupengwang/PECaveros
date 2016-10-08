#include <bits/stdc++.h>
using namespace std;
#define N 101010
char c[ N ][ 10 ];
int n , b[ N ];
bool bye[ N ];
void init(){
  scanf( "%d" , &n );
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%s" , c[ i ] );
    if( c[ i ][ 0 ] == 'c' )
      scanf( "%d" , &b[ i ] );
  }
}
void solve(){
  vector< int > ans;
  for( int i = n ; i >= 1 ; i -- ){
    if( bye[ i ] ) continue;
    ans.push_back( i );
    if( c[ i ][ 0 ] == 'c' )
      bye[ b[ i ] ] = true;
  }
  reverse( ans.begin() , ans.end() );
  printf( "%d\n" , (int)ans.size() );
  for( size_t i = 0 ; i < ans.size() ; i ++ )
    printf( "%d%c" , ans[ i ] , " \n"[ i + 1 == ans.size() ] );
}
int main(){
  freopen( "bureau.in" , "r" , stdin );
  freopen( "bureau.out" , "w" , stdout );
  init();
  solve();
}
