#include <bits/stdc++.h>
using namespace std;
#define N 514
int n , a[ N ];
vector< pair<int,int> > rules;
void add_rule( int i1 , int i2 ){
  rules.push_back( { i1 , i2 } );
}
vector<int> v[ N ];
vector< pair<int,int> > vv[ N ];
int main(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < 3 ; i ++ )
    for( int j = 1 ; j <= n ; j ++ ){
      int x; scanf( "%d" , &x );
      if( x ) a[ j ] |= ( 1 << i );
    }
  for( int i = 1 ; i <= n ; i ++ )
    v[ a[ i ] ].push_back( i );
  int cc = 0;
  for( int i = 1 ; i < 4 ; i ++ )
    if( v[ i ].size() or v[ 7 - i ].size() )
      cc ++;
  if( cc > 2 ){
    puts( "-1" );
    exit( 0 );
  }
  for( auto i : v[ 0 ] ) add_rule( +i , -i );
  for( auto i : v[ 7 ] ) add_rule( -i , +i );
  for( int i = 1 ; i < 7 ; i ++ )
    for( auto j : v[ i ] )
      vv[ min( i , 7 - i ) ].push_back( { i , j } );
  vector< pair<int,int> > cand;
  for( int i = 1 ; i < 4 ; i ++ ){
    for( auto tp : vv[ i ] ){
      if( tp == vv[ i ][ 0 ] ) continue;
      if( tp.first == vv[ i ][ 0 ].first ){
        add_rule( vv[ i ][ 0 ].second , tp.second );
        add_rule( tp.second , vv[ i ][ 0 ].second );
      }else{
        add_rule( vv[ i ][ 0 ].second , -tp.second );
        add_rule( -tp.second , vv[ i ][ 0 ].second );
      }
    }
    if( vv[ i ].size() )
      cand.push_back( vv[ i ][ 0 ] );
  }
  if( cand.size() > 1u ){
    int tag[ 2 ][ 2 ] = {};
    for( int i = 0 ; i < 3 ; i ++ ){
      int b1 = ( cand[ 0 ].first >> i ) & 1;
      int b2 = ( cand[ 1 ].first >> i ) & 1;
      tag[ b1 ][ b2 ] = 1;
    }
    for( int i = 0 ; i < 2 ; i ++ )
      for( int j = 0 ; j < 2 ; j ++ )
        if( tag[ i ][ j ] == 0 ){
          int c1 = cand[ 0 ].second;
          int c2 = cand[ 1 ].second;
          if( i == 0 ) c1 = -c1;
          if( j == 1 ) c2 = -c2;
          add_rule( c1 , c2 );
        }
  }
  printf( "%d\n" , (int)rules.size() );
  for( auto r : rules ){
    if( r.first < 0 ) putchar( '!' );
    printf( "x%d -> " , abs( r.first ) );
    if( r.second < 0 ) putchar( '!' );
    printf( "x%d\n" , abs( r.second ) );
  }
}
