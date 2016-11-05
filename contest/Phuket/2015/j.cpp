
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
const double EPS = 1e-8;
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
const int MAXN = 100010;
const int LOG  = 19;
struct HLD{
  int n;
  vector<int> g[MAXN];
  int sz[MAXN], dep[MAXN];
  int ts, tid[MAXN], tdi[MAXN], tl[MAXN], tr[MAXN];
  //  ts : timestamp , useless after yutruli
  //  tid[ u ] : pos. of node u in the seq.
  //  tdi[ i ] : node at pos i of the seq.
  //  tl , tr[ u ] : subtree interval in the seq. of node u
  int mom[MAXN][LOG], head[MAXN];
  // head[ u ] : head of the chain contains u
  void dfssz(int u, int p){
    dep[u] = dep[p] + 1;
    mom[u][0] = p;
    sz[u] = 1;
    head[u] = u;
    for(int& v:g[u]) if(v != p){
      dep[v] = dep[u] + 1;
      dfssz(v, u);
      sz[u] += sz[v];
    }
  }
  void dfshl(int u){
    //printf("dfshl %d\n", u);
    ts++;
    tid[u] = tl[u] = tr[u] = ts;
    tdi[tid[u]] = u;
    sort(ALL(g[u]),
         [&](int a, int b){return sz[a] > sz[b];});
    bool flag = 1;
    for(int& v:g[u]) if(v != mom[u][0]){
      if(flag) head[v] = head[u], flag = 0;
      dfshl(v);
      tr[u] = tr[v];
    }
  }
  inline int lca(int a, int b){
    if(dep[a] > dep[b]) swap(a, b);
    //printf("lca %d %d\n", a, b);
    int diff = dep[b] - dep[a];
    REPD(k, LOG-1, 0) if(diff & (1<<k)){
      //printf("b %d\n", mom[b][k]);
      b = mom[b][k];
    }
    if(a == b) return a;
    REPD(k, LOG-1, 0) if(mom[a][k] != mom[b][k]){
      a = mom[a][k];
      b = mom[b][k];
    }
    return mom[a][0];
  }
  void init( int _n ){
    n = _n;
    REP( i , 1 , n ) g[ i ].clear();
  }
  void addEdge( int u , int v ){
    g[ u ].push_back( v );
    g[ v ].push_back( u );
  }
  void yutruli(){
    dfssz(1, 0);
    ts = 0;
    dfshl(1);
    REP(k, 1, LOG-1) REP(i, 1, n)
      mom[i][k] = mom[mom[i][k-1]][k-1];
  }
  vector< tii > getPath( int u , int v ){
    vector< tii > res;
    while( tid[ u ] < tid[ head[ v ] ] ){
      res.push_back( tii(tid[ head[ v ] ] , tid[ v ]) );
      v = mom[ head[ v ] ][ 0 ];
    }
    res.push_back( tii( tid[ u ] , tid[ v ] ) );
    reverse( ALL( res ) );
    return res;
    /*
     * res : list of intervals from u to v
     * u must be ancestor of v
     * usage :
     * vector< tii >& path = tree.getPath( u , v )
     * for( tii tp : path ) {
     *   int l , r;tie( l , r ) = tp;
     *   upd( l , r );
     *   uu = tree.tdi[ l ] , vv = tree.tdi[ r ];
     *   uu ~> vv is a heavy path on tree
     * }
     */
  }
} tree;
typedef ll type;
struct Pt {
  type X , Y;
  bool operator<( const Pt& rhs ) const {
    if( X == rhs.X ) return Y < rhs.Y;
    return X < rhs.X;
  }
};
Pt operator+( const Pt& p1 , const Pt& p2 ){
  return { p1.X + p2.X , p1.Y + p2.Y };
}
Pt operator-( const Pt& p1 , const Pt& p2 ){
  return { p1.X - p2.X , p1.Y - p2.Y };
}
Pt operator*( const Pt& tp , const type& tk ){
  return { tp.X * tk , tp.Y * tk };
}
Pt operator/( const Pt& tp , const type& tk ){
  return { tp.X / tk , tp.Y / tk };
}
type operator*( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
type operator%( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
type norm2( const Pt& tp ){
  return tp * tp;
}
double norm( const Pt& tp ){
  return sqrt( norm2( tp ) );
}
Pt perp( const Pt& tp ){
  return { tp.Y , -tp.X };
}

int n;
Pt ip[ MAXN ];
vector<int> ch[ MAXN << 2 ];

type cross(int o, int a, int b){
  return (ip[a]-ip[o]) % (ip[b]-ip[o]);
}
void convex_hull(vector<int>& pt){
  sort(pt.begin(),pt.end(),[&](int a,int b){return ip[a]<ip[b];});
  int top=0;
  vector<int> stk(2*pt.size());
  for (int i=0; i<(int)pt.size(); i++){
    while (top >= 2 && cross(stk[top-2],stk[top-1],pt[i]) < 0)
      top--;
    stk[top++] = pt[i];
  }
  for (int i=pt.size()-2, t=top+1; i>=0; i--){
    while (top >= t && cross(stk[top-2],stk[top-1],pt[i]) < 0)
      top--;
    stk[top++] = pt[i];
  }
  stk.resize(top-1);
  pt.swap( stk );
}

void init( int id , int l , int r ) {
  if( l == r ) {
    int u = tree.tdi[ l ];
    ch[ id ] = { u };
    return;
  }
  int mid = ( l+r ) / 2;
  init( id*2 , l , mid );
  init( id*2+1 , mid+1 , r );
  ch[ id ].resize( r-l+1 );
  REP( i , l , r )
    ch[ id ][ i-l ] = tree.tdi[ i ];
  convex_hull( ch[ id ] );
}

void input() {
  R( n );
  tree.init( n );
  REP( i , 1 , n ) {
    int x , y; R( x , y );
    ip[ i ] = { x , y };
  }
  FOR( i , n-1 ) {
    int u , v; R( u , v );
    tree.addEdge( u , v );
  }
  tree.yutruli();
  init( 1 , 1 , n );
}

struct Ans {
  Pt dir;
  ll ans;
  vector<int> ids;
  bool upd( int id ) {
    ll tans = dir * ip[ id ];
    if( tans > ans || !SZ( ids ) ) {
      ans = tans;
      ids = { id };
      return 1;
    }
    if( tans == ans ) {
      ids.push_back( id );
      return 1;
    }
    return 0;
  }
} ac;

// <<<<< ===== >>>>>

// <
inline int sgn( type x ) {
  if( x > 0 ) return 1;
  if( x < 0 ) return -1;
  return 0;
}
inline bool cmp( const Pt& a , const Pt& b , const Pt& o ) {
  int pa = sgn( o % a );
  int pb = sgn( o % b );
  if( pa == 0 ) pa = sgn( a * o );
  if( pb == 0 ) pb = sgn( b * o );
  if( pa != pb ) return pa > pb;
  return ( a%b ) > 0;
}

inline void calc( int id ) {
  ac.upd( ch[ id ][ 0 ] );
  if( SZ( ch[ id ] ) == 1 ) return;

  ac.upd( ch[ id ].back() );

  Pt per = { -ac.dir.Y , ac.dir.X };
  Pt ori = ip[ ch[ id ][ 1 ] ] - ip[ ch[ id ][ 0 ] ];

  int ansl = 0 , ansr = SZ( ch[ id ] )-1;
  int l = 0 , r = SZ( ch[ id ] )-2;
  while( l <= r ) {
    int mid = ( l+r ) / 2;
    Pt v = ip[ ch[ id ][ mid+1 ] ] - ip[ ch[ id ][ mid ] ];
    if( cmp( v , per , ori ) ) {
      ansl = mid;
      l = mid+1;
    } else r = mid-1;
  }
  l = 0 , r = SZ( ch[ id ] )-2;
  while( l <= r ) {
    int mid = ( l+r ) / 2;
    Pt v = ip[ ch[ id ][ mid+1 ] ] - ip[ ch[ id ][ mid ] ];
    if( cmp( per , v , ori ) ) {
      ansr = mid;
      r = mid-1;
    } else l = mid+1;
  }
  REP( i , ansl , ansr )
    ac.upd( ch[ id ][ i ] );
}

void qry( int id , int l , int r , int a , int b ) {
  if( b < l || r < a ) return;
  if( a <= l && r <= b ) {
    calc( id );
    //for( int idx : ch[ id ] )
      //ac.upd( idx );
    return;
  }
  int mid = ( l+r ) / 2;
  qry( id*2 , l , mid , a , b );
  qry( id*2+1 , mid+1 , r , a , b );
  return;
}

void solve() {
  int q;R( q );
  while( q-- ) {
    int u , v , x , y;
    R( u , v , x , y );
    ac = { { -x , -y } , 0 , {} };
    int anc = tree.lca( u , v );
    //printf( "%d %d %d %d %d\n" , anc , u , v , -x , -y );
    auto path = tree.getPath( anc , u );
    for( tii p : path ) {
      int l , r; tie( l , r ) = p;
      qry( 1 , 1 , n , l , r );
    }
    path = tree.getPath( anc , v );
    for( tii p : path ) {
      int l , r; tie( l , r ) = p;
      qry( 1 , 1 , n , l , r );
    }
    sort( ALL( ac.ids ) );
    ac.ids.resize( unique( ALL( ac.ids ) ) - ac.ids.begin() );
    FOR( i , SZ( ac.ids ) )
      printf( "%d%c" , ac.ids[ i ] , " \n"[ i + 1 == SZ( ac.ids ) ] );
  }
}

int main() {
  //ip[ 1 ] = { 0 , 0 };
  //ip[ 2 ] = { 2 , -2 };
  //ip[ 3 ] = { 4 , -2 };
  //ip[ 4 ] = { 6 , 0 };
  //ip[ 5 ] = { 4 , 2 };
  //ip[ 6 ] = { 2 , 2 };
  //ip[ 7 ] = { 1 , 1 };
  //ch[ 1 ] = { 1 , 2 , 3 , 4 , 5 , 6 , 7 };
  //convex_hull( ch[ 1 ] );
  //for( int x : ch[ 1 ] ) printf( "%d " , x );
  //puts( " ----" );
  //ac = { { -1 , 1 } , 0 , {} };
  //calc( 1 );
  //for( int x : ac.ids ) printf( "%d " , x );
  //puts( " ac" );

  int tc;R( tc );REP( _ , 1 , tc ) {
    printf( "Case %d:\n" , _ );
    input();
    solve();
  }
}
