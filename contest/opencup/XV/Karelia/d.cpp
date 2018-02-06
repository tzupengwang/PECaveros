#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
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
  void init(int x) {
    tot = x+2;
    s = x+1, t = x+2;
    for(int i = 0; i <= tot; i++) {
      G[i].clear();
      iter[i] = d[i] = gap[i] = 0;
    }
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
  int solve() {
    int res = 0;
    gap[0] = tot;
    for(res = 0; d[s] < tot; res += dfs(s, INF));
    return res;
  }
} flow;
#define N 3030
int n;
map< tuple<int,int,int> , int > v;
int gcd( int xi , int yi ){
  if( !xi or !yi ) return xi + yi;
  return __gcd( xi , yi );
}
map< pair<int,int> , int > y_to_id;
map< pair<int,int> , int > slope;
pair<int,int> to_fac( int xi , int yi ){
  int gg = gcd( xi , yi );
  xi /= gg;
  yi /= gg;
  if( yi < 0 ) return {-xi, -yi};
  return {xi, yi};
}
int yzor , ver;
void init(){
  scanf( "%d" , &n );
  v.clear();
  y_to_id.clear();
  slope.clear();
  yzor = -1;
  ver = -1;
  for( int i = 0 ; i < n ; i ++ ){
    int ai , bi , ci;
    scanf( "%d%d%d" , &ai , &bi , &ci );
    int gg = gcd( abs( ai ) , gcd( abs( bi ) , abs( ci ) ) );
    ai /= gg;
    bi /= gg;
    ci /= gg;
    if( ai < 0 ){
      ai = -ai;
      bi = -bi;
      ci = -ci;
    }else if( ai == 0 and bi < 0 ){
      ai = -ai;
      bi = -bi;
      ci = -ci;
    }
    if( bi == 0 ){
      if( ci == 0 )
        yzor = i;
      else
        ver = i;
    }else
      v[ make_tuple( ai , bi , ci ) ] = i;
  }
}
void add( map< pair<int,int> , int >& _id , const pair<int,int>& cp , int& idd ){
  auto it = _id.find( cp );
  if( it != _id.end() ) return;
  _id[ cp ] = idd ++;
}
map< pair<int,int> , int > rec;
void solve(){
  int s_id = 0 , y_id = 0;
  for( auto l : v ){
    int ai = get<0>( l.first );
    int bi = get<1>( l.first );
    int ci = get<2>( l.first );
    add( slope   , to_fac( -ai , bi ) , s_id );
    add( y_to_id , to_fac( -ci , bi ) , y_id );
  }
  flow.init( s_id + y_id );
  for( int i = 0 ; i < s_id ; i ++ )
    flow.addEdge( flow.s , i , 1 );
  for( int i = 0 ; i < y_id ; i ++ )
    flow.addEdge( s_id + i , flow.t , 1 );
  rec.clear();
  for( auto l : v ){
    int ai = get<0>( l.first );
    int bi = get<1>( l.first );
    int ci = get<2>( l.first );
    int ss = slope[ to_fac( -ai , bi ) ];
    int tt = s_id + y_to_id[ to_fac( -ci , bi ) ];
    flow.addEdge( ss , tt , 1 );
    rec[ { ss , tt } ] = l.second;
  }
  flow.solve();
  vector<int> vans;
  for( int i = 0 ; i < s_id ; i ++ )
    for( auto e : flow.G[ i ] )
      if( s_id <= e.v and e.v < s_id + y_id and e.c == 0 )
        vans.push_back( rec[ { i , e.v } ] );
  if( ver != -1 ) vans.push_back( ver );
  if( vans.empty() and yzor != -1 )
    vans = {yzor};
  printf( "%d\n" , (int)vans.size() );
  for( size_t i = 0 ; i < vans.size() ; i ++ )
    printf( "%d%c" , vans[ i ] + 1 , " \n"[ i + 1 == vans.size() ] );
}
int main(){
  int t; scanf( "%d" , &t ); while( t -- ){
    init();
    solve();
  }
}
