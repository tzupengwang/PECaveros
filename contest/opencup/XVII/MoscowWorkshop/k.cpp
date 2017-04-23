#include <bits/stdc++.h>
using namespace std;
#define N 202020
typedef long long LL;
int n;
vector< pair<int,LL> > v[ N ];
int kd[ N ];
void init(){
  scanf( "%d" , &n );
  for( int i = 1 ; i < n ; i ++ ){
    int ui , vi , wi;
    scanf( "%d%d%d" , &ui , &vi , &wi );
    v[ ui ].push_back( { vi , wi } );
    v[ vi ].push_back( { ui , wi } );
  }
  for( int i = 1 ; i <= 2 ; i ++ ){
    int m , x; scanf( "%d" , &m ); while( m -- ){
      scanf( "%d" , &x );
      kd[ x ] = i;
    }
  }
}
const LL inf = 10000000000000000LL;
LL dp[ N ][ 3 ];
void DP( int now , int prt ){
  if( kd[ now ] ){
    dp[ now ][ 0 ] = inf;
    dp[ now ][ 3 - kd[ now ] ] = inf;
  }
  for( auto i : v[ now ] ){
    int son = i.first;
    LL wt = i.second;
    if( son == prt ) continue;
    DP( son , now );
    LL bst = inf;
    for( int clr = 0 ; clr < 3 ; clr ++ )
      bst = min( bst , dp[ son ][ clr ] );
    for( int clr = 0 ; clr < 3 ; clr ++ ){
      if( dp[ now ][ clr ] == inf ) continue;
      if( clr == 0 )
        dp[ now ][ clr ] += min( bst + wt , dp[ son ][ clr ] );
      else{
        dp[ now ][ clr ] += min( bst + wt , min( dp[ son ][ 0 ] ,
                                                 dp[ son ][ clr ] ) );
      }
    }
  }
}
void solve(){
  DP( 1 , 1 );
  LL ans = inf;
  for( int i = 0 ; i < 3 ; i ++ )
    ans = min( ans , dp[ 1 ][ i ] );
  printf( "%lld\n" , ans );
}
int main(){
  init();
  solve();
}
