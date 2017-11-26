#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define SZ(X) ((int)X.size())
#define MAXV 20010
#define INF 10000000
struct MaxFlow{
  struct Edge{
    int v , c , r;
    Edge( int _v , int _c , int _r ){
      v = _v;
      c = _c;
      r = _r;
    }
  };
  int s , t;
  vector<Edge> G[ MAXV ];
  int iter[ MAXV ] , d[ MAXV ] , gap[ MAXV ] , tot;
  void init( int x ){
    tot = x + 2;
    s = x + 1 , t = x + 2;
    for( int i = 0 ; i <= tot ; i ++ ){
      G[ i ].clear();
      iter[ i ] = d[ i ] = gap[ i ] = 0;
    }
  }
  void addEdge( int u , int v , int c ){
    G[ u ].push_back( Edge( v , c , SZ( G[ v ] ) ) );
    G[ v ].push_back( Edge( u , 0 , SZ( G[ u ] ) - 1 ) );
  }
  int dfs( int p , int flow ){
    if( p == t ) return flow;
    for( int &i = iter[p] ; i < SZ(G[p]) ; i ++ ){
      Edge& e = G[p][i];
      if( e.c > 0 and d[p] == d[e.v] + 1 ){
        int f = dfs( e.v , min( flow , e.c ) );
        if( f ){
          e.c -= f;
          G[e.v][e.r].c += f;
          return f;
        }
      }
    }
    if( (--gap[d[p]]) == 0 ) d[s] = tot;
    else{
      d[p] ++;
      iter[p] = 0;
      ++ gap[d[p]];
    }
    return 0;
  }
  int solve(){
    int res = 0;
    gap[ 0 ] = tot;
    for( res = 0 ; d[s] < tot ; res += dfs(s, INF) );
    return res;
  }
} flow;
#define N 10101
#define K 22
int n , d , x[ N ] , y[ N ];
int id[ K ][ K ] , stmp , idd[ K ];
void init(){
  scanf( "%d" , &d );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%d%d" , &x[ i ] , &y[ i ] );
  stmp = 0;
  for( int i = 1 ; i <= d ; i ++ )
    for( int j = i ; j <= d ; j ++ )
      id[ i ][ j ] = ++ stmp;
  for( int i = 1 ; i <= d ; i ++ )
    idd[ i ] = ++ stmp;
}
int cnt[ N ][ N ];
void solve(){
  vector<int> ans;
  for( int i = 1 ; i <= d ; i ++ )
    for( int j = i ; j <= d ; j ++ )
      cnt[ i ][ j ] = 0;
  int pred = 0;
  for( int _ = 0 ; _ < n ; _ ++ ){
    cnt[ x[ _ ] ][ y[ _ ] ] ++;
    flow.init( stmp );
    for( int i = 1 ; i <= d ; i ++ )
      for( int j = i ; j <= d ; j ++ )
        if( cnt[ i ][ j ] ){
          flow.addEdge( flow.s , id[ i ][ j ] , cnt[ i ][ j ] );
          for( int k = i ; k <= j ; k ++ )
            flow.addEdge( id[ i ][ j ] , idd[ k ] , n );
        }
    for( int i = 1 ; i <= d ; i ++ )
      flow.addEdge( idd[ i ] , flow.t , pred );
    int ret = flow.solve();
    if( ret != _ + 1 ){
      pred ++;
      ans.push_back( _ + 1 );
    }
  }
  for( size_t i = 0 ; i < ans.size() ; i ++ )
    printf( "%d%c" , ans[ i ] , " \n"[ i + 1 == ans.size() ] );
}
int main(){
  while( scanf( "%d" , &n ) == 1 and n ){
    init();
    solve();
  }
}
