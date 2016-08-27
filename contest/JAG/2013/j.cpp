// eddy1021
#include <bits/stdc++.h>
using namespace std;
#define N 4096
//   ( A and B ) or ( C and D ) or ( E and F )
// = ( A or C or E ) and ( A or C or F ) and ( A or D or E ) ...
typedef vector<int> clause;
vector< clause > eq;
int n;
char c[ 3 ][ N ];
inline int term( char ctmp ){
  if( ctmp >= 'a' ) return 1 + ( ( ctmp - 'a' ) << 1 );
  return ( ctmp - 'A' ) << 1;
}
inline bool init(){
  scanf( "%d" , &n );
  if( n == 0 ) return false;
  eq.clear();
  for( int i = 0 ; i < 3 ; i ++ )
    scanf( "%s" , c[ i ] );
  for( int i = 1 ; i <= n ; i ++ ){
    int st = 3 * i - 2;
    for( int j = 0 ; j < 2 ; j ++ )
      for( int k = 0 ; k < 2 ; k ++ )
        for( int l = 0 ; l < 2 ; l ++ ){
          vector<int> tv = { term( c[ 0 ][ st + j ] ) ,
                             term( c[ 1 ][ st + k ] ) ,
                             term( c[ 2 ][ st + l ] ) };
          sort( tv.begin() , tv.end() );
          eq.push_back( tv );
        }
  }
  sort( eq.begin() , eq.end() );
  eq.resize( unique( eq.begin() , eq.end() ) - eq.begin() );
  return true;
}
#define K 26
int on[ K ];
bool go( size_t now ){
  if( now == eq.size() ) return true;
  if( on[ eq[ now ][ 0 ] / 2 ] == eq[ now ][ 0 ] % 2 ||
      on[ eq[ now ][ 1 ] / 2 ] == eq[ now ][ 1 ] % 2 ||
      on[ eq[ now ][ 2 ] / 2 ] == eq[ now ][ 2 ] % 2 )
    return go( now + 1 );
  int sv[ K ];
  for( int i = 0 ; i < 3 ; i ++ )
    sv[ eq[ now ][ i ] / 2 ] = on[ eq[ now ][ i ] / 2 ];
  for( int i = 0 ; i < 3 ; i ++ ){
    on[ eq[ now ][ i ] / 2 ] = eq[ now ][ i ] % 2;
    if( sv[ eq[ now ][ i ] / 2 ] == 2 ||
        sv[ eq[ now ][ i ] / 2 ] == on[ eq[ now ][ i ] / 2 ] ){
      if( go( now + 1 ) ) return true;
    }
    on[ eq[ now ][ i ] / 2 ] = 1 - on[ eq[ now ][ i ] / 2 ];
  }
  for( int i = 0 ; i < 3 ; i ++ )
    on[ eq[ now ][ i ] / 2 ] = sv[ eq[ now ][ i ] / 2 ];
  return false;
}
inline void solve(){
  for( int i = 0 ; i < K ; i ++ ) on[ i ] = 2;
  if( go( 0 ) ){
    vector< char > ans;
    for( int i = 0 ; i < K ; i ++ )
      if( on[ i ] == 1 )
        ans.push_back( (char)( i + 'A' ) );
    printf( "%d" , (int)ans.size() );
    for( char cc : ans ) printf( " %c" , cc );
    puts( "" );
  }else puts( "-1" );
}
int main(){
  while( init() ) solve();
}
