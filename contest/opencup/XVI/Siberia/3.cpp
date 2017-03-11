#include <bits/stdc++.h>
using namespace std;
#define N 100010
int n , m , k , a[ N ] , b[ N ];
#define MXN N
struct Scc{
#define FZ(X) memset(X,0,sizeof X)
#define PB push_back
  int n, nScc, vst[MXN], bln[MXN];
  vector<int> E[MXN], rE[MXN], vec;
  void init(int _n){
    n = _n;
    for (int i=1; i<=n; i++){
      E[i].clear();
      rE[i].clear();
    }
  }
  void add_edge(int u, int v){
    E[u].PB(v);
    rE[v].PB(u);
  }
  void DFS(int u){
    vst[u]=1;
    for (auto v : E[u])
      if (!vst[v]) DFS(v);
    vec.PB(u);
  }
  void rDFS(int u){
    vst[u] = 1;
    bln[u] = nScc;
    for (auto v : rE[u])
      if (!vst[v]) rDFS(v);
  }
  void solve(){
    nScc = 0;
    vec.clear();
    FZ(vst);
    for (int i=1; i<=n; i++)
      if (!vst[i]) DFS(i);
    reverse(vec.begin(),vec.end());
    FZ(vst);
    for (auto v : vec){
      if (!vst[v]){
        rDFS(v);
        nScc++;
      }
    }
  }
} graph;
int qa[ N ] , qb[ N ];
vector< int > qry[ N ];
void init(){
  scanf( "%d%d" , &n , &m );
  for( int i = 0 ; i < m ; i ++ )
    scanf( "%d%d" , &a[ i ] , &b[ i ] );
  scanf( "%d" , &k );
  for( int i = 0 ; i < k ; i ++ ){
    scanf( "%d%d" , &qa[ i ] , &qb[ i ] );
    qry[ qb[ i ] ].push_back( qa[ i ] );
  }
}
vector<int> cat[ N ];
vector<int> v[ N ];
int indeg[ N ];
#define X 2000
vector< bitset<X> > reach;
bool flg = true;
void solve(){
  graph.init( n );
  for( int i = 0 ; i < m ; i ++ )
    graph.add_edge( a[ i ] , b[ i ] );
  graph.solve();
  for( int i = 1 ; i <= n ; i ++ )
    cat[ graph.bln[ i ] ].push_back( i );
  for( int i = 0 ; i < m ; i ++ ){
    int ai = graph.bln[ a[ i ] ];
    int bi = graph.bln[ b[ i ] ];
    if( ai == bi ) continue;
    v[ ai ].push_back( bi );
  }
  reach.resize( graph.nScc );
  for( int i = 0 ; i < graph.nScc ; i ++ ){
    sort( v[ i ].begin() , v[ i ].end() );
    v[ i ].resize( unique( v[ i ].begin() , v[ i ].end() ) - v[ i ].begin() );
    for( int nxt : v[ i ] )
      indeg[ nxt ] ++;
  }
  vector<int> topo;
  queue<int> Q;
  for( int i = 0 ; i < graph.nScc ; i ++ )
    if( indeg[ i ] == 0 )
      Q.push( i );
  while( Q.size() ){
    topo.push_back( Q.front() );
    int now = Q.front(); Q.pop();
    for( int x : v[ now ] ){
      indeg[ x ] --;
      if( indeg[ x ] == 0 )
        Q.push( x );
    }
  }
  reverse( topo.begin() , topo.end() );
  for( int blk = 0 ; blk <= n / X ; blk ++ ){
    int lft = blk * X , rgt = lft + X;
    for( int i = 0 ; i < graph.nScc ; i ++ ){
      reach[ i ].reset();
      for( int j : cat[ i ] )
        if( lft <= j and j < rgt )
          reach[ i ][ j % X ] = 1;
    }
    for( auto i : topo )
      for( int nxt : v[ i ] )
        reach[ i ] |= reach[ nxt ];
    for( int i = lft ; i < min( rgt , n + 1 ) ; i ++ ){
      for( int j : qry[ i ] )
        if( reach[ graph.bln[ j ] ][ i % X ] ){
          flg = false; break;
        }
      if( not flg ) break;
    }
    if( not flg ) break;
  }
  if( flg ){
    puts( "YES" );
    printf( "%d\n" , m );
    for( int i = 0 ; i < m ; i ++ )
      printf( "%d %d\n" , a[ i ] , b[ i ] );
  }else
    puts( "NO" );
}
int main(){
#ifndef LOCAL
  freopen( "input.txt" , "r" , stdin );
  freopen( "output.txt" , "w" , stdout );
#endif
  init();
  solve();
}
