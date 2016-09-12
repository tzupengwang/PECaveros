#include <bits/stdc++.h>
using namespace std;
#define N 333
int n , cnt[ N ];
vector< vector<int> > v , v2;
int at[ N ][ N ];
void build(){
  at[ 1 ][ 1 ] = n - 1;
  for( int i = 2 ; i <= n ; i ++ ){
    at[ i ][ i - 1 ] = i - 1;
    at[ i ][ i ] = n - i;
  }
}
void init(){
  scanf( "%d" , &n );
  for( int i = 1 ; i <= n ; i ++ ){
    vector< int > tv;
    for( int j = 1 ; j < n ; j ++ ){
      int x; scanf( "%d" , &x );
      tv.push_back( x );
      if( x == 1 ) cnt[ j ] ++;
    }
    v.push_back( tv );
  }
  sort( v.begin() , v.end() );
}
inline int where(){
  for( int i = 1 ; i <= n ; i ++ ){
    bool okay = true;
    for( int j = 1 ; j <= n ; j ++ )
      if( cnt[ j ] != at[ i ][ j ] ){
        okay = false;
        break;
      }
    if( okay ) return i;
  }
  return -1;
}
void check( const vector< int >& tmp ){
  v2.clear();
  for( int i = 0 ; i < n ; i ++ ){
    vector< int > tv;
    int bye = tmp[ i ];
    for( int j = 0 ; j < n ; j ++ ){
      if( i == j ) continue;
      tv.push_back( tmp[ j ] > bye ? tmp[ j ] - 1 : tmp[ j ] );
    }
    v2.push_back( tv );
  }
  sort( v2.begin() , v2.end() );
  if( v == v2 ){
    for( size_t i = 0 ; i < tmp.size() ; i ++ )
      printf( "%d%c" , tmp[ i ] , " \n"[ i + 1 == tmp.size() ] );
    exit( 0 );
  }
}
void go( int id ){
  int ii = -1;
  for( size_t i = 0 ; i < v[ id ].size() ; i ++ )
    if( v[ id ][ i ] == 1 ){
      ii = i + 1;
      break;
    }
  cnt[ ii ] --;
  int pos = where();
  cnt[ ii ] ++;
  if( pos == -1 ) return;
  vector< int > tmp;
  for( size_t i = 0 ; i < v[ id ].size() ; i ++ ){
    if( (int)i + 1 == pos ) tmp.push_back( 1 );
    tmp.push_back( v[ id ][ i ] + 1 );
  }
  if( pos == n ) tmp.push_back( 1 );
  check( tmp );
}
void solve(){
  build();
  for( size_t i = 0 ; i < v.size() ; i ++ )
    go( i );
}
int main(){
  freopen( "permutation.in" , "r" , stdin );
  freopen( "permutation.out" , "w" , stdout );
  init();
  solve();
}
