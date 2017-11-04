#include <bits/stdc++.h>
using namespace std;
#define N 303030
int n , m , p[ N ] , sz[ N ];
int f( int x ){
  return x == p[ x ] ? x : p[ x ] = f( p[ x ] );
}
void uni( int x , int y ){
  x = f( x );
  y = f( y );
  if( x == y ) return;
  p[ x ] = y;
  sz[ y ] += sz[ x ];
}
vector< pair<int,int> > vv;
void init(){
  for( int i = 0 ; i < N ; i ++ ){
    p[ i ] = i;
    sz[ i ] = 1;
  }
  cin >> n >> m;
  vv.resize( m );
  for( int i = 0 ; i < m ; i ++ )
    cin >> vv[ i ].first >> vv[ i ].second;
}
int ans[ N ] , l[ N ] , r[ N ];
void solve(){
  for( int i = 1 ; i <= n ; i ++ ){
    ans[ i ] = 1;
    l[ i ] = i;
    r[ i ] = i;
  }
  sort( vv.begin() , vv.end() );
  for( auto i : vv ){
    int who = i.second;
    int tl = min( l[ who ] , l[ who + 1 ] );
    int tr = max( r[ who ] , r[ who + 1 ] );
    l[ who ] = l[ who + 1 ] = tl;
    r[ who ] = r[ who + 1 ] = tr;
  }
  for( int i = 1 ; i <= n ; i ++ )
    ans[ i ] = r[ i ] - l[ i ] + 1;
  for( int i = 1 ; i <= n ; i ++ )
    printf( "%d%c" , ans[ i ] , " \n"[ i == n ] );
}
int main(){
  init();
  solve();
}
