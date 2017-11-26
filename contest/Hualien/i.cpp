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
int m , n , e;
int main(){
  while( cin >> m and m ){
    cin >> n >> e;
    flow.init( m + n + 2 );
    for( int i = 0 ; i < m ; i ++ )
      flow.addEdge( flow.s , i , 1 );
    for( int i = 0 ; i < n ; i ++ )
      flow.addEdge( m + i , flow.t , 1 );
    while( e -- ){
      int a , b;
      cin >> a >> b;
      flow.addEdge( a , m + b , 1 );
    }
    cout << flow.solve() << endl;
  }
}
