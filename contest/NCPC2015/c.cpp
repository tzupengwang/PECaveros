#include <bits/stdc++.h>
using namespace std;
#define N 110
#define inf 1000000000
vector<int> v[ N ];
int __ = 1 , n , p[ N ];
int dp[ N ][ 3 ];
void init(){
  scanf( "%d" , &n );
  for( int i = 1 ; i <= n ; i ++ )
    v[ i ].clear();
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%d" , &p[ i ] );
    if( i > 1 )
      v[ p[ i ] ].push_back( i );
  }
}
void DFS( int now ){
  dp[ now ][ 0 ] = 1;
  dp[ now ][ 1 ] = inf;
  dp[ now ][ 2 ] = inf;
  vector<int> tv;
  int tsum = 0;
  for( int i = 0 ; i < (int)v[ now ].size() ; i ++ ){
    DFS( v[ now ][ i ] );
    tsum += min( dp[ v[ now ][ i ] ][ 0 ] ,
                 dp[ v[ now ][ i ] ][ 2 ] );
    dp[ now ][ 0 ] += min( dp[ v[ now ][ i ] ][ 0 ],
                           dp[ v[ now ][ i ] ][ 1 ] );
    if( dp[ v[ now ][ i ] ][ 0 ] >
        dp[ v[ now ][ i ] ][ 2 ] )
      tv.push_back( dp[ v[ now ][ i ] ][ 0 ] -
                    dp[ v[ now ][ i ] ][ 2 ] );
  }
  sort( tv.begin() , tv.end() );
  int now0 = (int)v[ now ].size() - (int)tv.size();
  int ptr = 0;
  if( (int)v[ now ].size() >= 1 ){
    if( now0 < 1 ){
      now0 ++;
      tsum += tv[ ptr ++ ];
    }
    dp[ now ][ 1 ] = tsum;
    if( (int)v[ now ].size() >= 2 ){
      if( now0 < 2 ){
        now0 ++;
        tsum += tv[ ptr ++ ];
      }
      dp[ now ][ 2 ] = tsum;
    }
  }
}
void solve(){
  DFS( 1 );
  printf( "%d\n" , min( dp[ 1 ][ 0 ] , dp[ 1 ][ 2 ] ) );
}
int main(){
  scanf( "%d" , &__ ); while( __ -- ){
    init();
    solve();
  }
}
