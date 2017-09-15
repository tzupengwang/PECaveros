#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 514
int n , m , clr[ N ] , tag[ N ] , stmp , vst[ N ];
vector< int > v[ N ];
bool tg[ N ];
void gogo( int now , int clr1 , int clr2 ){
  if( vst[ now ] == stmp )
    return;
  if( clr[ now ] == clr2 )
    swap( clr1 , clr2 );
  if( !clr[ now ] )
    clr[ now ] = clr1;
  vst[ now ] = stmp;
  for( auto i : v[ now ] ){
    if( tag[ i ] != stmp )
      continue;
    gogo( i , clr2 , clr1 );
  }
}
void go( int now ){
  if( tg[ now ] )
    return;
  if( !clr[ now ] )
    clr[ now ] = 1;
  tg[ now ] = true;
  ++ stmp;
  for( int i : v[ now ] )
    tag[ i ] = stmp;
  vector<int> other;
  for( int i = 1 ; i <= 3 ; i ++ )
    if( i != clr[ now ] )
      other.push_back( i );
  for( int i : v[ now ] )
    if( clr[ i ] )
      gogo( i , other[ 0 ] , other[ 1 ] );
  for( int i : v[ now ] )
    gogo( i , other[ 0 ] , other[ 1 ] );
  for( int i : v[ now ] )
    go( i );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "mayors.in" , "r" , stdin );
  freopen( "mayors.out" , "w" , stdout );
#endif
  scanf( "%d%d" , &n , &m );
  while( m -- ){
    int ui , vi;
    scanf( "%d%d" , &ui , &vi );
    v[ ui ].push_back( vi );
    v[ vi ].push_back( ui );
  }
  for( int i = 1 ; i <= n ; i ++ )
    if( !tg[ i ] )
      go( i );
  for( int i = 1 ; i <= n ; i ++ )
    for( auto j : v[ i ] )
      if( clr[ i ] == clr[ j ] ){
        puts( "Plan failed" );
        exit(0);
      }
  puts( "Plan OK" );
  for( int i = 1 ; i <= n ; i ++ )
    printf( "%c" , " RGB"[ clr[ i ] ] );
  puts( "" );
}
