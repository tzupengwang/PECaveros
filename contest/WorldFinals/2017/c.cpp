#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define MAXV 20010
#define INFf 1e6
#define INFc 1e14
struct MinCostMaxFlow{
  struct Edge{
    int v, cap;
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
    for(int i = 0 ; i <= V; i++) g[i].clear();
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
    int mxf = 0; LL mnc=0;
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
        for(int i = 0 ; i <(int)g[u].size() ; i ++ ){
          Edge& e = g[u][i];
          int v = e.v;
          if(e.cap > 0 and d[v] > d[u] + e.w ){
            d[v] = d[u] + e.w;
            mom[v] = u;
            id[v] = i;
            if(!inqu[v]) q.push(v), inqu[v] = 1;
          }
        }
      }
      if( mom[t] == -1 ) break;
      int df = INFf;
      for(int u = t ; u != s ; u = mom[u] )
        df = min( df , g[mom[u]][id[u]].cap );
      for(int u = t ; u != s ; u = mom[u] ){
        Edge &e = g[mom[u]][id[u]];
        e.cap             -= df;
        g[e.v][e.rev].cap += df;
      }
      mxf += df;
      mnc += df * d[t];
    }
    return {mxf, mnc};
  }
} flow;
#define N 111
int r , c , mxr[ N ] , mxc[ N ] , a[ N ][ N ];
int main(){
  cin >> r >> c;
  LL all = 0;
  for( int i = 0 ; i < r ; i ++ )
    for( int j = 0 ; j < c ; j ++ ){
      int x; cin >> x;
      mxr[ i ] = max( mxr[ i ] , x );
      mxc[ j ] = max( mxc[ j ] , x );
      a[ i ][ j ] = x;
      all += x;
    }
  flow.init( r + c );
  for( int i = 0 ; i < r ; i ++ )
    if( mxr[ i ] )
      flow.addEdge( flow.s , i , 1 , 0 );
  for( int i = 0 ; i < c ; i ++ )
    if( mxc[ i ] )
      flow.addEdge( r + i , flow.t , 1 , 0 );
  for( int i = 0 ; i < r ; i ++ )
    for( int j = 0 ; j < c ; j ++ )
      if( mxr[ i ] == mxc[ j ] and a[ i ][ j ] > 0 )
        flow.addEdge( i , r + j , 1 , -mxr[ i ] );
  pair<int,LL> ret = flow.solve();
  LL ans = 0;
  ans += accumulate( mxr , mxr + r , 0LL );
  ans += accumulate( mxc , mxc + c , 0LL );
  ans += ret.second;
  int cnt = 0;
  for( int i = 0 ; i < r ; i ++ )
    for( int j = 0 ; j < c ; j ++ )
      if( a[ i ][ j ] )
        cnt ++;
  for( int i = 0 ; i < r ; i ++ )
    if( mxr[ i ] )
      cnt --;
  for( int i = 0 ; i < c ; i ++ )
    if( mxc[ i ] )
      cnt --;
  cnt += ret.first;
  ans += cnt;
  printf( "%lld\n" , all - ans );
}
