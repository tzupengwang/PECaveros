#include <bits/stdc++.h>
using namespace std;
#define N 505050
#define SN 800
#define K 20
typedef long long LL;
const LL mod7 = 1000000007;
int n , p[ N ][ K ];
LL v[ N ] , ov[ N ];
int l[ N ] , r[ N ] , stmp;
vector< int > son[ N ];
void init(){
  scanf( "%d" , &n );
  for( int i = 1 ; i < n ; i ++ ){
    int ui , vi;
    scanf( "%d%d" , &ui , &vi );
    p[ vi ][ 0 ] = ui;
    son[ ui ].push_back( vi );
  }
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%lld" , &v[ i ] );
}
int dep[ N ];
void go( int now , LL ps , int tdep ){
  l[ now ] = ++ stmp;
  ps += v[ now ];
  ov[ now ] = ps;
  dep[ now ] = tdep;
  for( int s : son[ now ] )
    go( s , ps , tdep + 1 );
  r[ now ] = stmp;
}
inline int lca( int ai , int bi ){
  if( dep[ ai ] > dep[ bi ] ) swap( ai , bi );
  int dlt = dep[ bi ] - dep[ ai ];
  for( int i = 0 ; i < K ; i ++ )
    if( ( dlt >> i ) & 1 )
      bi = p[ bi ][ i ];
  if( ai == bi ) return ai;
  for( int i = K - 1 ; i >= 0 ; i -- )
    if( p[ ai ][ i ] !=
        p[ bi ][ i ] ){
      ai = p[ ai ][ i ];
      bi = p[ bi ][ i ];
    }
  return p[ ai ][ 0 ];
}
LL sum[ SN ] , ss[ N ];
inline void add( int xi , LL dlt ){
  v[ xi ] += dlt;
  ss[ l[ xi ] ] += dlt;
  sum[ l[ xi ] / SN ] += dlt;
  if( r[ xi ] == n - 1 ) return;
  ss[ r[ xi ] + 1 ] -= dlt;
  sum[ ( r[ xi ] + 1 ) / SN ] -= dlt;
}
inline LL query( int who ){
  LL ret = ov[ who ];
  for( int i = 0 ; i < l[ who ] / SN ; i ++ )
    ret += sum[ i ];
  for( int i = l[ who ] ; i >= 0 && i / SN == l[ who ] / SN ; i -- )
    ret += ss[ i ];
  return ret;
}
void solve(){
  stmp = -1;
  go( 0 , 0 , 0 );
  for( int i = 1 ; i < K ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      p[ j ][ i ] = p[ p[ j ][ i - 1 ] ][ i - 1 ];
  int q; scanf( "%d" , &q ); while( q -- ){
    int k , x1 , y1 , a , b , c , d , qu , qv;
    scanf( "%d%d%d%d%d%d%d%d%d" , &k , &x1 , &y1 , &a , &b , &c , &d , &qu , &qv );
    for( int i = 0 ; i < k ; i ++ ){
      add( x1 , y1 );
      x1 = ( (LL)a * x1 + (LL)b ) % n;
      y1 = ( (LL)c * y1 + (LL)d ) % mod7;
    }
    int tlca = lca( qu , qv );
    LL su = query( qu );
    LL sv = query( qv );
    LL sl = query( tlca );
    LL ans = su + sv - 2 * sl + v[ tlca ];
    printf( "%lld\n" , ans );
  }
}
int main(){
  init();
  solve();
}
