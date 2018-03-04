#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 52
int n , m;
char c[ N ][ N ];
pair<int,int> nxt[ N ][ N ][ 4 ];
int dn[]={0,0,1,-1};
int dm[]={1,-1,0,0};
bool in( int xn , int xm ){
  return 0 <= xn and xn < n and
         0 <= xm and xm < m;
}
pair<int,int> next( int xn , int xm , int dir ){
  char cc = c[ xn ][ xm ];
  while( true ){
    xn += dn[ dir ];
    xm += dm[ dir ];
    if( not in( xn , xm ) )
      return {-1, -1};
    if( c[ xn ][ xm ] != cc )
      return {xn, xm};
  }
}
#define K 10005
char goal[ K ];
bool gt[ N ][ N ][ K ];
typedef pair<LL, tuple<int,int,int>> dat;
int glen;
int main(){
  scanf( "%d%d" , &n , &m );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%s" , c[ i ] );
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < m ; j ++ )
      for( int dir = 0 ; dir < 4 ; dir ++ ){
        nxt[ i ][ j ][ dir ] = next( i , j , dir );
      }
  scanf( "%s" , goal );
  glen = strlen( goal );
  goal[ glen ++ ] = '*';
  queue< dat> Q;
  gt[ 0 ][ 0 ][ 0 ] = true;
  Q.push( {0, make_tuple(0, 0, 0)} );
  while( Q.size() ){
    dat td = Q.front(); Q.pop();
    LL nd = td.first;
    int cn = get<0>( td.second );
    int cm = get<1>( td.second );
    int cg = get<2>( td.second );
    if( cg == glen ){
      printf( "%lld\n" , nd );
      exit(0);
    }
    if( c[ cn ][ cm ] == goal[ cg ] ){
      if( not gt[ cn ][ cm ][ cg + 1 ] ){
        gt[ cn ][ cm ][ cg + 1 ] = true;
        Q.push( { nd + 1 , make_tuple(cn, cm, cg + 1) } );
      }
    }
    for( int i = 0 ; i < 4 ; i ++ ){
      int nxtn = nxt[ cn ][ cm ][ i ].first;
      int nxtm = nxt[ cn ][ cm ][ i ].second;
      if( nxtn == -1 ) continue;
      if( gt[ nxtn ][ nxtm ][ cg ] ) continue;
      gt[ nxtn ][ nxtm ][ cg ] = true;
      Q.push( {nd + 1 , make_tuple(nxtn, nxtm, cg)} );
    }
  }
  assert( false );
}
