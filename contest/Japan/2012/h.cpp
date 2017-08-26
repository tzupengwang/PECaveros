#include <bits/stdc++.h>
using namespace std;
#define N 1021
#define MXN 1021
#define PB push_back
#define FZ(X) memset(X,0,sizeof(X))
struct Scc{
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
int s[ 11111 ] , a[ 11111 ] , b[ 11111 ];
int ccc;
bool init(){
  cin >> n >> m;
  if( n == 0 and m == 0 )
    return false;
  for( int i = 0 ; i < m ; i ++ )
    cin >> s[ i ] >> a[ i ] >> b[ i ];
  return true;
}
vector< pair<int,int> > con[ 5 ];
int gp[ N ];
bool reachable[ N ][ N ];
void gogo( int st , int now ){
  if( reachable[ st ][ now ] )
    return;
  reachable[ st ][ now ] = true;
  for( auto nxt : graph.E[ now ] )
    gogo( st , nxt );
}
bool emp[ N ][ N ];
void go_emp( int s1 , int s2 ){
  if( emp[ s1 ][ s2 ] )
     return;
  emp[ s1 ][ s2 ] = true;
  for( auto i : graph.E[ s2 ] )
    go_emp( s1 , i );
  for( auto i : graph.E[ s1 ] )
    go_emp( i , s2 );
}
bool okay( int til ){
  for( int i = 0 ; i < 5 ; i ++ )
    con[ i ].clear();
  for( int i = 0 ; i < til ; i ++ )
    con[ s[ i ] - 1 ].push_back( { a[ i ] , b[ i ] } );
  graph.init( n );
  for( auto i : con[ 0 ] )
    graph.add_edge( i.second , i.first );
  for( auto i : con[ 1 ] ){
    graph.add_edge( i.first , i.second );
    graph.add_edge( i.second , i.first );
  }
  graph.solve();
  for( int i = 1 ; i <= n ; i ++ ){
    gp[ i ] = graph.bln[ i ];
    for( int j = 1 ; j <= n ; j ++ )
      reachable[ i ][ j ] = false;
    gogo( i , i );
  }
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= n ; j ++ )
      emp[ i ][ j ] = false;
  for( auto i : con[ 3 ] ){
    go_emp( i.first , i.second );
    go_emp( i.second , i.first );
  }
  for( auto i : con[ 4 ] ){
    if( emp[ i.first ][ i.first ] )
      return false;
    if( emp[ i.second ][ i.second ] )
      return false;
    if( emp[ i.first ][ i.second ] )
      return false;
  }
  for( auto i : con[ 2 ] ){
    if( gp[ i.first ] == gp[ i.second ] )
      return false;
    if( emp[ i.first ][ i.first ] and
        emp[ i.second ][ i.second ] )
      return false;
  }
  return true;
}
void solve(){
  int bl = 2 , br = m , ba = 1;
  while( bl <= br ){
    int bmid = (bl + br) >> 1;
    if( okay( bmid ) )
      ba = bmid , bl = bmid + 1;
    else
      br = bmid - 1;
  }
  cout << ba << "\n";
}
int main(){
  while( init() )
    solve();
}
