#include <bits/stdc++.h>

using namespace std;

#define SZ(c) ((int)(c).size())
struct Maxflow {
  static const int MAXV = 20010;
  static const int INF  = 1000000;
  struct Edge {
    int v, c, r;
    Edge(int _v, int _c, int _r):
      v(_v), c(_c), r(_r) {}
  };
  int s, t;
  vector<Edge> G[MAXV*2];
  int iter[MAXV*2], d[MAXV*2], gap[MAXV*2], tot;
  int side[ MAXV*2 ];
  bool vis[MAXV*2];
  void flowinit(int x) {
    tot = x;
    for(int i = 0; i <= tot; i++) {
      G[i].clear();
    }
  }
  void clean() {
    for ( int i = 1 ; i <= tot ; i++ ) {
      for ( Edge &e : G[ i ] )
        e.c = 1;
    }
  }
  void addEdge(int u, int v) {
    G[u].push_back(Edge(v, 1, SZ(G[v]) ));
    G[v].push_back(Edge(u, 1, SZ(G[u]) - 1));
  }
  int dfs(int p, int flow) {
    vis[p] = 1;
    if(p == t) {
      return flow;
    }
    for(int i = 0; i < SZ(G[p]); i++) {
      Edge &e = G[p][i];
      if(e.c > 0 && !vis[e.v]) {
        int f = dfs(e.v, min(flow, e.c));
        if(f) {
          e.c -= f;
          G[e.v][e.r].c += f;
          return f;
        }
      }
    }
    return 0;
  }
  void dfs2( int u ) {
    side[ u ] = 1;
    for ( Edge e : G[u] ) if ( e.c && side[e.v] == 2 ) {
      dfs2(e.v);
    }
  }
  int mincut( int _s , int _t ) {
    s = _s;
    t = _t;
    int res = 0;
    while(1) {
      fill(vis, vis+tot+1 , 0);
      int tmp = dfs(s, INF);
      if ( tmp == 0 ) break;
      res += tmp;
    }
    fill( side , side+tot+1 , 2 );
    dfs2( s );
    return res;
  }
} flow;

const int MAXN = 3030;
const int MAXM = 5555;

int N , M;
int ans;
int mn[ MAXN ];
int U[ MAXN ];

// root : U[l]
void dq( int l , int r ) {
  static int tmp[ MAXN ];
  if ( l >= r ) return ;
  int a = U[ l ];
  int b = U[ r ];
  flow.clean();
  int mc = flow.mincut( a , b );
  //printf( "dq %d %d %d %d %d\n  " , l , r , a , b , mc );
  //for ( int i = l ; i <= r ; i++ ) printf( "%d " , U[i] );
  //puts("");
  int it1 = l , it2 = r;
  for ( int i = l ; i <= r ; i++ ) {
    if ( flow.side[U[i]] == 1 ) {
      tmp[it1] = U[i];
      it1++;
    }
    else {
      tmp[it2] = U[i];
      it2--;
    }
  }
  for ( int i = l ; i <= r ; i++ ) U[i] = tmp[i];
  dq( l , it1-1 );
  dq( it1 , r );
  for ( int i = it1 ; i <= r ; i++ ) mn[U[i]] = min( mn[U[i]] , mc );
  for ( int i = l ; i < it1 ; i++ )
    for ( int j = it1 ; j <= r ; j++ ) {
      int u = min( U[i], U[j] );
      int v = max( U[i], U[j] );
      int tt = min(mn[u], mn[v]);
      //int tt = mc;
      //printf( "  mincut %d %d %d\n" , u , v , tt );
      ans += tt;
    }
}

int main() {
  ios_base::sync_with_stdio( 0 );
  cin.tie(0);
  while ( cin >> N >> M ) {
    flow.flowinit(N);
    for ( int i = 0 ; i < M ; i++ ) {
      int u , v;
      cin >> u >> v;
      flow.addEdge( u , v );
    }
    ans = 0;
    for ( int i = 1 ; i <= N ; i++ )
      mn[ i ] = 5;
    for ( int i = 1 ; i <= N ; i++ )
      U[ i ] = i;
    dq( 1 , N );
    cout << ans << '\n';
  }
}
