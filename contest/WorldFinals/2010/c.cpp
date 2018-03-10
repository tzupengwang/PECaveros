#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 1021
int m , n , w , lx[ N ] , rx[ N ] , y[ N ];
vector<int> lix , liy;
void uniq( vector<int>& li ){
  sort( li.begin() , li.end() );
  li.resize( unique( li.begin() , li.end() ) - li.begin() );
}
void init(){
  lix.clear();
  liy.clear();
  for( int i = 0 ; i < w ; i ++ ){
    scanf( "%d%d" , &lx[ i ] , &y[ i ] );
    scanf( "%d%d" , &rx[ i ] , &y[ i ] );
    lix.push_back( lx[ i ]     );
    lix.push_back( rx[ i ] + 1 );
    liy.push_back( y[ i ] );
    liy.push_back( y[ i ] + 1 );
  }
  lix.push_back( 0 );
  lix.push_back( n );
  liy.push_back( 0 );
  liy.push_back( m );
  uniq( lix );
  uniq( liy );
}
bool ok[ 2 ][ N + N ];
int blk[ N + N ];
int id[ N ];
bool cmp( int id1 , int id2 ){
  return y[ id1 ] > y[ id2 ];
}
int _cs;
void solve(){
  for( int i = 0 ; i < w ; i ++ ){
    lx[ i ] = lower_bound( lix.begin() , lix.end() , lx[ i ]     ) - lix.begin();
    rx[ i ] = lower_bound( lix.begin() , lix.end() , rx[ i ] + 1 ) - lix.begin();
    y[ i ] = lower_bound( liy.begin() , liy.end() , y[ i ] ) - liy.begin();
    id[ i ] = i;
  }
  sort( id , id + w , cmp );
  int lst = 0 , pre = 1 , ptr = 0;
  for( size_t i = 0 ; i + 1 < lix.size() ; i ++ )
    ok[ lst ][ i ] = false;
  ok[ lst ][ lix.size() - 2u ] = true;
  LL ans = 0;
  for( int j = (int)liy.size() - 2 ; j >= 0 ; j -- ){
    swap( lst , pre );
    for( size_t i = 0 ; i < lix.size() ; i ++ ){
      blk[ i ] = 0;
      ok[ lst ][ i ] = false;
    }
    while( ptr < w and y[ id[ ptr ] ] == j ){
      int lb = lx[ id[ ptr ] ];
      int rb = rx[ id[ ptr ] ];
      blk[ lb ] ++;
      blk[ rb ] --;
      ptr ++;
    }
    for( size_t i = 1 ; i < lix.size() ; i ++ )
      blk[ i ] += blk[ i - 1 ];
    for( int i = (int)lix.size() - 2 ; i >= 0 ; i -- ){
      if( blk[ i ] ) continue;
      ok[ lst ][ i ] = ok[ pre ][ i ] or ok[ lst ][ i + 1 ];
      if( not ok[ lst ][ i ] )
        ans += (LL)(liy[ j + 1 ] - liy[ j ]) *
               (LL)(lix[ i + 1 ] - lix[ i ]);
    }
  }
  printf( "Case %d: %lld\n" , ++ _cs , ans );
}
int main(){
  while( scanf( "%d%d%d" , &m , &n , &w ) == 3 and m ){
    init();
    solve();
  }
}
