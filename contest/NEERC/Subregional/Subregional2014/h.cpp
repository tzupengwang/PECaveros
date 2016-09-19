#include <bits/stdc++.h>
using namespace std;
#define N 5140
#define M 550
typedef long long LL;
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
  bool vst[ MAXV * 2 ];
  void dfs( int now ){
    vst[ now ] = true;
    for( Edge e : G[ now ] )
      if( e.c > 0 && !vst[ e.v ] && e.v != t )
        dfs( e.v );
  }
  void find_ans(){
    dfs( s );
  }
  void flowinit(int x) {
    tot = x+2;
    s = x+1, t = x+2;
    for(int i = 0; i <= tot; i++) {
      G[i].clear();
      iter[i] = d[i] = gap[i] = 0;
    }
    for( int i = 0 ; i <= tot ; i ++ )
      vst[ i ] = false;
  }
  void addEdge(int u, int v, int c) {
    G[u].push_back(Edge(v, c, SZ(G[v]) ));
    G[v].push_back(Edge(u, 0, SZ(G[u]) - 1));
  }
  int dfs(int p, int flow) {
    if(p == t) return flow;
    for(int &i = iter[p]; i < SZ(G[p]); i++) {
      Edge &e = G[p][i];
      if(e.c > 0 && d[p] == d[e.v]+1) {
        int f = dfs(e.v, min(flow, e.c));
        if(f) {
          e.c -= f;
          G[e.v][e.r].c += f;
          return f;
        }
      }
    }
    if( (--gap[d[p]]) == 0) d[s] = tot;
    else {
      d[p]++;
      iter[p] = 0;
      ++gap[d[p]];
    }
    return 0;
  }
  int maxflow() {
    //puts("MF");
    int res = 0;
    gap[0] = tot;
    for(res = 0; d[s] < tot; res += dfs(s, INF));
    find_ans();
    return res;
  }
} flow;
Maxflow::Edge e(1, 1, 1);
const LL BS = 13131;
const LL mod = 1000000007;
int n , k;
LL lh[ N ] , rh[ N ];
char c[ N ][ M ];
vector< int > lv , rv;
void init(){
  scanf( "%d%d" , &n , &k );
  for( int i = 0 ; i < n ; i ++ ){
    scanf( "%s" , c[ i ] );
    int len = strlen( c[ i ] );
    for( int j = 0 ; j < k ; j ++ )
      lh[ i ] = ( lh[ i ] * BS + c[ i ][ j ] ) % mod;
    for( int j = 0 ; j < k ; j ++ )
      rh[ i ] = ( rh[ i ] * BS + c[ i ][ len - j - 1 ] ) % mod;
    lv.push_back( lh[ i ] );
    rv.push_back( rh[ i ] );
  }
  sort( lv.begin() , lv.end() );
  lv.resize( unique( lv.begin() , lv.end() ) - lv.begin() );
  sort( rv.begin() , rv.end() );
  rv.resize( unique( rv.begin() , rv.end() ) - rv.begin() );
}
bool lft[ N ];
bool rgt[ N ];
int p[ N ];
vector< int > lw[ N ] , rw[ N ];
void find_ans(){
  for( int i = 1 ; i <= (int)lv.size() ; i ++ )
    if( !flow.vst[ i ] )
      lft[ i ] = true;
  for( int i = 1 ; i <= (int)rv.size() ; i ++ )
    if( flow.vst[ i + (int)lv.size() ] )
      rgt[ i ] = true;
  for( int i = 0 ; i < n ; i ++ ){
    int lid = lower_bound( lv.begin() , lv.end() , lh[ i ] ) - lv.begin() + 1;
    int rid = lower_bound( rv.begin() , rv.end() , rh[ i ] ) - rv.begin() + 1;
    if( lft[ lid ] ) lw[ lid ].push_back( i + 1 );
    else rw[ rid ].push_back( i + 1 );
  }
  for( int i = 1 ; i <= (int)lv.size() ; i ++ )
    if( lw[ i ].size() ){
      printf( "%d" , (int)lw[ i ].size() );
      for( int x : lw[ i ] )
        printf( " %d" , x );
      puts( "" );
    }
  for( int i = 1 ; i <= (int)rv.size() ; i ++ )
    if( rw[ i ].size() ){
      printf( "%d" , (int)rw[ i ].size() );
      for( int x : rw[ i ] )
        printf( " %d" , x );
      puts( "" );
    }
}
void solve(){
  vector< pair<int,int> > vv;
  for( int i = 0 ; i < n ; i ++ ){
    int lid = lower_bound( lv.begin() , lv.end() , lh[ i ] ) - lv.begin();
    int rid = lower_bound( rv.begin() , rv.end() , rh[ i ] ) - rv.begin();
    vv.push_back( { lid , rid } );
  }
  sort( vv.begin() , vv.end() );
  vv.resize( unique( vv.begin() , vv.end() ) - vv.begin() );
  flow.flowinit( (int)lv.size() + (int)rv.size() );
  for( auto tp : vv )
    flow.addEdge( tp.first + 1 , tp.second + 1 + (int)lv.size() , 1 );
  for( int i = 1 ; i <= (int)lv.size() ; i ++ )
    flow.addEdge( flow.s , i , 1 );
  for( int i = 1 ; i <= (int)rv.size() ; i ++ )
    flow.addEdge( i + (int)lv.size() , flow.t , 1 );
  int ans = flow.maxflow();
  printf( "%d\n" , ans );
  find_ans();
}
int main(){
  freopen( "heavy.in" , "r" , stdin );
  freopen( "heavy.out" , "w" , stdout );
  init();
  solve();
}
