#include <bits/stdc++.h>
using namespace std;
#define N 514
#define PB push_back
#define FZ(X) memset(X,0,sizeof(X))
struct Scc{
#define MXN N
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
int n , m;
void init(){
  cin >> n >> m;
  graph.init( n );
  while( m -- ){
    int ui , vi;
    cin >> ui >> vi;
    graph.add_edge( ui , vi );
  }
  graph.solve();
}
int way[ N ][ N ];
vector<int> who[ N ];
vector< pair<int,int> > e;
void solve(){
  for( int i = 1 ; i <= n ; i ++ )
    who[ graph.bln[ i ] ].push_back( i );
  for( int i = 0 ; i < graph.nScc ; i ++ )
    if( who[ i ].size() > 1u ){
      for( size_t j = 0 ; j < who[ i ].size() ; j ++ )
        e.push_back( { who[ i ][ j ] , who[ i ][ (j + 1) % who[ i ].size() ] } );
    }
  for( int i = 1 ; i <= n ; i ++ )
    for( auto j : graph.E[ i ] )
      if( graph.bln[ i ] != graph.bln[ j ] )
        way[ graph.bln[ i ] ][ graph.bln[ j ] ] = 1;
  //for( int i = 0 ; i < graph.nScc ; i ++ )
    //for( int j = 0 ; j < graph.nScc ; j ++ )
      //if( way[ i ][ j ] )
        //printf( "%d -> %d\n" , i , j );
  for( int k = 0 ; k < graph.nScc ; k ++ )
    for( int i = 0 ; i < graph.nScc ; i ++ )
      for( int j = 0 ; j < graph.nScc ; j ++ )
        if( way[ i ][ k ] and way[ k ][ j ] )
          way[ i ][ j ] = 2;
  for( int i = 0 ; i < graph.nScc ; i ++ )
    for( int j = 0 ; j < graph.nScc ; j ++ )
      if( i != j and way[ i ][ j ] == 1 )
        e.push_back( { who[ i ][ 0 ] , who[ j ][ 0 ] } );
  printf( "%d %d\n" , n , (int)e.size() );
  for( auto ee : e )
    printf( "%d %d\n" , ee.first , ee.second );
}
int main(){
  init();
  solve();
}
