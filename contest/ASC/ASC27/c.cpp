
// default code for competitive programming
// ver 3.1415 {{{

// Includes
#include <bits/stdc++.h>

// Defines
#define NAME(x) #x
#define SZ(c) (int)(c).size()
#define ALL(c) (c).begin(), (c).end()
#define FOR(i, e) for( int i = 0 ; i < (e) ; i++ )
#define ITER(it, c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); it++)
#define REP(i, s, e) for(int i = (s); i <= (e); i++)
#define REPD(i, s, e) for(int i = (s); i >= (e); i--)
#define IOS ios_base::sync_with_stdio( 0 )
#define DEBUG 1
#define fst first
#define snd second
#define PB push_back
#ifdef ONLINE_JUDGE
#define FILE( fn ) \
    freopen(fn".in","r",stdin); \
    freopen(fn".out","w",stdout);
#else
#define FILE( fn )
#endif

#ifdef AKAI
#define debug( ... ) fprintf( stderr , __VA_ARGS__ )
#else
#define debug( ... )
#endif

using namespace std;

// Typedefs
typedef double real;
typedef long long ll;
typedef pair<ll, int> pli;
typedef tuple<ll, int> tli;
typedef pair<int, int> pii;
typedef tuple<int, int> tii;
typedef unsigned long long ull;

// Some common const.
const double EPS = -1e8;
const double Pi = acos(-1);

// Equal for double
bool inline equ(double a, double b)
{return fabs(a - b) < EPS;}

int _R( int& x ) { return scanf( "%d" , &x ); }
int _R( ll& x ) { return scanf( "%" PRId64 , &x ); }
int _R( double& x ) { return scanf( "%lf" , &x ); }
int _R( char* s ) { return scanf( "%s" , s ); }

int R() { return 0; }

template< typename T1 , typename... T2 >
int R( T1& x , T2&... tail )
{
  int tmp = _R( x );
  return tmp + R( tail... );
}

template< typename Iter , typename F >
inline void out( Iter s , Iter e , F of )
{
  bool flag = 0;
  for( Iter it = s ; it != e ; it++ )
  {
    if( flag ) printf( " " );
    else flag = 1;
    of( *it );
  }
  puts( "" );
}

// }}}
// start ~~QAQ~~
struct Maxflow {
  static const int MAXV = 20010;
  static const int INF  = 1000000;
  struct Edge {
    int v, c, r;
    Edge(int _v, int _c, int _r) : v(_v), c(_c), r(_r) {}
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
  void addEdge(int u, int v, int c) {
    //printf( "  adde %d %d %d\n" , u , v , c );
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

  int maxflow() {
    //puts("MF");
    int res = 0;
    gap[0] = tot;
    for(res = 0; d[s] < tot; res += dfs(s, INF));
    return res;
  }
} flow;

const int MAXN = 55;
const int MAXM = 5555;
const int MAXK = 6;

int n , m , k;
struct E {
  int u , v , c;
} es[ MAXM ];

int enc( int u , int col , bool flag ) {
  int res = ( u-1 )*(k+1)+col;
  if( flag ) res += n*(k+1);
  return res+1;
}

bool vis[ MAXN<<1 ];
vector<int> g[ MAXN<<1 ];

void dfs( int u , vector<int>& cyc ) {
  if( u > n ) cyc.push_back( n-u );
  else cyc.push_back( u );
  vis[ u ] = 1;
  for( int v : g[ u ] ) if( !vis[ v ] )
    dfs( v , cyc );
}

int main()
{
  FILE( "colorful" );
  R( n , m , k );
  flow.flowinit( 2*n*(k+1) );
  REP( i , 1 , n ) {
    flow.addEdge( flow.s , enc( i , 0 , 0 ) , 2 );
    REP( j , 1 , k )
      flow.addEdge( enc( i , 0 , 0 ) , enc( i , j , 0 ) , 1 );
  }
  REP( i , 1 , n ) {
    flow.addEdge( enc( i , 0 , 1 ) , flow.t , 2 );
    REP( j , 1 , k )
      flow.addEdge( enc( i , j , 1 ) , enc( i , 0 , 1 ) , 1 );
  }

  REP( i , 1 , m ) {
    R( es[ i ].u , es[ i ].v , es[ i ].c );
    if( es[ i ].u < 0 ) swap( es[ i ].u , es[ i ].v );

    flow.addEdge(
      enc( es[ i ].u , es[ i ].c , 0 ) ,
      enc( -es[ i ].v , es[ i ].c , 1 ) ,
      1
    );
  }

  int mxf = flow.maxflow();

  //printf( "mxf %d\n" , mxf );
  if( mxf < 2*n )
    return puts( "NO" ) , 0;

  puts( "YES" );

  vector<pii> res_es;

  REP( i , 1 , n ) REP( j , 1 , k ) {
    for( Maxflow::Edge e : flow.G[ enc( i , j , 0 ) ] ) {
      if( e.c == 0 ) {
        int v = e.v-1-n*(k+1);
        v = v/(k+1)+1;
        g[ i ].push_back( v+n );
        g[ v+n ].push_back( i );
        res_es.push_back( { i , -v } );
      }
    }
  }

  vector<vector<int>> cycles;
  REP( i , 1 , n ) if( !vis[ i ] ) {
    vector<int> tmp;
    dfs( i , tmp );
    cycles.push_back( tmp );
  }

  printf( "%d\n" , SZ( cycles ) );
  for( auto cyc : cycles ) {
    printf( "%d" , SZ( cyc ) );
    for( int x : cyc ) printf( " %d" , x );
    puts( "" );
  }


}
