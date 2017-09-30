#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 101010
int n , q , root;
vector<int> v[ N ];
void init(){
  scanf( "%d%d%d" , &n , &q , &root );
  for( int i = 1 ; i <= n ; i ++ )
    v[ i ].clear();
  for( int i = 1 ; i < n ; i ++ ){
    int ui , vi;
    scanf( "%d%d" , &ui , &vi );
    v[ ui ].push_back( vi );
    v[ vi ].push_back( ui );
  }
}
#define K 20
int p[ K ][ N ] , dep[ N ] , sz[ N ];
int up( int ui , int dlt ){
  while( dlt ){
    int bt = __lg( dlt );
    ui = p[ bt ][ ui ];
    dlt ^= (1 << bt);
  }
  return ui;
}
int lca( int ui , int vi ){
  if( dep[ ui ] > dep[ vi ] ) swap( ui , vi );
  int dlt = dep[ vi ] - dep[ ui ];
  while( dlt ){
    int bt = __lg( dlt );
    vi = p[ bt ][ vi ];
    dlt ^= (1 << bt);
  }
  if( ui == vi ) return ui;
  for( int i = K - 1 ; i >= 0 ; i -- )
    if( p[ i ][ ui ] != p[ i ][ vi ] ){
      ui = p[ i ][ ui ];
      vi = p[ i ][ vi ];
    }
  return p[ 0 ][ ui ];
}
void go( int now , int prt , int tdep ){
  sz[ now ] = 1;
  dep[ now ] = tdep;
  p[ 0 ][ now ] = prt;
  for( int son : v[ now ] ){
    if( son == prt ) continue;
    go( son , now , tdep + 1 );
    sz[ now ] += sz[ son ];
  }
}
int cs;
void solve(){
  go( 1 , 1 , 0 );
  for( int j = 1 ; j < K ; j ++ )
    for( int i = 1 ; i <= n ; i ++ )
      p[ j ][ i ] = p[ j - 1 ][ p[ j - 1 ][ i ] ];
  int nroot = root;
  printf( "Case #%d:\n" , ++ cs );
  while( q -- ){
    int cmd , who;
    scanf( "%d%d" , &cmd , &who );
    if( cmd == 0 ) nroot = who;
    else{
      int ans = 0;
      if( nroot == who )
        ans = n;
      else{
        int lp = lca( nroot , who );
        if( lp == who )
          ans = n - sz[ up( nroot , dep[ nroot ] - dep[ who ] - 1 ) ];
        else
          ans = sz[ who ];
      }
      printf( "%d\n" , ans );
    }
  }
}
int main(){
  int t; scanf( "%d" , &t ); while( t -- ){
    init();
    solve();
  }
}
