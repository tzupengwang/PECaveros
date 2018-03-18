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
set<int> wt[ 2 ];
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
  wt[ sz[ p1 ] & 1 ].erase( p1 );
  wt[ sz[ p2 ] & 1 ].erase( p2 );

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
  wt[ sz[ p2 ] & 1 ].insert( p2 );
}
bool win[ N ][ N ][ 2 ];
int main(){
  for( int i = 2 ; i < N ; i ++ )
    for( int od = 0 ; od <= i ; od ++ ){
      int ev = i - od;
      for( int bt = 0 ; bt < 2 ; bt ++ ){
        bool twin = false;
        if( bt ) twin = twin or not win[ i ][ od ][ 0 ];
        if( od > 1 ) twin = twin or not win[ i - 1 ][ od - 2 ][ bt ];
        if( ev > 1 ) twin = twin or not win[ i - 1 ][ od ][ 1 - bt ];
        if( od and ev ) twin = twin or not win[ i - 1 ][ od ][ 1 - bt ];
        win[ i ][ od ][ bt ] = twin;
      }
      assert( win[ i ][ od ][ 0 ] or win[ i ][ od ][ 1 ] );
    }
  cin >> n >> m;
  for( int i = 1 ; i <= n ; i ++ ){
    p[ i ] = i;
    at[ i ].push_back( i );
    sz[ i ] = 1;
    cnt[ 1 ] ++;
    wt[ 1 ].insert( i );
  }
  while( m -- ){
    int x , y;
    cin >> x >> y;
    add( x , y );
  }
  if( cnt[ 0 ] + cnt[ 1 ] == 1 ){
    puts( "1" );
    fflush( stdout );
    exit(0);
  }
  int turn = 0;
  if( win[ cnt[ 0 ] + cnt[ 1 ] ][ cnt[ 1 ] ][ edge.size() & 1 ] )
    printf( "1\n" );
  else{
    turn = 1;
    printf( "2\n" );
  }
  fflush( stdout );
  while( cnt[ 0 ] + cnt[ 1 ] > 1 ){
    if( turn == 0 ){
      int tot = cnt[ 0 ] + cnt[ 1 ];
      int odd = cnt[ 1 ];
      int other = edge.size() % 2;
      int x , y;
      if( edge.size() and not win[ tot ][ odd ][ 1 - other ] ){
        tie( x , y ) = *edge.begin();
        edge.erase( {x, y} );
      }else if( odd > 1 and not win[ tot - 1 ][ odd - 2 ][ other ] ){
        x = *wt[ 1 ].begin();
        y = *wt[ 1 ].rbegin();
      }else if( tot - odd > 1 and not win[ tot - 1 ][ odd ][ 1 - other ] ){
        x = *wt[ 0 ].begin();
        y = *wt[ 0 ].rbegin();
      }else if( odd and tot - odd and not win[ tot - 1 ][ odd ][ 1 - other ] ){
        x = *wt[ 0 ].begin();
        y = *wt[ 1 ].begin();
      }else{
        tie( x , y ) = *edge.begin();
        edge.erase( {x, y} );
      }
      assert( x != y );
      printf( "%d %d\n" , x , y );
      fflush( stdout );
      add( x , y );
    }else{
      int x , y;
      scanf( "%d%d" , &x , &y );
      if( x == 0 and y == 0 )
        exit(0);
      add( x , y );
    }
    turn = 1 - turn;
  }
}
