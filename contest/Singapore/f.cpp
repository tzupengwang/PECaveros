#include <bits/stdc++.h>
using namespace std;
#define N 111
int n , l[ N ] , r[ N ];
bool c[ N ];
void init(){
  scanf( "%d" , &n );
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%d%d" , &l[ i ] , &r[ i ] );
}
vector< pair<int,int> > v;
int cl[ N ][ N ] , cr[ N ][ N ];
bool can[ N ][ N ];
void cal(){
  for( int i = 1 ; i <= n ; i ++ )
    if( !c[ i ] )
      v.push_back( { l[ i ] , r[ i ] } );
  sort( v.begin() , v.end() );
  n = (int)v.size();
  for( int i = 0 ; i < n ; i ++ ){
    cl[ i ][ i ] = v[ i ].first;
    cr[ i ][ i ] = v[ i ].second;
    for( int j = i + 1 ; j < n ; j ++ ){
      cl[ i ][ j ] = max( cl[ i ][ j - 1 ] , v[ j ].first );
      cr[ i ][ j ] = min( cr[ i ][ j - 1 ] , v[ j ].second );
      // printf( "%d %d : %d %d\n" , i , j,  cl[ i ][ j ],  cr[ i ][ j ] );
    }
  }
  can[ 0 ][ 1 ] = true;
  for( int i = 1 ; i < n ; i ++ )
    if( cl[ 0 ][ i ] <= cr[ 0 ][ i ] )
      can[ i ][ 1 ] = true;
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j <= n ; j ++ ){
      if( !can[ i ][ j ] ) continue;
      for( int k = i + 1 ; k < n ; k ++ )
        if( cl[ i + 1 ][ k ] <= cr[ i + 1 ][ k ] )
          can[ k ][ j + 1 ] = true;
    }
  for( int i = 0 ; i <= n ; i ++ )
    if( can[ n - 1 ][ i ] ){
      printf( "%d\n" , i );
      exit( 0 );
    }
}
void solve(){
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = i + 1 ; j <= n ; j ++ )
      if( l[ i ] <= l[ j ] && r[ j ] <= r[ i ] )
        c[ i ] = true;
  cal();
}
int main(){
  init();
  solve();
}
