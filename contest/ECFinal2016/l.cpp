#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
map< vector<int> , int > cnt;
vector< pair<int,int> > matches;
vector<int> sc;
void go( size_t cur ){
  if( cur == matches.size() ){
    vector<int> tmp = sc;
    cnt[ tmp ] ++;
    return;
  }
  int sc1[]={3,1,0};
  int sc2[]={0,1,3};
  for( int i = 0 ; i < 3 ; i ++ ){
    int one = matches[ cur ].first;
    int two = matches[ cur ].second;
    sc[ one ] += sc1[ i ];
    sc[ two ] += sc2[ i ];
    go( cur + 1 );
    sc[ one ] -= sc1[ i ];
    sc[ two ] -= sc2[ i ];
  }
}
void build(){
  sc.resize( 4 );
  for( int i = 0 ; i < 4 ; i ++ )
    sc[ i ] = 0;
  for( int i = 0 ; i < 4 ; i ++ )
    for( int j = i + 1 ; j < 4 ; j ++ )
      matches.push_back( {i, j} );
  go( 0 );
}
int _cs;
int main(){
  build();
  int t; scanf( "%d" , &t ); while( t -- ){
    vector<int> tmp;
    tmp.resize( 4 );
    for( int i = 0 ; i < 4 ; i ++ )
      scanf( "%d" , &tmp[ i ] );
    auto it = cnt.find( tmp );
    printf( "Case #%d: " , ++ _cs );
    if( it == cnt.end() ) puts( "Wrong Scoreboard" );
    else if( it->second > 1 ) puts( "No" );
    else puts( "Yes" );
  }
}
