// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long long ll;
typedef pair<int,int> PII;
#define mod9 1000000009ll
#define mod7 1000000007ll
//#define INF  1023456789ll
#define INF16 10000000000000000ll
#define FI first
#define SE second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define eps 1e-9
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(), (x).end()
ll getint(){
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
bool equal( D _x ,  D _y ){
    return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , cs;
/*********default*********/
const double INF  = 1000000000000.0;
struct Maxflow {
  static const int MAXV = 20010;
  struct Edge {
    int v;
    double c;
    int r;
    Edge(int _v, double _c, int _r) : v(_v), c(_c), r(_r) {}
  };
  int s, t;
  vector<Edge> G[MAXV*2];
  int iter[MAXV*2], d[MAXV*2], gap[MAXV*2], tot;
  void flowinit(int x) {
    tot = x+2;
    s = x+1, t = x+2;
    for(int i = 0; i <= tot; i++) {
      G[i].clear();
      iter[i] = d[i] = gap[i] = 0;
    }
  }
  void addEdge(int u, int v, double c) {
    G[u].push_back(Edge(v, c, SZ(G[v]) ));
    G[v].push_back(Edge(u, 0, SZ(G[u]) - 1));
  }
  double dfs(int p, double flow) {
    if(p == t) return flow;
    for(int &i = iter[p]; i < SZ(G[p]); i++) {
      Edge &e = G[p][i];
      if(e.c > 0. && d[p] == d[e.v]+1) {
        double f = dfs(e.v, min(flow, e.c));
        if(f > 0.) {
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

  double maxflow() {
    //puts("MF");
    double res = 0;
    gap[0] = tot;
    for(res = 0.; d[s] < tot; res += dfs(s, INF));
    return res;
  }
} flow;
#define N 110
int n , a[ N ] , m;
vector<int> v[ N ];
void build(){

}
void init(){
    n = getint();
    for( int i = 1 ; i <= n ; i ++ ){
        a[ i ] = getint();
        v[ i ].clear();
    }
    m = 0;
    for( int i = 1 ; i <= n ; i ++ ){
        for( int j = 1 ; j < i ; j ++ )
            if( a[ j ] > a[ i ] ) v[ i ].PB( j ) , m ++;
        for( int j = i + 1 ; j <= n ; j ++ )
            if( a[ j ] < a[ i ] ) v[ i ].PB( j ) , m ++;
    }

}
bool good( D g ){
    flow.flowinit( n );
    for( int i = 1 ; i <= n ; i ++ ){
        for( int j = 0 ; j < (int)v[ i ].size() ; j ++ )
            flow.addEdge( i , v[ i ][ j ] , 1 );
        flow.addEdge( flow.s , i , (D)m / 2. );
        flow.addEdge( i , flow.t , (D)m / 2. + 2. * g - (D)v[ i ].size() );
    }
    return ( (D)n * (D)m * 0.5 - flow.maxflow() ) > 0.;
}
void solve(){
    D l = 0.0 , mid , r = (D)m / 2;
    for( int i = 0 ; i < 100 ; i ++ ){
        mid = ( l + r ) * 0.5;
        if( good( mid ) ) l = mid;
        else r = mid;
    }
    printf( "Case #%d: %.12f\n" , ++ cs , ( l + r ) * 0.5 );
}
int main(){
    build();
    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
