#include <bits/stdc++.h>
using namespace std;
#define SZ(c) ((int)(c).size())
#define N 1021
#define PB push_back
struct DisjointSet{
  // save() is like recursive
  // undo() is like return
  int n, fa[ N ], sz[ N ];
  vector< pair<int*,int> > h;
  vector<int> sp;
  void init( int tn ){
    n=tn;
    for( int i = 0 ; i <= n ; i ++ ){
      fa[ i ]=i;
      sz[ i ]=1;
    }
    sp.clear(); h.clear();
  }
  void assign( int *k, int v ){
    h.PB( {k, *k} );
    *k = v;
  }
  void save(){ sp.PB(SZ(h)); }
  void undo(){
    assert(!sp.empty());
    int last=sp.back(); sp.pop_back();
    while( SZ(h)!=last ){
      auto x=h.back(); h.pop_back();
      *x.first = x.second;
    }
  }
  int f( int x ){
    while( fa[ x ] != x ) x = fa[ x ];
    return x;
  }
  void uni( int x , int y ){
    x = f( x ); y = f( y );
    if( x == y ) return;
    if( sz[ x ] < sz[ y ] ) swap( x, y );
    assign( &sz[ x ] , sz[ x ] + sz[ y ] );
    assign( &fa[ y ] , x);
  }
}djs;
/*
  A template for Min Cost Max Flow
  tested with TIOJ 1724
*/
struct MinCostMaxFlow{
  static const int MAXV = 20010;
  static const int INF  = 1000000000;
  struct Edge{
    int v, cap, w, rev;
    Edge(){}
    Edge(int t2, int t3, int t4, int t5)
    : v(t2), cap(t3), w(t4), rev(t5) {}
  };
  int V, s, t;
  vector<Edge> g[MAXV];
  void init(int n){
    V = n+2;
    s = n+1, t = n+2;
    for(int i = 0; i <= V; i++) g[i].clear();
  }
  void addEdge(int a, int b, int cap, int w){
    //printf( "%d --(cap=%d,w=%d)--> %d\n" , a , cap , w , b );
    g[a].push_back(Edge(b, cap, w, (int)g[b].size()));
    g[b].push_back(Edge(a, 0, -w, (int)g[a].size()-1));
  }
  int d[MAXV], id[MAXV], mom[MAXV];
  bool inqu[MAXV];
  queue<int> q;
  //the size of qu should be much large than MAXV
  int solve(){
    int mxf = 0, mnc = 0;
    while(1){
      fill(d, d+1+V, INF);
      fill(inqu, inqu+1+V, 0);
      fill(mom, mom+1+V, -1);
      mom[s] = s;
      d[s] = 0;
      while( q.size() ) q.pop();
      q.push(s);
      inqu[s] = 1;
      while(q.size()){
        int u = q.front(); q.pop();
        inqu[u] = 0;
        for(int i = 0; i < (int) g[u].size(); i++){
          Edge &e = g[u][i];
          int v = e.v;
          if(e.cap > 0 && d[v] > d[u]+e.w){
            d[v] = d[u]+e.w;
            mom[v] = u;
            id[v] = i;
            if(!inqu[v]){
              q.push(v);
              inqu[v] = 1;
            }
          }
        }
      }
      if(mom[t] == -1) break ;
      int df = INF;
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
    //cerr << "mxf: " << mxf;
    //cerr << ", mnc: " << mnc << endl;
    return mxf;
    return mnc;
  }
} flow;
#define x1 sdjfksldfjlkx1
#define y1 sdjfksldfjlky1
#define x2 sdjfksldfjlkx2
#define y2 sdjfksldfjlky2
int n , x[ N ] , y[ N ];
bool neighbor( int x1 , int y1 , int x2 , int y2 ){
  if( x1 % 2 == x2 % 2 ) return false;
  if( x1 % 2 ){
    swap( x1 , x2 );
    swap( y1 , y2 );
  }
  int dx[]={1,-1,1};
  int dy[]={0,0,-1};
  for( int i = 0 ; i < 3 ; i ++ )
    if( x1 + dx[ i ] == x2 and
        y1 + dy[ i ] == y2 )
      return true;
  return false;
}
vector<int> v[ 2 ];
vector<int> nn[ N ];
void init(){
  cin >> n;
  for( int i = 0 ; i < n ; i ++ ){
    cin >> x[ i ] >> y[ i ];
    v[ abs( x[ i ] ) % 2 ].push_back( i );
  }
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      if( neighbor( x[ i ] , y[ i ] , x[ j ] , y[ j ] ) )
        nn[ i ].push_back( j );
}
int f[ N ];
void solve(){
  for( int three = 0 ; three <= n / 3 ; three ++ ){
    int two = n - three * 3;
    if( two % 2 ) continue;
    two >>= 1;
    int nd = two + three + three;
    flow.init( n + 1 );
    for( auto i : v[ 0 ] ){
      flow.addEdge( flow.s , i , 1 , 0 );
      flow.addEdge( flow.s , i , 1 , 1021 );
    }
    for( auto i : v[ 1 ] ){
      flow.addEdge( i , n + 1 , 1 , 0 );
      flow.addEdge( i , n + 1 , 1 , 1021 );
    }
    for( auto i : v[ 0 ] )
      for( auto j : nn[ i ] )
        flow.addEdge( i , j , 1 , 0 );
    flow.addEdge( n + 1 , flow.t , nd , 0 );
    int ret = flow.solve();
    //cout << "==============================" << endl;
    //cout << three << " " << ret << " " << nd << endl;
    if( ret != nd ) continue;
    djs.init( n );
    for( auto i : v[ 0 ] )
      for( auto nxt : flow.g[ i ] )
        if( 0 <= nxt.v and nxt.v < n and nxt.cap == 0 ){
          djs.uni( i , nxt.v );
          //cout << i << " " << nxt.v << endl;
        }
    vector<int> vv;
    bool ok = true;
    for( int i = 0 ; i < n ; i ++ ){
      if( djs.sz[ djs.f( i ) ] < 2 or
          djs.sz[ djs.f( i ) ] > 3 ){
        ok = false;
        break;
      }
      f[ i ] = djs.f( i );
      vv.push_back( f[ i ] );
    }
    if( not ok ) continue;
    sort( vv.begin() , vv.end() );
    vv.resize( unique( vv.begin() , vv.end() ) - vv.begin() );
    printf( "%d\n" , (int)vv.size() );
    for( int i = 0 ; i < n ; i ++ )
      printf( "%d%c" ,
              (int)(lower_bound( vv.begin() , vv.end() , f[ i ] ) - vv.begin() + 1) ,
              " \n"[ i + 1 == n ] );
    exit(0);
  }
  puts( "No solution" );
  exit(0);
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "tiling.in" , "r" , stdin );
  freopen( "tiling.out" , "w" , stdout );
#endif
  init();
  solve();
}
