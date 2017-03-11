#include <bits/stdc++.h>
using namespace std;
#define N 2020202
#define M 1010101
#define X 10211
int n , m , a[ X ] , l[ X ] , r[ X ];
void init(){
  scanf( "%d%d" , &n , &m );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%d" , &a[ i ] );
  for( int i = 0 ; i < m ; i ++ )
    scanf( "%d%d" , &l[ i ] , &r[ i ] );
}
int cnt[ N ];
void solve(){
  for( int i = 0 ; i < n ; i ++ ){
    vector< pair<int,int> > inter;
    for( int j = 0 ; j < m ; j ++ ){
      int ldlt = l[ j ] - a[ i ];
      int rdlt = r[ j ] - a[ i ];
      inter.push_back( { ldlt , rdlt } );
    }
    sort( inter.begin() , inter.end() );
    size_t sz = 1;
    for( size_t j = 1 ; j < inter.size() ; j ++ )
      if( inter[ j ].first <= inter[ sz - 1 ].second + 1 )
        inter[ sz - 1 ].second = max( inter[ sz - 1 ].second ,
                                      inter[ j ].second );
      else
        inter[ sz ++ ] = inter[ j ];
    inter.resize( sz );
    for( auto ii : inter ){
      cnt[ M + ii.first ] ++;
      cnt[ M + ii.second + 1 ] --;
    }
  }
  int bst = 0 , shift = 0;
  for( int i = 1 ; i < N ; i ++ ){
    cnt[ i ] += cnt[ i - 1 ];
    if( cnt[ i ] > bst or
        ( cnt[ i ] == bst and
          abs( i - M ) < shift ) ){
      bst = cnt[ i ];
      shift = abs( i - M );
    }
  }
  printf( "%d %d\n" , shift , bst );
}
int main(){
#ifndef LOCAL
  freopen( "input.txt" , "r" , stdin );
  freopen( "output.txt" , "w" , stdout );
#endif
  init();
  solve();
}
