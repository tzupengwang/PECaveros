#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define SZ(c) ((int)(c).size())
static const LL INF  = 100000000000000LL;
struct Maxflow {
  static const LL MAXV = 200010;
  struct Edge {
    LL v, c, r;
    Edge(LL _v, LL _c, LL _r):
      v(_v), c(_c), r(_r) {}
  };
  LL s, t;
  vector<Edge> G[MAXV*2];
  LL iter[MAXV*2], d[MAXV*2], gap[MAXV*2], tot;
  void init(LL x) {
    tot = x+2;
    s = x+1, t = x+2;
    for(LL i = 0; i <= tot; i++) {
      G[i].clear();
      iter[i] = d[i] = gap[i] = 0;
    }
  }
  void addEdge(LL u, LL v, LL c) {
    //fprintf( stderr, "%lld -(%lld)-> %lld\n" , u , c , v );
    G[u].push_back(Edge(v, c, SZ(G[v]) ));
    G[v].push_back(Edge(u, 0, SZ(G[u]) - 1));
  }
  LL dfs(LL p, LL flow) {
    if(p == t) return flow;
    for(LL &i = iter[p]; i < SZ(G[p]); i++) {
      Edge &e = G[p][i];
      if(e.c > 0 && d[p] == d[e.v]+1) {
        LL f = dfs(e.v, min(flow, e.c));
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
  LL solve() {
    //puts("MF");
    LL res = 0;
    gap[0] = tot;
    for(res = 0; d[s] < tot; res += dfs(s, INF));
    return res;
  }
} flow;
#define N 52
int getint(){
  int x = 0; char c=getchar();
  while( c < '0' or c > '9' ) c = getchar();
  while( c>='0' and c<='9' )
    x = x * 10 + c - '0' , c = getchar();
  return x;
}
int n , m , k;
int a[ N ][ N ];
int id[ N ][ 6 ][ N << 2 ];
int aid[ N ][ N ];
int tot;
#define L(X) (X<<1)
#define R(X) (1+(X<<1))
#define mid ((l+r)>>1)
void go( int ni , int nj , int no , int l , int r ){
  //printf( "%d %d %d : %d\n" , ni , nj , no );
  id[ ni ][ nj ][ no ] = tot ++;
  if( l == r ) return;
  go( ni , nj , L( no ) , l , mid );
  go( ni , nj , R( no ) , mid + 1 , r );
}
#define M 101010
int t[ M ] , b[ M ] , il[ M ] , ir[ M ] , x[ M ];
int bid[ M ];
void init(){
  n = getint();
  m = getint();
  k = getint();
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < m ; j ++ ){
      a[ i ][ j ] = getint();
      aid[ i ][ j ] = tot ++;
    }
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; i + ( 1 << j ) - 1 < n ; j ++ )
      go( i , j , 1 , 0 , m - 1 );
  for( int i = 0 ; i < k ; i ++ ){
    bid[ i ] = tot ++;
    t[ i ] = getint() - 1;
    b[ i ] = getint() - 1;
    il[ i ] = getint() - 1;
    ir[ i ] = getint() - 1;
    x[ i ] = getint();
  }
}
void go2( int ni , int nj , int no , int l , int r ){
  if( l == r ){
    for( int jj = ni ; jj < ni + ( 1 << nj ) ; jj ++ )
      flow.addEdge( aid[ jj ][ l ] , id[ ni ][ nj ][ no ] , INF );
    return;
  }
  flow.addEdge( id[ ni ][ nj ][ L( no ) ] , id[ ni ][ nj ][ no ] , INF );
  flow.addEdge( id[ ni ][ nj ][ R( no ) ] , id[ ni ][ nj ][ no ] , INF );
  go2( ni , nj , L( no ) , l , mid );
  go2( ni , nj , R( no ) , mid + 1 , r );
}
void go3( int ni , int nj , int no , int l , int r , int ql , int qr , int tid ){
  if( r < ql or l > qr ) return;
  if( ql <= l and r <= qr ){
    flow.addEdge( id[ ni ][ nj ][ no ] , tid , INF );
    return;
  }
  go3( ni , nj , L( no ) , l , mid , ql , qr , tid );
  go3( ni , nj , R( no ) , mid + 1 , r , ql , qr , tid );
}
void solve(){
  flow.init( tot );
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < m ; j ++ )
      flow.addEdge( flow.s , aid[ i ][ j ] , a[ i ][ j ] );
  for( int i = 0 ; i < k ; i ++ )
    flow.addEdge( bid[ i ] , flow.t , x[ i ] );
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; i + ( 1 << j ) - 1 < n ; j ++ )
      go2( i , j , 1 , 0 , m - 1 );
  for( int i = 0 ; i < k ; i ++ ){
    int bst = __lg( b[ i ] - t[ i ] + 1 );
    //printf( "%d %d %d\n" , t[ i ] , b[ i ] , bst );
    go3( t[ i ] , bst , 1 , 0 , m - 1 , il[ i ] , ir[ i ] , bid[ i ] );
    int st = b[ i ] - ( 1 << bst ) + 1;
    if( st != t[ i ] )
      go3( st , bst , 1 , 0 , m - 1 , il[ i ] , ir[ i ] , bid[ i ] );
  }
  printf( "%lld\n" , flow.solve() );
}
int main(){
  init();
  solve();
}
