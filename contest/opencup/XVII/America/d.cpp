#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 200020
int n , v[ N ] , p[ N ] , sz;
int d[ N ] ;
vector<int> s[ N ];
typedef pair< int , int > ii ;

void init(){
  d[ 0 ] = 0 ;
  scanf( "%d" , &n );
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%d%d" , &v[ i ] , &p[ i ] );
    d[ i ] = d[ p[ i ] ] + 1 ;
    if( p[ i ] )
      s[ p[ i ] ].push_back( i );
  }
  vector<int> vv;
  for( int i = 1 ; i <= n ; i ++ )
    vv.push_back( i );
  sort( vv.begin() , vv.end() , [&]( int i , int j ) {
        if ( v[ i ] != v[ j ] ) return v[ i ] <= v[ j ] ;
        return d[ i ] 
        });
  vv.resize( unique( vv.begin() , vv.end() ) - vv.begin() );
  for( int i = 1 ; i <= n ; i ++ )
    v[ i ] = lower_bound( vv.begin() , vv.end() , v[ i ] ) - vv.begin() + 1;
  sz = (int)vv.size();
}

void solve(){
  int ans = 1;
  for( int i = n ; i >= 1 ; i -- ){
    root[ i ] = -1;
    for( int son : s[ i ] ){
      if( root[ i ] == -1 )
        root[ i ] = root[ son ];
      else
        root[ i ] = merge( root[ i ] , root[ son ] , 1 , sz );
      //if( i == 1 ) print( root[ i ] , 1 , sz );
      //puts( "====" );
    }
    if( root[ i ] == -1 ) root[ i ] = new_node();
    int bst = 1 + query( root[ i ] , 1 , sz , 1 , v[ i ] - 1 );
    int pos = query2( root[ i ] , 1 , sz , bst );
    //printf( "%d : \n" , i );
    if( v[ i ] <= pos ){
      //printf( "Assign %d %d -> %d\n" , v[ i ] , pos , bst );
      asgn( root[ i ] , 1 , sz , v[ i ] , pos , bst );
    }
    ans = max( ans , bst );
    ans = max( ans , query( root[ i ] , 1 , sz , 1 , sz ) );
  }
  printf( "%d\n" , ans );
}
int main(){
  init();
  solve();
}
