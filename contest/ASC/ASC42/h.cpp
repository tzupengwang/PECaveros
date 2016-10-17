#include <bits/stdc++.h>
using namespace std;
#define SZ(c) ((int)(c).size())
struct Maxflow {
  static const int MAXV = 20010;
  static const int INF  = 1000000;
  struct Edge {
    int v, c, r , ret;
    Edge(int _v, int _c, int _r,int _ret = 0):
      v(_v), c(_c), r(_r), ret(_ret) {}
  };
  int s, t;
  vector<Edge> G[MAXV*2];
  int iter[MAXV*2], d[MAXV*2], gap[MAXV*2], tot;
  void init(int x) {
    tot = x+2;
    s = x+1, t = x+2;
    for(int i = 0; i <= tot; i++){
      G[i].clear();
      iter[i] = d[i] = gap[i] = 0;
    }
  }
  void addEdge(int u, int v, int c , int ret = 0) {
    G[u].push_back(Edge(v, c, SZ(G[v]), ret ));
    G[v].push_back(Edge(u, 0, SZ(G[u]) - 1, ret));
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
    //puts("MF");
    int res = 0;
    gap[0] = tot;
    for(res = 0; d[s] < tot; res += dfs(s, INF));
    return res;
  }
} flow;
Maxflow::Edge e(1, 1, 1);
#define N 101010
int n , m , k[ N ];
inline int toint( const vector<int>& s , int tar ){
  int ret = 0;
  for( int i = 0 ; i < tar ; i ++ )
    ret = ret * 4 + s[ i ];
  return ret;
}
inline vector<int> tovec( int s , int tar ){
  vector<int> ret;
  for( int i = 0 ; i < tar ; i ++ ){
    ret.push_back( s % 4 );
    s /= 4;
  }
  reverse( ret.begin() , ret.end() );
  return ret;
}

