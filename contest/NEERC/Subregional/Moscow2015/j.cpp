// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long double LD;
typedef long long ll;
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<ll,ll> PLL;
typedef pair<LD,LD> Pt;
#define mod9 1000000009ll
#define mod7 1000000007ll
#define INF16 10000000000000000ll
#define FI first
#define SE second
#define X FI
#define Y SE
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define eps 1e-9
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(), (x).end()
#ifndef ONLINE_JUDGE
#define debug(...) printf(__VA_ARGS__)
#else 
#define debug(...)
#endif
inline ll getint(){
  ll _x=0,_tmp=1; char _tc=getchar();    
  while( (_tc<'0'||_tc>'9')&&_tc!='-' ) _tc=getchar();
  if( _tc == '-' ) _tc=getchar() , _tmp = -1;
  while(_tc>='0'&&_tc<='9') _x*=10,_x+=(_tc-'0'),_tc=getchar();
  return _x*_tmp;
}
ll mypow( ll _a , ll _x , ll _mod ){
  if( _x == 0 ) return 1ll;
  ll _tmp = mypow( _a , _x / 2 , _mod );
  _tmp = ( _tmp * _tmp ) % _mod;
  if( _x & 1 ) _tmp = ( _tmp * _a ) % _mod;
  return _tmp;
}
inline ll add( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x + _y;
  if( _ >= _mod ) _ -= _mod;
  return _;
}
inline ll sub( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x - _y;
  if( _ < 0 ) _ += _mod;
  return _;
}
inline ll mul( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x * _y;
  if( _ >= _mod ) _ %= _mod;
  return _;
}
inline bool equal( D _x ,  D _y ){
  return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , cs;
/*********default*********/
struct MinCostMaxFlow{
  static const int MAXV = 22222;
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
    for(int i = 1; i <= V; i++) g[i].clear();
  }
  void addEdge(int a, int b, int cap, int w){
    // printf("addEdge %d %d %d %d\n", a, b, cap, w);
    g[a].push_back(Edge(b, cap, w, (int) g[b].size()));
    g[b].push_back(Edge(a, 0, -w, ((int) g[a].size()) - 1));
  }
  int d[MAXV], id[MAXV], mom[MAXV];
  bool inqu[MAXV];
  int qu[2000000], ql, qr;//the size of qu should be much large than MAXV
  int mncmxf(){
    int mxf = 0, mnc = 0;
    while(1){
      fill(d+1, d+1+V, INF);
      fill(inqu+1, inqu+1+V, 0);
      fill(mom+1, mom+1+V, -1);
      mom[s] = s;
      d[s] = 0;
      ql = 1, qr = 0;
      qu[++qr] = s;
      inqu[s] = 1;
      while(ql <= qr){
        int u = qu[ql++];
        inqu[u] = 0;
        for(int i = 0; i < (int) g[u].size(); i++){
          Edge &e = g[u][i];
          int v = e.v;
          if(e.cap > 0 && d[v] > d[u]+e.w){
            d[v] = d[u]+e.w;
            mom[v] = u;
            id[v] = i;
            if(!inqu[v]) qu[++qr] = v, inqu[v] = 1;
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
      //printf("mxf %d mnc %d\n", mxf, mnc);
      mxf += df;
      mnc += df*d[t];
      //printf("mxf %d mnc %d\n", mxf, mnc);
    }
    return mnc;
  }
} flow;
#define N 110
void build(){

}
int n , m , k , cst[ N ] , x[ N ] , za;
#define INF 100000
bool nd[ N ][ N ];
int trans_grl_in( int lyr , int grl ){
  return m + ( ( lyr - 1 ) * k + grl ) * 2 - 1;
}
int trans_grl_out( int lyr , int grl ){
  return m + ( ( lyr - 1 ) * k + grl ) * 2;
}
int input[ N ][ N ];
void init(){
  n = getint();
  m = getint();
  k = getint();
  if( k == 0 ){
    puts( "0" );
    exit( 0 );
  }
  for( int i = 1 ; i <= k ; i ++ )
    cst[ i ] = getint();
  for( int i = 1 ; i <= n ; i ++ ){
    x[ i ] = getint();
    for( int j = 1 ; j <= x[ i ] ; j ++ ){
      input[ i ][ j ] = getint();
      nd[ i ][ input[ i ][ j ] ] = true;
    }
    za += m - x[ i ];
  }
  flow.init( m + k * n * 2 );
//  addEdge(int a, int b, int cap, int w)
  for( int i = 1 ; i <= m ; i ++ )
    flow.addEdge( flow.s , i , 1 , 0 );
  for( int i = 1 ; i <= k ; i ++ )
    if( nd[ 1 ][ i ] ){
      for( int j = 1 ; j <= m ; j ++ )
        flow.addEdge( j , trans_grl_in( 1 , i ) , 1 , 0 );
    }else{
      for( int j = 1 ; j <= m ; j ++ )
        flow.addEdge( j , trans_grl_in( 1 , i ) , 1 , INF );
    }
  for( int i = 2 ; i <= n ; i ++ ){
    for( int j = 1 ; j <= k ; j ++ )
      if( nd[ i ][ j ] ){
        for( int u = 1 ; u <= k ; u ++ ){
          int _cst = ( j == u ? 0 : cst[ j ] );
          flow.addEdge( trans_grl_out( i - 1 , u ) ,
                        trans_grl_in( i , j ) , 1 , _cst );
        }
      }else
        flow.addEdge( trans_grl_out( i - 1 , j ),
                      trans_grl_in( i , j ) , 1 , INF );
  }
  for( int i = 1 ; i <= k ; i ++ )
    flow.addEdge( trans_grl_out( n , i ) , flow.t , 1 , 0 );
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= k ; j ++ )
      flow.addEdge( trans_grl_in( i , j ) ,
                    trans_grl_out( i , j ) , 1 , 0 );
}
int ans[ 2 * N * N ];
void solve(){
  printf( "%d\n" , flow.mncmxf() - za * INF );
  for( int i = 1 ; i <= m ; i ++ ) ans[ i ] = i;
  for( int i = 1 ; i < flow.s ; i ++ )
    for( int j = 0 ; j < (int)flow.g[ i ].size() ; j ++ )
      if( flow.g[ i ][ j ].cap == 0 &&
          flow.g[ i ][ j ].v > i ){
        // printf( "%d -> %d\n" , i , flow.g[ i ][ j ].v );
        ans[ flow.g[ i ][ j ].v ] = ans[ i ];
      }
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= x[ i ] ; j ++ )
      printf( "%d%c" , ans[ trans_grl_in( i , input[ i ][ j ] ) ] ,
                       " \n"[ j == x[ i ] ] );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
