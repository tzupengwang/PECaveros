#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 514
LL n , x[ N ] , y[ N ];
int good[ N ][ N ];
void init(){
  scanf( "%lld" , &n );
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%lld" , &x[ i ] );
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%lld" , &y[ i ] );
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= n ; j ++ )
      scanf( "%d" , &good[ i ][ j ] );
}
vector< LL > cand;
vector< pair< LL , int > > info;
LL sqr( LL u ){ return u * u; }
LL dist( int id1 , int id2 ){
  return sqr( x[ id1 ] - x[ id2 ] ) +
         sqr( y[ id1 ] - y[ id2 ] );
}
int _cs;
void solve(){
  cand.clear();
  info.clear();
  LL sum[ 2 ] = {} , cnt[ 2 ] = {};
  cand.push_back( 0 );
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= n ; j ++ ){
      LL dd = dist( i , j );
      cand.push_back( dd );
      info.push_back( { dd , good[ i ][ j ] } );
      sum[ good[ i ][ j ] ] ++;
    }
  sort( cand.begin() , cand.end() );
  cand.resize( unique( cand.begin() , cand.end() ) - cand.begin() );
  sort( info.begin() , info.end() );
  LL bst = n * n * n , bi = -1;
  size_t ptr = 0;
  for( auto i : cand ){
    while( ptr < info.size() &&
           info[ ptr ].first <= i ){
      cnt[ info[ ptr ].second ] ++;
      ptr ++;
    }
    LL bad = cnt[ 0 ] + sum[ 1 ] - cnt[ 1 ];
    if( bad < bst ){
      bst = bad;
      bi = i;
    }
  }
  printf( "Case #%d: %lld %lld\n" , ++ _cs , bi , bst );
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
