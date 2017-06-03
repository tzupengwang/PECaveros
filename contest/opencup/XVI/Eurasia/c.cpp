#include <bits/stdc++.h>
using namespace std;
#define MXN 101010
#define N 101010
#define PB push_back
#define FZ(X) memset(X,0,sizeof(X))
struct Scc{
  int n, nScc, vst[MXN], bln[MXN];
  vector<int> E[MXN], rE[MXN], vec;
  void init(int _n){
    n = _n;
    for (int i=1; i<=MXN; i++){
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
void no(){
  puts( "NO" );
  exit(0);
}
int n , k;
int vl[ N ] , vr[ N ];
int vl2[ N ] , vr2[ N ];
vector< pair<int,int> > v[ N ] , v2[ N ];
void init(){
  scanf( "%d%d" , &n , &k );
  for( int i = 1 ; i <= k ; i ++ ){
    vl[ i ] = -2000000000;
    vr[ i ] = +2000000000;
  }
  graph.init( k );
}
int who[ N ] , ind[ N ];
int ans[ N ];
void find_sol(){
  queue<int> Q;
  for( int i = 0 ; i < graph.nScc ; i ++ )
    if( ind[ i ] == 0 )
      Q.push( i );
  while( Q.size() ){
    int tn = Q.front(); Q.pop();
    if( vl2[ tn ] > vr2[ tn ] ) no();
    ans[ tn ] = vl2[ tn ];
    for( auto e : v2[ tn ] ){
      if( e.first == 0 )
        vl2[ e.second ] = max( vl2[ e.second ] , ans[ tn ] );
      else
        vl2[ e.second ] = max( vl2[ e.second ] , ans[ tn ] + 1 );
      ind[ e.second ] --;
      if( ind[ e.second ] == 0 )
        Q.push( e.second );
    }
  }
}
void solve(){
  while( n -- ){
    int sl , tl , al , tr , ar;
    scanf( "%d%d%d%d%d" , &sl , &tl , &al , &tr , &ar );
    if( sl == 0 ){ // <=
      if( tl == 1 and tr == 1 ){
        if( al > ar )
          no();
      }else if( tl == 1 and tr == 0 ){
        vl[ ar ] = max( vl[ ar ] , al );
      }else if( tl == 0 and tr == 1 ){
        vr[ al ] = min( vr[ al ] , ar );
      }else{
        v[ al ].push_back( { sl , ar } );
        graph.add_edge( al , ar );
      }
    }else{ // <
      if( tl == 1 and tr == 1 ){
        if( al >= ar )
          no();
      }else if( tl == 1 and tr == 0 ){
        vl[ ar ] = max( vl[ ar ] , al + 1 );
      }else if( tl == 0 and tr == 1 ){
        vr[ al ] = min( vr[ al ] , ar - 1 );
      }else{
        v[ al ].push_back( { sl , ar } );
        graph.add_edge( al , ar );
      }
    }
  }
  for( int i = 1 ; i <= k ; i ++ )
    if( vl[ i ] > vr[ i ] )
      no();
  graph.solve();
  for( int i = 1 ; i <= k ; i ++ )
    who[ i ] = graph.bln[ i ];
  for( int i = 0 ; i < graph.nScc ; i ++ ){
    vl2[ i ] = -2000000000;
    vr2[ i ] = +2000000000;
  }
  for( int i = 1 ; i <= k ; i ++ ){
    int ni = who[ i ];
    vl2[ ni ] = max( vl2[ ni ] , vl[ i ] );
    vr2[ ni ] = min( vr2[ ni ] , vr[ i ] );
    for( auto e : v[ i ] ){
      int nj = who[ e.second ];
      if( ni == nj ){
        if( e.first == 1 ) no();
      }else{
        v2[ ni ].push_back( { e.first , nj } );
        ind[ nj ] ++;
      }
    }
  }
  for( int i = 0 ; i < graph.nScc ; i ++ )
    if( vl2[ i ] > vr2[ i ] )
      no();
  find_sol();
  puts( "YES" );
  for( int i = 1 ; i <= k ; i ++ )
    printf( "%d\n" , ans[ who[ i ] ] );
}
int main(){
  freopen( "input.txt" , "r" , stdin );
  freopen( "output.txt" , "w" , stdout );
  init();
  solve();
}
