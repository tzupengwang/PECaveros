#include <bits/stdc++.h>
using namespace std;
#define N 505050
int n , p[ N ] , sz[ N ];
int find_p( int x ){
  return x == p[ x ] ? x : p[ x ] = find_p( p[ x ] );
}
void Union( int x , int y ){
  x = find_p( x );
  y = find_p( y );
  if( x == y ) return;
  p[ x ] = y;
  sz[ y ] += sz[ x ];
}
void init(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < N ; i ++ )
    p[ i ] = i , sz[ i ] = 1;
}
int clr[ N ];
void solve(){
  int ans = 0;
  while( n -- ){
    int k; scanf( "%d" , &k );
    for( int i = 0 ; i < k ; i ++ )
      scanf( "%d" , &clr[ i ] );
    map< int , int > M;
    for( int i = 0 ; i < k ; i ++ )
      M[ find_p( clr[ i ] ) ] ++;
    bool okay = true;
    for( auto it = M.begin() ; it != M.end() ; it ++ )
      if( sz[ it->first ] != it->second ){
        okay = false;
        break;
      }
    if( !okay ) continue;
    ans ++;
    for( int i = 1 ; i < k ; i ++ )
      Union( clr[ i - 1 ] , clr[ i ] );
  }
  printf( "%d\n" , ans );
}
int main(){
  init();
  solve();
}
