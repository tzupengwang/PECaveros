#include <bits/stdc++.h>
using namespace std;
#define N 101010
map< pair<int,int> , int > M;
set< pair<int,int> > s[ N ];
int n , k , midx;
void init(){
  scanf( "%d%d" , &n , &k );
  for( int i = 0 ; i < n ; i ++ ){
    int a[ 4 ];
    for( int j = 0 ; j < 4 ; j ++ )
      scanf( "%d" , &a[ j ] );
    if( M.count( { a[ 0 ] , a[ 1 ] } ) == 0 )
      M[ { a[ 0 ] , a[ 1 ] } ] = midx ++;
    int id = M[ { a[ 0 ] , a[ 1 ] } ];
    s[ id ].insert( { a[ 2 ] , a[ 3 ] } );
  }
}
vector< vector< int > > ans;
void solve(){
  for( int i = 0 ; i < k ; i ++ ){
    int a[ 5 ];
    for( int j = 0 ; j < 5 ; j ++ )
      scanf( "%d" , &a[ j ] );
    if( M.count( { a[ 0 ] , a[ 1 ] } ) == 0 )
      continue;
    int id = M[ { a[ 0 ] , a[ 1 ] } ];
    auto it = s[ id ].lower_bound( { a[ 3 ] , -1 } );
    if( it == s[ id ].begin() ) continue;
    it --;
    vector< int > tans;
    tans.push_back( it->second );
    tans.push_back( a[ 0 ] );
    tans.push_back( a[ 1 ] );
    tans.push_back( it->first );
    tans.push_back( a[ 2 ] );
    tans.push_back( a[ 3 ] );
    tans.push_back( a[ 4 ] );
    ans.push_back( tans );
  }
  sort( ans.begin() , ans.end() );
  printf( "%d\n" , (int)ans.size() );
  int per[] = { 1 , 2 , 3 , 0 , 4 , 5 , 6 };
  for( size_t i = 0 ; i < ans.size() ; i ++ ){
    for( size_t j = 0 ; j < ans[ i ].size() ; j ++ )
      printf( "%d%c" , ans[ i ][ per[ j ] ] , " \n"[ j + 1 == ans[ i ].size() ] );
  }
}
int main(){
  init();
  solve();
}
