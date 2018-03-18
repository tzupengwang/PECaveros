#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 222
int n , m , p[ N ];
int f( int x ){
  return x == p[ x ] ? x : p[ x ] = f( p[ x ] );
}
set< pair<int,int> > edge;
vector<int> at[ N ];
int cnt[ 2 ] , sz[ N ];
void add( int x , int y ){
  if( x > y ) swap( x , y );
  if( f( x ) == f( y ) ){
    edge.erase( { x , y } );
    return;
  }
  int p1 = f( x );
  int p2 = f( y );
  cnt[ sz[ p1 ] & 1 ] --;
  cnt[ sz[ p2 ] & 1 ] --;

  for( auto i : at[ p1 ] )
    for( auto j : at[ p2 ] ){
      int ii = i , jj = j;
      if( ii > jj ) swap( ii , jj );
      if( ii == x and jj == y )
        continue;
      edge.insert( {ii, jj} );
    }

  p[ p1 ] = p2;
  sz[ p2 ] += sz[ p1 ];
  for( auto i : at[ p1 ] )
    at[ p2 ].push_back( i );
  cnt[ sz[ p2 ] & 1 ] ++;
}
bool win[ N ][ N ][ 2 ];
int main(){
  cin >> n >> m;
  for( int i = 1 ; i <= n ; i ++ ){
    p[ i ] = i;
    at[ i ].push_back( i );
    cnt[ 1 ] ++;
    sz[ 1 ] = 1;
  }
  while( m -- ){
    int x , y;
    cin >> x >> y;
    add( x , y );
  }
  for( int i = 2 ; i <= n ; i ++ )
    for( int od = 0 ; od <= i ; od ++ ){
      int ev = i - od;
      for( int bt = 0 ; bt < 2 ; bt ++ ){
        bool twin = false;
        if( bt ) twin = twin or not win[ i ][ od ][ bt ];
        if( od > 1 ) twin = twin or not win[ i - 1 ][ od - 2 ][ bt ];
        if( ev > 1 ) twin = twin or not win[ i - 1 ][ od ][ 1 - bt ];
        if( od and ev ) twin = twin or not win[ i - 1 ][ od ][ 1 - bt ];
        win[ i ][ od ][ bt ] = twin;
      }
    }
  int turn = 0;
  if( win[ cnt[ 0 ] + cnt[ 1 ] ][ cnt[ 1 ] ][ edge.size() & 1 ] )
    printf( "1\n" );
  else{
    turn = 1;
    printf( "2\n" );
  }
  while( true ){
    if( turn == 0 ){
      if( (edge.size() & 1) and not win[ cnt[ 0 ] + cnt[ 1 ] ][ cnt[ 1 ] ][ (int)edge.size() & 1u ] ){
        
      }
    }else{
      int x , y;
      scanf( "%d%d" , &x , &y );
      add( x , y );
    }
    turn = 1 - turn;
  }
}
