#include <bits/stdc++.h>
using namespace std;
#define N 200010
int p[ N ];
int n , m , k;
bool alive[ N ];
int find_p( int x ){
  return x == p[ x ] ? x : p[ x ] = find_p( p[ x ] );
}
void Union( int x , int y ){
  x = find_p( x );
  y = find_p( y );
  p[ x ] = y;
}
char c[ 100 ];
void init(){
  freopen( "eve.in" , "r" , stdin );
  freopen( "eve.out" , "w" , stdout );
  scanf( "%d" , &n );
  for( int i = 0 ; i < N ; i ++ ) p[ i ] = i , alive[ i ] = true;
  for( int i = 0 ; i < n ; i ++ ) scanf( "%s" , c );
  scanf( "%d" , &m );
  while( m -- ){
    int ta , tb; scanf( "%d" , &ta );
    if( ta < 0 ) alive[ -ta ] = false;
    else{
      scanf( "%d%s" , &tb , c );
      Union( tb , ++ n );
    }
  }
}
set<int> S;
int g[ N ];
void solve(){
  scanf( "%d" , &k ); while( k -- ){
    int no , ng;
    scanf( "%d%d" , &no , &ng );
    g[ find_p( no ) ] = ng;
  }
  for( int i = 1 ; i <= n ; i ++ )
    if( alive[ i ] && g[ find_p( i ) ] > 0 )
      S.insert( g[ find_p( i ) ] );
  if( (int)S.size() > 1 ) puts( "NO" );
  else{
    S.clear();
    for( int i = 1 ; i <= n ; i ++ )
      if( alive[ i ] )
        S.insert( g[ find_p( i ) ] );
    if( (int)S.size() > 1 ) puts( "POSSIBLY" );
    else{
      if( *S.begin() == 0 ){
        S.clear();
        for( int i = 1 ; i <= n ; i ++ )
          if( alive[ i ] )
            S.insert( find_p( i ) );
        if( (int)S.size() > 1 ) puts( "POSSIBLY" );
        else puts( "YES" );
      }else puts( "YES" );
    }
  }
}
int main(){
  init();
  solve();
}