inline vector<int> mcp( vector<int> s){
  int nn = (int)s.size();
  for( int i = 0 ; i < nn ; i ++ )
    s.push_back( s[ i ] );
  int i=0, j=1;
  while (i<n && j<n){
    int kk = 0;
    while (kk < n && s[i+kk] == s[j+kk]) kk++;
    if (s[i+kk] <= s[j+kk]) j += kk+1;
    else i += kk+1;
    if (i == j) j++;
  }
  int ans = i < nn ? i : j;
  vector< int > ret;
  for( int u = ans ; u < ans + n ; u ++ )
    ret.push_back( s[ u ] );
  return ret;
}
void init(){
  scanf( "%d%d" , &n , &m );
  for( int i = 0 ; i < m ; i ++ )
    scanf( "%d" , &k[ i ] );
  sort( k , k + m );
}
vector< int > lft , rgt;
int clr[ N ];
set< vector<int> > S;
vector< int > vv;
void gogogo( int now , vector< int >& co , int rot ){
  if( now == n - ( 1 - rot ) ){
    if( rot ) co.push_back( toint( mcp( vv ) , n ) );
    else co.push_back( toint( vv , n - 1 ) );
    return;
  }
  for( int i = 0 ; i < m ; i ++ )
    if( clr[ i ] > 0 ){
      vv[ now ] = i;
      clr[ i ] --;
      gogogo( now + 1 , co , rot );
      clr[ i ] ++;
    }
}
void gogo( const vector<int>& v ){
  for( int i = 0 ; i < m ; i ++ )
    clr[ i ] = k[ v[ i ] ];
  vector< int > cc;
  for( int i = 0 ; i < m ; i ++ )
    cc.push_back( clr[ i ] );
  if( S.count( cc ) ) return;
  S.insert( cc );
  vv.resize( n );
  for( int i = 0 ; i < m ; i ++ ){
    clr[ i ] --;
    gogogo( 0 , lft , 0 );
    clr[ i ] ++;
  }
  gogogo( 0 , rgt , 1 );
}
vector< pair< pair<int,int> , pair<int,int> > > cand_edge;
inline void build_edge( int id , int x ){
  vector<int> tv = tovec( x , n - 1 );
  int cnt[ 4 ] = {};
  for( int u : tv ) cnt[ u ] ++;
  vector< pair<int,int> > v2;
  for( int i = 0 ; i < m ; i ++ )
    v2.push_back( { cnt[ i ] , i } );
  sort( v2.begin() , v2.end() );
  int req = 0;
  for( int i = 0 ; i < m ; i ++ )
    if( v2[ i ].first != k[ i ] )
      req = v2[ i ].first;
  vector< int > pos;
  for( int i = 0 ; i < m ; i ++ )
    if( v2[ i ].first == req )
      pos.push_back( v2[ i ].second );
  tv.resize( n );
  for( int cand : pos ){
    tv[ n - 1 ] = cand;
    int wh = lower_bound( rgt.begin() , rgt.end() , toint( mcp( tv ) , n ) ) - rgt.begin();
    cand_edge.push_back( { { id , (int)lft.size() + wh + 1 } , { 1 , cand } } );
    // printf( "%d %d %d %d\n" , id - 1 , wh , 1 , cand );
  }
}
int combo[ N ];
void build_build(){
  for( size_t i = 0 ; i < rgt.size() ; i ++ ){
    combo[ i ] = 1;
    vector< int > xv = tovec( rgt[ i ] , n );
    for( int j = 1 ; j < n ; j ++ ){
      vector< int > yv;
      for( int u = 0 ; u < n ; u ++ )
        yv.push_back( xv[ ( j + u ) % n ] );
      bool same = true;
      for( int u = 0 ; u < n && same ; u ++ )
        if( yv[ u ] != xv[ u ] )
          same = false;
      if( same ) combo[ i ] ++;
    }
  }
}
inline bool okay( int tar ){
  flow.init( (int)lft.size() + (int)rgt.size() );
  for( auto i : cand_edge )
    flow.addEdge( i.first.first , i.first.second , i.second.first , i.second.second );
  for( size_t i = 0 ; i < lft.size() ; i ++ )
    flow.addEdge( flow.s , i + 1 , 1 );
  int nd = 0;
  for( size_t i = 0 ; i < rgt.size() ; i ++ ){
    int xar = tar / combo[ i ] + ( tar % combo[ i ] != 0 );
    flow.addEdge( (int)lft.size() + i + 1 , flow.t , xar );
    nd += xar;
  }
  return flow.solve() == nd;
}
inline void print_vec( int x , int tar ){
  vector<int> vvv = tovec( x , tar );
  for( int u : vvv ) printf( "%d" , u );
  puts( "" );
}
void solve(){
  vector< int > v;
  for( int i = 0 ; i < n ; i ++ ) v.push_back( i );
  do gogo( v );
  while( next_permutation( v.begin() , v.end() ) );
  sort( lft.begin() , lft.end() );
  lft.resize( unique( lft.begin() , lft.end() ) - lft.begin() );
  sort( rgt.begin() , rgt.end() );
  rgt.resize( unique( rgt.begin() , rgt.end() ) - rgt.begin() );
  for( size_t i = 0 ; i < lft.size() ; i ++ )
    build_edge( i + 1 , lft[ i ] );
  build_build();

  // printf( "left:\n" ) ;
  // for( int u : lft ) print_vec( u , n - 1 );
  // printf( "right:\n" ) ;
  // for( int u : rgt ) print_vec( u , n );

  int l = 1 , r = n , ans = 0;
  while( l <= r ){
    int mid = ( l + r ) >> 1;
    // printf( "bi %d\n" , mid );
    if( okay( mid ) ) ans = mid , l = mid + 1;
    else r = mid - 1;
  }
  okay( ans );
  printf( "%d\n" , ans );
  for( size_t i = 0 ; i < lft.size() ; i ++ ){
    int rans = 1;
    for( auto ee : flow.G[ i + 1 ] ){
      if( ee.c == 0 && ee.v != flow.s ){
        // printf( " %d " , ee.v );
        // printf( " %d\n" , ee.ret + 1 );
        rans = ee.ret + 1;
        break;
      }
    }
    vector<int> iv = tovec( lft[ i ] , n - 1 );
    for( int x : iv ) printf( "%d" , x + 1 );
    printf( " %d\n" , rans );
  }
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "hats.in" , "r" , stdin );
  freopen( "hats.out" , "w" , stdout );
#endif
  init();
  solve();
}
