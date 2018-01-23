#include <bits/stdc++.h>
using namespace std;
#define N 111
int w , h , n;
int x[ N ] , y[ N ] , r[ N ];
void init(){
  scanf( "%d%d%d" , &w , &h , &n );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%d%d%d" , &x[ i ] , &y[ i ] , &r[ i ] );
}
inline int cal( int nx ){
  vector< pair<int,int> > hh;
  for( int i = 0 ; i < n ; i ++ ){
    int dltx = abs( nx - x[ i ] );
    if( dltx > r[ i ] ) continue;
    int dlty = sqrt( (long long)r[ i ] * r[ i ] - (long long)dltx * dltx );
    int yu = max( 0 , y[ i ] - dlty );
    int yd = min( h - 1 , y[ i ] + dlty );
    if( yu <= yd ) hh.push_back( { yu , yd } );
  }
  sort( hh.begin() , hh.end() );
  if( hh.empty() ) return 0;
  size_t sz = 1;
  for( size_t i = 1 ; i < hh.size() ; i ++ )
    if( hh[ i ].first <= hh[ sz - 1 ].second )
      hh[ sz - 1 ].second = max( hh[ sz - 1 ].second , hh[ i ].second );
    else
      hh[ sz ++ ] = hh[ i ];
  hh.resize( sz );
  int tot = 0;
  for( auto i : hh )
    tot += i.second - i.first + 1;
  return tot;
}
void solve(){
  int ans = 0;
  for( int i = 0 ; i < w ; i ++ )
    ans += cal( i );
  printf( "%d\n" , w * h - ans );
}
int main(){
  freopen( "circles.in" , "r" , stdin );
  freopen( "circles.out" , "w" , stdout );
  init();
  solve();
}
