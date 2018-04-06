#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
struct MinCostMaxFlow{
#define MAXV 20010
  const int INFf = 1e9;
  const LL INFc = 1e12;
  struct Edge{
    int v , cap;
    LL w;
    int rev;
    Edge(){}
    Edge(int t2, int t3, LL t4, int t5)
    : v(t2), cap(t3), w(t4), rev(t5) {}
  };
  int V, s, t;
  vector<Edge> g[MAXV];
  void init(int n){
    V = n+2;
    s = n+1, t = n+2;
    for(int i = 0; i <= V; i++) g[i].clear();
  }
  void addEdge(int a, int b, int cap, LL w){
    g[a].push_back(Edge(b, cap, w, (int)g[b].size()));
    g[b].push_back(Edge(a, 0, -w, (int)g[a].size()-1));
  }
  LL d[MAXV];
  int id[MAXV], mom[MAXV];
  bool inqu[MAXV];
  queue<int> q;
  pair<int,LL> solve(){
    int mxf = 0; LL mnc = 0;
    while(1){
      fill(d, d+1+V, INFc);
      fill(inqu, inqu+1+V, 0);
      fill(mom, mom+1+V, -1);
      mom[s] = s;
      d[s] = 0;
      q.push(s); inqu[s] = 1;
      while(q.size()){
        int u = q.front(); q.pop();
        inqu[u] = 0;
        for(int i = 0; i < (int) g[u].size(); i++){
          Edge &e = g[u][i];
          int v = e.v;
          if(e.cap > 0 and d[v] > d[u] + e.w){
            d[v] = d[u] + e.w;
            mom[v] = u;
            id[v] =i;
            if(!inqu[v]) q.push(v), inqu[v] = 1;
          }
        }
      }
      if(mom[t] == -1) break;
      int df = INFf;
      for(int u = t; u != s; u = mom[u])
        df = min(df, g[mom[u]][id[u]].cap);
      for(int u = t; u != s; u = mom[u]){
        Edge &e = g[mom[u]][id[u]];
        e.cap             -= df;
        g[e.v][e.rev].cap += df;
      }
      mxf += df;
      mnc += df*d[t];
    }
    return {mxf, mnc};
  }
} flow;
#define N 33
int n , m , e[ N ][ N ] , in[ N ][ N ] , out[ N ][ N ];
int rgt[ N ][ N ] , dn[ N ][ N ] , ptr;
void init(){
  scanf( "%d%d" , &n , &m );
  ptr = 0;
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= m ; j ++ ){
      in[ i ][ j ] = ptr ++;
      out[ i ][ j ] = ptr ++;
      e[ i ][ j ] = 0;
    }
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j < m ; j ++ )
      scanf( "%d" , &rgt[ i ][ j ] );
  for( int i = 1 ; i < n ; i ++ )
    for( int j = 1 ; j <= m ; j ++ )
      scanf( "%d" , &dn[ i ][ j ] );
  int es; scanf( "%d" , &es ); while( es -- ){
    int x , y;
    scanf( "%d%d" , &x , &y );
    e[ x ][ y ] = 1;
  }
}
int _cs;
void solve(){
  flow.init( ptr + 2 );
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= m ; j ++ ){
      flow.addEdge( flow.s , in[ i ][ j ] , 1 , 0 );
      flow.addEdge( out[ i ][ j ] , flow.t , 1 , 0 );
      if( !e[ i ][ j ] )
        flow.addEdge( in[ i ][ j ] , out[ i ][ j ] , 1 , 0 );
      if( (i + j) & 1 ){
        if( i > 1 )
          flow.addEdge( in[ i ][ j ] , out[ i - 1 ][ j ] ,
                        1 , -dn[ i - 1 ][ j ] );
        if( i + 1 <= n )
          flow.addEdge( in[ i ][ j ] , out[ i + 1 ][ j ] ,
                        1 , -dn[ i ][ j ] );
      }else{
        if( j > 1 )
          flow.addEdge( in[ i ][ j ] , out[ i ][ j - 1 ] ,
                        1 , -rgt[ i ][ j - 1 ]);
        if( j + 1 <= m )
          flow.addEdge( in[ i ][ j ] , out[ i ][ j + 1 ] ,
                        1 , -rgt[ i ][ j ]);
      }
    }
  pair<int,LL> ret = flow.solve();
  printf( "Case #%d: " , ++ _cs );
  if( ret.first != n * m ) puts( "Impossible" );
  else printf( "%lld\n" , -ret.second );
}
int main(){
  int t; scanf( "%d" , &t ); while( t -- ){
    init();
    solve();
  }
}
