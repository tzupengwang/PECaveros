#include <bits/stdc++.h>
using namespace std;
#define N 55
map< vector<vector<int>> , int > M;
vector< vector<vector<int>> > d;
int fx[ N ] , fy[ N ];
int id;
vector< vector<int> > tar;
int add( int ai , int bi ){
  if( ai == 0 ) return bi == 2 ? 1 : 0;
  if( ai == 2 ) return bi == 0 ? 1 : 0;
  return bi;
}
int n , m;
void go( vector< vector<int> > b1 , vector< vector<int> > b2 , int id1 , int id2 ){
  vector< vector<int> > ret;
  ret.resize( n );
  for( int i = 0 ; i < n ; i ++ )
    ret[ i ].resize( m );
  int gt = 0;
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < m ; j ++ ){
      ret[ i ][ j ] = add( b1[ i ][ j ] , b2[ i ][ j ] );
      if( min( b1[ i ][ j ] , b2[ i ][ j ] ) == 0 and
          max( b1[ i ][ j ] , b2[ i ][ j ] ) == 2 )
        gt ++;
      if( gt > 1 ) return;
    }
  if( M.find( ret ) != M.end() ) return;
  M[ ret ] = (int)d.size();
  fx[ d.size() ] = id1;
  fy[ d.size() ] = id2;
  d.push_back( ret );
}
bool used[ 10101010 ];
void print( vector< vector<int> > vv , int iid ){
  printf( "%d\n" , iid );
  for( auto i : vv ){
    for( auto j : i )
      printf( "%d " , j );
    puts( "" );
  }
}
void go_find( int iid ){
  if( iid == -1 ) return;
  if( used[ iid ] ) return;
  used[ iid ] = true;
  go_find( fx[ iid ] );
  go_find( fy[ iid ] );
  print( d[ iid ] , iid );
}
int main(){
  cin >> n >> m;
  vector<int> tmp;
  for( int i = 0 ; i < m ; i ++ )
    tmp.push_back( 1 );
  for( int j = 0 ; j < n ; j ++ )
    tar.push_back( tmp );
  vector< vector<int> > tv;
  tv.resize( n );
  for( int i = 0 ; i < n ; i ++ ){
    tv[ i ].resize( m );
    for( int j = 0 ; j < m ; j ++ )
      tv[ i ][ j ] = 1;
  }
  fx[ 0 ] = fy[ 0 ] = 
  fx[ 1 ] = fy[ 1 ] = -1;
  tv[ 0 ][ 0 ] = 2; 
  tv[ 0 ][ 1 ] = 2; 
  M[ tv ] = 0;
  d.push_back( tv );
  tv[ 0 ][ 0 ] = 1;
  tv[ 0 ][ 1 ] = 1;
  for( int i = 0 ; i < n ; i ++ )
    tv[ i ][ 0 ] = 0;
  M[ tv ] = 1;
  d.push_back( tv );
  int psz = 0;
  while( M.find( tar ) == M.end() ){
    int sz = d.size();
    for( int i = psz ; i < sz ; i ++ )
      for( int j = 0 ; j < sz ; j ++ )
        go( d[ i ] , d[ j ] , i , j );
    int nsz = d.size();
    if( sz == nsz ) break;
    psz = sz;
    sz = nsz;
  }
  if( M.find( tar ) == M.end() )
    puts( "gg" );
  else
    go_find( M[ tar ] );
}
