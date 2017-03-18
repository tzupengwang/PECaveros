#include <bits/stdc++.h>
using namespace std;
#define N 101010
int id[ N ] , b , m , iid , who[ N ];
void go( int bt , const vector<int>& vv ){
  if( vv.empty() ) return;
  if( bt == b ){
    for( auto i : vv )
      id[ i ] = iid;
    who[ iid ] = vv[ 0 ];
    iid ++;
    return;
  }
  vector< pair<int,int> > vvv;
  for( auto i : vv )
    vvv.push_back( { ( i * b + bt ) % m , i } );
  sort( vvv.begin() , vvv.end() );
  for( size_t l = 0 , r = 0 ; l < vvv.size() ; l = r ){
    while( r < vvv.size() and vvv[ l ].first == vvv[ r ].first ) r ++;
    vector<int> tv;
    for( size_t i = l ; i < r ; i ++ )
      tv.push_back( vvv[ i ].second );
    go( bt + 1 , tv );
  }
}
int main(){
  scanf( "%d%d" , &b , &m );
  vector<int> v;
  for( int i = 1 ; i < m ; i ++ )
    v.push_back( i );
  id[ 0 ] = iid ++;
  go( 0 , v );
  printf( "%d %d\n" , iid , 0 );
  for( int i = 0 ; i < iid ; i ++ )
    printf( "%c%c" , "BG"[ i == 0 ] , " \n"[ i + 1 == iid ] );
  for( int i = 0 ; i < iid ; i ++ ){
    for( int j = 0 ; j < b ; j ++ )
      printf( "%d%c" , id[ ( who[ i ] * b + j ) % m ] , " \n"[ j + 1 == b ] );
  }
}
