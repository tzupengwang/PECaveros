#include <bits/stdc++.h>
using namespace std;
#define N 101010
#define K 20
int n , m , p[ N ][ K ] , dep[ N ];
vector< int > v[ N ];
inline int lca( int ai , int bi ){
  if( dep[ ai ] > dep[ bi ] ) swap( ai , bi );
  int dlt = dep[ bi ] - dep[ ai ];
  for( int i = 0 ; i < K ; i ++ )
    if( ( dlt >> i ) & 1 )
      bi = p[ bi ][ i ];
  if( ai == bi ) return ai;
  for( int i = K - 1 ; i >= 0 ; i -- )
    if( p[ ai ][ i ] != p[ bi ][ i ] ){
      ai = p[ ai ][ i ];
      bi = p[ bi ][ i ];
    }
  return p[ ai ][ 0 ];
}
void init(){
  scanf( "%d%d" , &n , &m );
  p[ 1 ][ 0 ] = 1;
  for( int i = 2 ; i <= n ; i ++ ){
    scanf( "%d" , &p[ i ][ 0 ] );
    v[ p[ i ][ 0 ] ].push_back( i );
    dep[ i ] = dep[ p[ i ][ 0 ] ] + 1;
  }
  for( int j = 1 ; j < K ; j ++ )
    for( int i = 1 ; i <= n ; i ++ )
      p[ i ][ j ] = p[ p[ i ][ j - 1 ] ][ j - 1 ];
}
int no[ N ] , from[ N ] , sz[ N ] , ncnt;
int who[ N ];
void go( int now , int fr ){
  from[ now ] = fr;
  if( v[ now ].empty() ){
    no[ now ] = ++ ncnt;
    who[ ncnt ] = now;
    sz[ now ] = 1;
    return;
  }
  for( int son : v[ now ] ){
    go( son , fr );
    sz[ now ] += sz[ son ];
  }
}
set< int > S[ N ];
int cans , ans , got[ N ] , tans[ N ];
inline void add( int id ){
  int pid = from[ id ];
  got[ pid ] ++;
  if( got[ pid ] == 1 ) cans ++;
  S[ pid ].insert( no[ id ] );
  int lft = *S[ pid ].begin();
  int rgt = *--S[ pid ].end();
  int tlca = lca( who[ lft ] , who[ rgt ] );
  ans -= tans[ pid ];
  tans[ pid ] = sz[ tlca ] - got[ pid ];
  ans += tans[ pid ];
}
inline void bye( int id ){
  int pid = from[ id ];
  got[ pid ] --;
  if( got[ pid ] == 0 ) cans --;
  S[ pid ].erase( no[ id ] );
  ans -= tans[ pid ];
  if( got[ pid ] == 0 )
    tans[ pid ] = 0;
  else{
    int lft = *S[ pid ].begin();
    int rgt = *--S[ pid ].end();
    int tlca = lca( who[ lft ] , who[ rgt ] );
    tans[ pid ] = sz[ tlca ] - got[ pid ];
  }
  ans += tans[ pid ];
}
void solve(){
  for( int son : v[ 1 ] )
    go( son , son );
  while( m -- ){
    char cmd[ 9 ]; int id;
    scanf( "%s%d" , cmd , &id );
    if( cmd[ 0 ] == '+' ) add( id );
    else bye( id );
    printf( "%d %d\n" , cans , ans );
  }
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "gangsters.in" , "r" , stdin );
  freopen( "gangsters.out" , "w" , stdout );
#endif
  init();
  solve();
}
