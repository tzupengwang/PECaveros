#include <bits/stdc++.h>
using namespace std;
#define N 101010
#define K 20
#define PB push_back
char c[ N ];
int p[ N ][ K ];
int nxt[ 4 ];
int trans( char ctmp ){
  if( ctmp == 'e' ) return 0;
  if( ctmp == 'a' ) return 1;
  if( ctmp == 's' ) return 2;
  if( ctmp == 'y' ) return 3;
  return 4;
}
int n , dep[ N ] , nxte[ N ];
vector<int> root;
void build(){
  for( int j = 1 ; j < K ; j ++ )
    for( int i = 1 ; i <= n ; i ++ )
      p[ i ][ j ] = p[ p[ i ][ j - 1 ] ][ j - 1 ];
}
void init(){
  scanf( "%s" , c + 1 );
  n = strlen( c + 1 );
  for( int i = 1 ; i <= n ; i ++ ) p[ i ][ 0 ] = i;
  for( int i = n ; i >= 1 ; i -- ){
    int now = trans( c[ i ] );
    int tnxt = ( now + 1 ) % 4;
    if( nxt[ tnxt ] ){
      p[ i ][ 0 ] = nxt[ tnxt ];
      dep[ i ] = dep[ nxt[ tnxt ] ] + 1;
    }else if( now == 3 ){
      root.PB( i );
      dep[ i ] = 1;
    }
    nxt[ now ] = i;
    nxte[ i ] = nxt[ 0 ];
  }
  build();
}
int query( int li , int ri ){
  int st = nxte[ li ];
  int aa = st;
  for( int i = K - 1 ; i >= 0 ; i -- )
    if( p[ aa ][ i ] <= ri )
      aa = p[ aa ][ i ];
  return ( dep[ st ] - dep[ aa ] + 1 ) / 4;
}
void solve(){
  int q; scanf( "%d" , &q );
  while( q -- ){
    int li , ri;
    scanf( "%d%d" , &li , &ri );
    printf( "%d\n" , query( li , ri ) );
  }
}
int main(){
  init();
  solve();
}
