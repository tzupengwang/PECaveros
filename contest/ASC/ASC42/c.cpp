#include <bits/stdc++.h>
using namespace std;
#define N 111
int n , a[ N ];
void init(){
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%d" , &a[ i ] );
}
inline bool bye(){
  for( int i = 1 ; i < n ; i ++ )
    if( a[ i ] > a[ i + 1 ] )
       return false;
  return true;
}
void solve(){
  if( bye() ){
    puts( "-1" );
    return;
  }
  vector< pair<int,int> > ans;
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = i + 1 ; j <= n ; j ++ )
      if( a[ i ] == a[ j ] )
        ans.push_back( { i , j } );
  int lst0 = 0;
  for( int i = 1 ; i <= n ; i ++ )
    if( a[ i ] == 0 )
      lst0 = i;
  int pz = 0;
  for( int i = 1 ; i <= n ; i ++ ){
    for( int j = 1 ; j < i ; j ++ ){
      if( i == lst0 && j == pz + 1 ) continue;
      ans.push_back( { i , j } );
    }
    if( a[ i ] == 0 ) pz ++;
  }
  printf( "%d\n" , (int)ans.size() );
  for( auto i : ans )
    printf( "%d %d\n" , i.first , i.second );
}
int main(){
  freopen( "comparator.in" , "r" , stdin );
  freopen( "comparator.out" , "w" , stdout );
  while( scanf( "%d" , &n ) == 1 && n ){
    init();
    solve();
  }
}
