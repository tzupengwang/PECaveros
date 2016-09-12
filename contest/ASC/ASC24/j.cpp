#include <bits/stdc++.h>
using namespace std;
#define N 101010
int n , k , ui[ N ] , vi[ N ];
bool block[ N ];
vector< pair< int , int > > v[ N ];
void init(){
  scanf( "%d%d" , &n , &k );
  for( int i = 1 ; i < n ; i ++ ){
    scanf( "%d%d" , &ui[ i ] , &vi[ i ] );
    v[ ui[ i ] ].push_back( { vi[ i ] , i } );
    v[ vi[ i ] ].push_back( { ui[ i ] , i } );
  }
}
int sz[ N ];
void dfs( int now , int prt ){
  sz[ now ] = 1;
  vector< pair<int,int> > res;
  for( pair<int,int> tp : v[ now ] ){
    int tson = tp.first;
    int id   = tp.second;
    if( tson == prt || block[ id ] ) continue;
    dfs( tson , now );
    res.push_back( { sz[ tson ] , id } );
  }
  if( res.empty() ) return;
  if( (int)res.size() == 1 ){
    if( res[ 0 ].first == k )
      block[ res[ 0 ].second ] = true;
    else
      sz[ now ] += res[ 0 ].first;
  }else{
    if( res[ 0 ].first + res[ 1 ].first + 1 <= k ){
      sz[ now ] += res[ 0 ].first + res[ 1 ].first;
    }else if( res[ 0 ].first + 1 <= k ){
      sz[ now ] += res[ 0 ].first;
      block[ res[ 1 ].second ] = true;
    }else if( res[ 1 ].first + 1 <= k ){
      sz[ now ] += res[ 1 ].first;
      block[ res[ 0 ].second ] = true;
    }else{
      block[ res[ 0 ].second ] = true;
      block[ res[ 1 ].second ] = true;
    }
  }
}
void solve(){
  dfs( 1 , 1 );
  vector< int > vv;
  for( int i = 1 ; i < n ; i ++ )
    if( block[ i ] )
      vv.push_back( i );
  sort( vv.begin() , vv.end() );
  if( (int)vv.size() > ( 2 * n + k - 1 ) / k ){
    puts( "-1" );
    exit( 0 );
  }
  printf( "%d\n" , (int)vv.size() );
  for( size_t i = 0 ; i < vv.size() ; i ++ )
    printf( "%d%c" , vv[ i ] , " \n"[ i + 1 == vv.size() ] );
}
int main(){
  freopen( "tree.in" , "r" , stdin );
  freopen( "tree.out" , "w" , stdout );
  init();
  solve();
}
