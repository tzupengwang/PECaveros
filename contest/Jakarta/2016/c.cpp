#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 10210
vector<int> v[ N ];
int n , m , ind[ N ];
LL lx , rx , b[ N ] , k[ N ];
const int inf = 1000000;
void init(){
  scanf( "%d%d" , &n , &m );
  lx = -inf; rx = inf;
  for( int i = 1 ; i <= n ; i ++ ){
    v[ i ].clear();
    ind[ i ] = 0;
  }
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%lld%lld" , &b[ i ] , &k[ i ] );
    // 1 <= b[ i ] + k[ i ] x <= 50000
    if( k[ i ] > 0 ){
      while( lx <= rx and b[ i ] + k[ i ] * lx < 1 ) lx ++;
      while( lx <= rx and b[ i ] + k[ i ] * rx > 50000 ) rx --;
      //int tlx = ( 1     - b[ i ] + k[ i ] - 1 ) / k[ i ];
      //int trx = ( 50000 - b[ i ] ) / k[ i ];
      //lx = max( lx , tlx );
      //rx = min( rx , trx );
    }
    if( k[ i ] < 0 ){
      while( lx <= rx and b[ i ] + k[ i ] * lx > 50000 ) lx ++;
      while( lx <= rx and b[ i ] + k[ i ] * rx < 1 ) rx --;
      //int tlx = ( b[ i ] - 50000 + k[ i ] - 1 ) / abs( k[ i ] );
      //int trx = ( b[ i ] - 1 ) / abs( k[ i ] );
      //lx = max( lx , tlx );
      //rx = min( rx , trx );
    }
  }
  while( m -- ){
    int aa , bb;
    scanf( "%d%d" , &aa , &bb );
    v[ aa ].push_back( bb );
    ind[ bb ] ++;
  }
}
vector<int> topo;
LL d[ N ];
LL cal( int curx ){
  for( int i = 1 ; i <= n ; i ++ )
    d[ i ] = b[ i ] + k[ i ] * curx;
  for( auto i : topo )
    for( int nxt : v[ i ] )
      d[ nxt ] = max( d[ nxt ] , d[ i ] + b[ nxt ] + k[ nxt ] * curx );
  return *max_element( d + 1 , d + n + 1 );
}
int _cs;
void solve(){
  topo.clear();
  for( int i = 1 ; i <= n ; i ++ )
    if( ind[ i ] == 0 )
      topo.push_back( i );
  for( size_t i = 0 ; i < topo.size() ; i ++ ){
    int now = topo[ i ];
    for( int nxt : v[ now ] ){
      ind[ nxt ] --;
      if( ind[ nxt ] == 0 )
        topo.push_back( nxt );
    }
  }
  LL ans = 1000000000000000LL;
  while( lx <= rx ){
    if( rx - lx <= 10 ){
      for( int i = lx ; i <= rx ; i ++ )
        ans = min( ans , cal( i ) );
      break;
    }
    int mid1 = lx + ( rx - lx ) / 3;
    int mid2 = rx - ( rx - lx ) / 3;
    LL lans = cal( mid1 );
    LL rans = cal( mid2 );
    if( lans < rans ){
      ans = min( ans , lans );
      rx = mid2 - 1;
    }else{
      ans = min( ans , rans );
      lx = mid1 + 1;
    }
  }
  printf( "Case #%d: %lld\n" , ++ _cs , ans );
}
int main(){
  int t; scanf( "%d" , &t ); while( t -- ){
    init();
    solve();
  }
}
