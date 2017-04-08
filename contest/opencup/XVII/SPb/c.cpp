#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 103
int n , r , ind[ N ];
int neg( int x ){
  return x <= n ? x + n : x - n;
}
int idx( int x ){
  return x < 0 ? abs( x ) + n : x;
}
vector<int> g[ N ];
bitset<N> gt[ N ] , rg[ N ];
void init(){
  scanf( "%d%d" , &n , &r );
  for( int i = 1 ; i <= n + n ; i ++ )
    gt[ i ].reset();
  while( r -- ){
    int ai , bi;
    scanf( "%d%d" , &ai , &bi );
    ai = idx( ai );
    bi = idx( bi );
    g[ neg( ai ) ].push_back( bi );
    g[ neg( bi ) ].push_back( ai );
    ind[ bi ] ++;
    ind[ ai ] ++;
    gt[ neg( ai ) ][ bi ] = 1;
    gt[ neg( bi ) ][ ai ] = 1;
    rg[ bi ][ neg( ai ) ] = 1;
    rg[ ai ][ neg( bi ) ] = 1;
  }
  for( int i = 1 ; i <= n + n ; i ++ )
    gt[ i ][ i ] = 1;
  for( int i = 0 ; i < n + n ; i ++ )
    for( int j = 1 ; j <= n + n ; j ++ )
      for( int nxt : g[ j ] ){
        gt[ j ] |= gt[ nxt ];
        rg[ nxt ] |= rg[ j ];
      }
}
LL ans = 1;
bool tag[ N ];
vector<int> cand;
void go( int now ){
  if( now > n ) now -= n;
  if( tag[ now ] ) return;
  tag[ now ] = true;
  cand.push_back( now );
  for( int nxt : g[ now ] )
    go( nxt );
  for( int nxt : g[ now + n ] )
    go( nxt );
}
LL go( size_t now , const bitset<N>& fix ,
                    const bitset<N>& ban ){
  LL tans = 0;
  if( now == cand.size() or (int)fix.count() == n )
    return 1;
  if( ban[ cand[ now ] ] or ban[ neg( cand[ now ] ) ] )
    return go( now + 1 , fix , ban );
  if( fix[ cand[ now ] ] or fix[ neg( cand[ now ] ) ] )
    return go( now + 1 , fix , ban );
  for( int dlt : { 0 , n } ){
    int tn = cand[ now ] + dlt;
    if( fix[ neg( tn ) ] ) continue;
    if( ban[ tn ] ) continue;
    bitset<N> nxt = fix | gt[ tn ];
    bitset<N> nban = ban | rg[ neg( tn ) ];
    if( ( nxt & nban ).count() > 0 )
      continue;
    if( ( nxt & ( nxt >> n ) ).count() > 0 )
      continue;
    if( ( nban & ( nban >> n ) ).count() > 0 )
      continue;
    tans += go( now + 1 , nxt , nban );
  }
  return tans;
}
void ssolve(){
  bitset<N> fix;
  bitset<N> ban;
  fix.reset();
  ban.reset();
  ans *= go( 0 , fix , ban );
}
void solve(){
  for( int i = 1 ; i <= n ; i ++ )
    if( gt[ i ][ neg( i ) ] and
        gt[ neg( i ) ][ i ] ){
      puts( "0" );
      exit( 0 );
    }
  for( int i = 1 ; i <= n ; i ++ )
    if( not tag[ i ] ){
      cand.clear();
      go( i );
      ssolve();
    }
  printf( "%lld\n" , ans );
}
int main(){
  init();
  solve();
}
