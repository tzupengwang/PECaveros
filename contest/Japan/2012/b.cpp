#include <bits/stdc++.h>
using namespace std;
char prog[ 2 ][ 12 ][ 111 ];
int n[ 2 ];
bool init(){
  scanf( "%d%d" , &n[ 0 ] , &n[ 1 ] );
  if( n[ 0 ] == 0 and n[ 1 ] == 0 )
    return false;
  for( int i = 0 ; i < 2 ; i ++ )
    for( int j = 0 ; j < n[ i ] ; j ++ )
      scanf( "%s" , prog[ i ][ j ] );
  return true;
}
vector<int> ans[ 12 ];
void go( int r , int c , int s ){
  int cc[ 3 ] = {};
  for( int i = 0 ; i < n[ 0 ] ; i ++ ){
    int ind = 0;
    bool cind = true;
    int tar = cc[ 0 ] * r + cc[ 1 ] * c + cc[ 2 ] * s;
    for( int j = 0 ; prog[ 0 ][ i ][ j ] ; j ++ ){
      if( prog[ 0 ][ i ][ j ] == '(' ) cc[ 0 ] ++;
      if( prog[ 0 ][ i ][ j ] == ')' ) cc[ 0 ] --;
      if( prog[ 0 ][ i ][ j ] == '{' ) cc[ 1 ] ++;
      if( prog[ 0 ][ i ][ j ] == '}' ) cc[ 1 ] --;
      if( prog[ 0 ][ i ][ j ] == '[' ) cc[ 2 ] ++;
      if( prog[ 0 ][ i ][ j ] == ']' ) cc[ 2 ] --;
      if( cind and prog[ 0 ][ i ][ j ] == '.' ) ind ++;
      else cind = false;
    }
    if( ind != tar )
      return;
  }
  cc[ 0 ] = cc[ 1 ] = cc[ 2 ] = 0;
  for( int i = 0 ; i < n[ 1 ] ; i ++ ){
    int ind = 0;
    bool cind = true;
    int tar = cc[ 0 ] * r + cc[ 1 ] * c + cc[ 2 ] * s;
    ans[ i ].push_back( tar );
    for( int j = 0 ; prog[ 1 ][ i ][ j ] ; j ++ ){
      if( prog[ 1 ][ i ][ j ] == '(' ) cc[ 0 ] ++;
      if( prog[ 1 ][ i ][ j ] == ')' ) cc[ 0 ] --;
      if( prog[ 1 ][ i ][ j ] == '{' ) cc[ 1 ] ++;
      if( prog[ 1 ][ i ][ j ] == '}' ) cc[ 1 ] --;
      if( prog[ 1 ][ i ][ j ] == '[' ) cc[ 2 ] ++;
      if( prog[ 1 ][ i ][ j ] == ']' ) cc[ 2 ] --;
      if( cind and prog[ 1 ][ i ][ j ] == '.' ) ind ++;
      else cind = false;
    }
  }
}
void solve(){
  for( int i = 0 ; i < n[ 1 ] ; i ++ )
    ans[ i ].clear();
  for( int r = 1 ; r <= 20 ; r ++ )
    for( int c = 1 ; c <= 20 ; c ++ )
      for( int s = 1 ; s <= 20 ; s ++ )
        go( r , c , s );
  for( int i = 0 ; i < n[ 1 ] ; i ++ ){
    sort( ans[ i ].begin() , ans[ i ].end() );
    ans[ i ].resize( unique( ans[ i ].begin() , ans[ i ].end() ) - ans[ i ].begin() );
    int ind = -1;
    if( ans[ i ].size() == 1u )
      ind = ans[ i ][ 0 ];
    printf( "%d%c" , ind , " \n"[ i + 1 == n[ 1 ] ] );
  }
}
int main(){
  while( init() )
    solve();
}
