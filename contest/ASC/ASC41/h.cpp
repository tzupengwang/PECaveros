#include <bits/stdc++.h>
using namespace std;
#define N 101010
typedef long long LL;
LL n , p[ N ];
vector< pair<LL,LL> > v[ N ];
void init(){
  scanf( "%lld" , &n );
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%lld" , &p[ i ] );
  for( int i = 1 ; i < n ; i ++ ){
    LL ui , vi , li;
    scanf( "%lld%lld%lld" , &ui , &vi , &li );
    v[ ui ].push_back( { vi , li } );
    v[ vi ].push_back( { ui , li } );
  }
}
LL dp[ N ] , pp[ N ];
void go( int now , int par ){
  dp[ now ] = 0; pp[ now ] = p[ now ];
  for( auto x : v[ now ] ){
    LL son = x.first;
    LL dst = x.second;
    if( son == par ) continue;
    go( son , now );
    dp[ now ] += dp[ son ] + pp[ son ] * dst;
    pp[ now ] += pp[ son ];
  }
}
LL bst , bstf;
void go2( int now , int par , LL pdp , LL ppp ){
  if( dp[ now ] + pdp < bstf ){
    bst = now;
    bstf = dp[ now ] + pdp;
  }
  for( auto x : v[ now ] ){
    LL son = x.first;
    LL dst = x.second;
    if( son == par ) continue;
    LL ndp = pdp + dp[ now ] - dp[ son ] - pp[ son ] * dst;
    LL npp = ppp + pp[ now ] - pp[ son ];
    go2( son , now , ndp + npp * dst , npp );
  }
}
void solve(){
  go( 1 , 1 );
  bst = 1; bstf = dp[ 1 ];
  go2( 1 , 1 , 0 , 0 );
  printf( "%lld %lld\n" , bst , bstf );
}
int main(){
  freopen( "house.in" , "r" , stdin );
  freopen( "house.out" , "w" , stdout );
  init();
  solve();
}
