#include <bits/stdc++.h>
using namespace std;
#define N 1111
typedef long long LL;
int n;
vector< LL > v[ N ];
LL gg[ N ] , ans;
void init(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ )
    v[ i ].clear();
  for( int i = 0 ; i < n ; i ++ ){
    int xi; scanf( "%d" , &xi );
    while( xi -- ){
      LL t; scanf( "%lld" , &t );
      v[ i ].push_back( t );
    }
    sort( v[ i ].begin() , v[ i ].end() );
    gg[ i ] = 0;
    for( size_t j = 1 ; j < v[ i ].size() ; j ++ )
      gg[ i ] = __gcd( gg[ i ] , v[ i ][ j ] - v[ i ][ j - 1 ] );
  }
}
int _cs;
void solve(){
  ans = 0;
  LL tsum = 0;
  for( int i = 0 ; i < n ; i ++ ){
    ans = __gcd( ans , gg[ i ] );
    tsum += v[ i ][ 0 ];
  }
  ans = __gcd( ans , tsum );
  printf( "Case #%d: %lld\n" , ++ _cs , ans );
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
