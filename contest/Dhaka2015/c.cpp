#include <bits/stdc++.h>
using namespace std;
#define N 101010
#define SZ(c) (int)(c).size()
#define ALL(c) (c).begin(), (c).end()
#define REP(i, s, e) for(int i = (s); i <= (e); i++)
#define REPD(i, s, e) for(int i = (s); i >= (e); i--)
typedef tuple< int , int > tii;
const int MAXN = 100010;
const int LOG  = 19;
struct HLD{
  int n;
  vector<int> g[MAXN] , g2[ MAXN ];
  int sz[MAXN], dep[MAXN];
  int ts, tid[MAXN], tdi[MAXN], tl[MAXN], tr[MAXN];
  //  ts : timestamp , useless after yutruli
  //  tid[ u ] : pos. of node u in the seq.
  //  tdi[ i ] : node at pos i of the seq.
  //  tl , tr[ u ] : subtree interval in the seq. of node u
  int mom[MAXN][LOG], head[MAXN];
  int cst[MAXN][LOG];
  // head[ u ] : head of the chain contains u
  void dfssz(int u, int p, int cc){
    dep[u] = dep[p] + 1;
    mom[u][0] = p;
    cst[u][0] = cc;
    sz[u] = 1;
    head[u] = u;
    int id = 0;
    for(int& v:g[u]){
      if(v != p){
        dep[v] = dep[u] + 1;
        dfssz(v, u , g2[ u ][ id ]);
        sz[u] += sz[v];
      }
      id ++;
    }
  }
  void dfshl(int u){
    //printf("dfshl %d\n", u);
    ts++;
    tid[u] = tl[u] = tr[u] = ts;
    tdi[tid[u]] = u;
    sort(ALL(g[u]),
         [&](int a, int b){return sz[a] > sz[b];});
    bool flag = 1;
    for(int& v:g[u]) if(v != mom[u][0]){
      if(flag) head[v] = head[u], flag = 0;
      dfshl(v);
      tr[u] = tr[v];
    }
  }
  inline int lca(int a, int b){
    if(dep[a] > dep[b]) swap(a, b);
    //printf("lca %d %d\n", a, b);
    int diff = dep[b] - dep[a];
    REPD(k, LOG-1, 0) if(diff & (1<<k)){
      //printf("b %d\n", mom[b][k]);
      b = mom[b][k];
    }
    if(a == b) return a;
    REPD(k, LOG-1, 0) if(mom[a][k] != mom[b][k]){
      a = mom[a][k];
      b = mom[b][k];
    }
    return mom[a][0];
  }
  inline int lca2(int a, int b){
    if(dep[a] > dep[b]) swap(a, b);
    //printf("lca %d %d\n", a, b);
    int diff = dep[b] - dep[a];
    int fcst = 0;
    REPD(k, LOG-1, 0) if(diff & (1<<k)){
      //printf("b %d\n", mom[b][k]);
      //printf( "%d %d : %d\n" , b , k , cst[b][k] );
      fcst = max( fcst , cst[b][k] );
      b = mom[b][k];
    }
    if(a == b) return fcst;
    REPD(k, LOG-1, 0) if(mom[a][k] != mom[b][k]){
      fcst = max( fcst , cst[a][k] );
      fcst = max( fcst , cst[b][k] );
      //printf( "%d %d : %d\n" , a , k , cst[a][k] );
      //printf( "%d %d : %d\n" , b , k , cst[b][k] );
      a = mom[a][k];
      b = mom[b][k];
    }
    //printf( "%d %d : %d\n" , a , 0 , cst[a][0] );
    //printf( "%d %d : %d\n" , b , 0 , cst[b][0] );
    fcst = max( fcst , cst[a][0] );
    fcst = max( fcst , cst[b][0] );
    //printf( "%d\n" , fcst );
    return fcst;
  }
  void init( int _n ){
    n = _n;
    REP( i , 1 , n ){
      g[ i ].clear();
      g2[ i ].clear();
    }
  }
  void addEdge( int u , int v , int ci ){
    g[ u ].push_back( v );
    g2[ u ].push_back( ci );
    g[ v ].push_back( u );
    g2[ v ].push_back( ci );
  }
  void yutruli(){
    dfssz(1, 0, 0);
    ts = 0;
    dfshl(1);
    //for( int i = 1 ; i <= n ; i ++ )
      //printf( "%d : %d\n" , tdi[i] , cst[i][0] );
    REP(k, 1, LOG-1) REP(i, 1, n){
      mom[i][k] = mom[mom[i][k-1]][k-1];
      cst[i][k] = max(cst[i][k-1], cst[mom[i][k-1]][k-1]);
    }
  }
  vector< pair<int,int> > getPath( int u , int v ){
    vector< pair<int,int> > res;
    while( tid[ u ] < tid[ head[ v ] ] ){
      res.push_back( { tid[ head[ v ] ] , tid[ v ] } );
      v = mom[ head[ v ] ][ 0 ];
    }
    if( tid[ u ] + 1 <= tid[ v ] )
      res.push_back( { tid[ u ] + 1 , tid[ v ] } );
    reverse( ALL( res ) );
    return res;
    /*
     * res : list of intervals from u to v
     * u must be ancestor of v
     * usage :
     * vector< tii >& path = tree.getPath( u , v )
     * for( tii tp : path ) {
     *   int l , r;tie( l , r ) = tp;
     *   upd( l , r );
     *   uu = tree.tdi[ l ] , vv = tree.tdi[ r ];
     *   uu ~> vv is a heavy path on tree
     * }
     */
  }
} tree;
#define L(X) (X<<1)
#define R(X) (1+(X<<1))
#define mid ((l+r)>>1)
int st[ N << 2 ] , tag[ N << 2 ];
void build_st( int no , int l , int r ){
  st[ no ] = 10000; tag[ no ] = 10000;
  if( l == r ) return;
  build_st( L( no ) , l , mid );
  build_st( R( no ) , mid + 1 , r );
}
void push( int no , int l , int r ){
  if( tag[ no ] == 10000 ) return;
  tag[ L( no ) ] = min( tag[ L( no ) ] , tag[ no ] );
  tag[ R( no ) ] = min( tag[ R( no ) ] , tag[ no ] );
  st[ L( no ) ] = min( st[ L( no ) ] , tag[ no ] );
  st[ R( no ) ] = min( st[ R( no ) ] , tag[ no ] );
  tag[ no ] = 10000;
}
void modify( int no , int l , int r , int ql , int qr , int cc ){
  if( qr < l || ql > r ) return;
  if( ql <= l && r <= qr ){
    tag[ no ] = min( tag[ no ] , cc );
    st[ no ] = min( st[ no ] , cc );
    return;
  }
  push( no , l , r );
  modify( L( no ) , l , mid , ql , qr , cc );
  modify( R( no ) , mid + 1 , r , ql , qr , cc );
  st[ no ] = min( st[ L( no ) ] , st[ R( no ) ] );
}
int query( int no , int l , int r , int pos ){
  if( l == r ) return st[ no ];
  push( no , l , r );
  if( pos <= mid ) return query( L( no ) , l , mid , pos );
  return query( R( no ) , mid + 1 , r , pos );
}
int n , m , u[ N ] , v[ N ] , c[ N ] , a[ N ] , b[ N ];
void init(){
  scanf( "%d%d" , &n , &m );
  for( int i = 1 ; i <= m ; i ++ ){
    scanf( "%d%d%d" , &u[ i ], &v[ i ] , &c[ i ] );
    a[ i ] = b[ i ] = -1;
  }
  tree.init( n );
  for( int i = 1 ; i < n ; i ++ )
    tree.addEdge( u[ i ] , v[ i ] , c[ i ] );
  tree.yutruli();
}
int id;
void solve(){
  build_st( 1 , 1 , n );
  for( int i = n ; i <= m ; i ++ ){
    int mx = tree.lca2( u[ i ] , v[ i ] );
    b[ i ] = c[ i ] - mx;
    int lca = tree.lca( u[ i ] , v[ i ] );
    vector< pair<int,int> > vv = tree.getPath( lca , u[ i ] );
    for( auto j : vv )
      modify( 1 , 1,  n , j.first , j.second , c[ i ] );      
                            vv = tree.getPath( lca , v[ i ] );
    for( auto j : vv )
      modify( 1 , 1,  n , j.first , j.second , c[ i ] );      
  }
  for( int i = 1 ; i < n ; i ++ ){
    int prt = u[ i ] , son = v[ i ];
    if( tree.mom[ prt ][ 0 ] == son )
      swap( prt , son );
    int pos = tree.tid[ son ];
    int vl = query( 1 , 1 , n , pos );
    if( vl != 10000 )
      a[ i ] = vl - c[ i ];
  }
  long long ans = 0;
  for( long long i = 1 ; i <= m ; i ++ ){
    //printf( "%d %d\n" , a[ i ] , b[ i ] );
    ans += ( i * a[ i ] + i * i * b[ i ] );
  }
  printf( "Case %d: %lld\n" , ++ id , ans );
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
