#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define int long long 
#define MAXV 20010
#define INFf 20010
#define INFc 10000000000000000LL
struct MinCost{
  struct Edge{
    int v, cap;
    LL w;
    int rev;
    Edge(){}
    Edge(int t2, int t3, int t4, int t5){
      v = t2;
      cap = t3;
      w = t4;
      rev = t5;
    }
  };
  int V , s , t;
  vector<Edge> g[ MAXV ];
  void init( int n ){
    V = n + 2;
    s = n + 1; t = n + 2;
    for( int i = 0 ; i <= V ; i ++ )
      g[ i ].clear();
  }
  void addEdge( int a , int b , int cap , LL w ){
    g[a].push_back(Edge(b, cap, +w, (int)g[b].size()    ));
    g[b].push_back(Edge(a, 0  , -w, (int)g[a].size() - 1));
  }
  LL d[ MAXV ];
  int id[ MAXV ] , mom[ MAXV ];
  bool inqu[ MAXV ];
  queue<int> q;
  LL solve(){
    int mxf = 0;
    LL mnc = 0;
    while( true ){
      fill( d , d + V + 1 , INFc );
      fill( inqu , inqu + V + 1 , 0 );
      fill( mom , mom + V + 1 , -1 );
      mom[ s ] = s;
      d[ s ] = 0;
      q.push( s ); inqu[ s ] = 1;
      while(q.size()){
        int u = q.front(); q.pop();
        inqu[ u ] = 0;
        for( int i = 0 ; i < (int)g[ u ].size() ; i ++ ){
          Edge &e = g[u][i];
          int v = e.v;
          if(e.cap > 0 and d[ v ] > d[ u ] + e.w ){
            d[ v ] = d[ u ] + e.w;
            mom[ v ] = u;
            id[ v ] = i;
            if( !inqu[v] )
              q.push(v), inqu[v] = 1;
          }
        }
      }
      if(mom[t] == -1) break;
      int df = INFf;
      for( int u = t ; u != s ; u = mom[u] )
        df = min(df, g[mom[u]][id[u]].cap);
      for( int u = t ; u != s ; u = mom[u] ){
        Edge &e = g[mom[u]][id[u]];
        e.cap -= df;
        g[e.v][e.rev].cap += df;
      }
      mxf += df;
      mnc += df * d[ t ];
    }
    return mnc;
  }
} flow;
#define N 111
const LL inf = 10000000000LL;
int n , k;
int32_t main(){
  cin >> n >> k;
  flow.init( (n + 1) * 2 );
  flow.addEdge( flow.s , 2 , k , 0 );
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = i + 1 ; j <= n + 1 ; j ++ ){
      int d; cin >> d;
      flow.addEdge( i * 2 , j * 2 - 1 , 1 , d );
    }
  for( int i = 2 ; i <= n + 1 ; i ++ ){
    flow.addEdge( flow.s , i * 2 , 1 , 0 );
    //flow.addEdge( i * 2 , i * 2 - 1 , 1 , 0 );
    flow.addEdge( i * 2 - 1 , flow.t , 1 , 0 );
  }
  cout << flow.solve() << endl;
}
