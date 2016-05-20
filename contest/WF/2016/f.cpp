
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

const int MAXN = 1e6+10;
const ll INF = 1e12+10;

template<typename T>
using minheap = priority_queue<T,vector<T>,greater<T>>;

struct BIT {
  int sz , dat[ MAXN*2 ];
  void init( int _sz ) {
    sz = _sz;
    fill( dat , dat+sz+1 , 0 );
  }
  void upd( int id , int x ) {
    for( int i = id ; i <= sz ; i += i&-i )
      dat[ i ] += x;
  }
  int qry( int id ) {
    int res = 0;
    for( int i = id ; i ; i -= i&-i )
      res += dat[ i ];
    return res;
  }
};

int n , m , root , tot;
int mom[ MAXN ];
ll c[ MAXN ];
vector<int> g[ MAXN ];
char in[ MAXN ][ 11 ];

void read() {
  R( n , m );
  root = n+1;
  tot = n+m+1;
  REP( i , 1 , n ) {
    R( in[ i ] , mom[ i ] , c[ i ] );
    mom[ i ] += root;
    g[ mom[ i ] ].push_back( i );
  }
  REP( i , root+1 , root+m ) {
    R( mom[ i ] , c[ i ] );
    mom[ i ] += root;
    g[ mom[ i ] ].push_back( i );
  }
}

int st[ MAXN ] , ed[ MAXN ];
ll dep[ MAXN ];

void dfs( int u , ll d ) {
  static int ts = 0;
  st[ u ] = ++ts;
  dep[ u ] = d;
  for( int v : g[ u ] )
    dfs( v , d+c[ v ] );
  ed[ u ] = ++ts;
}

void predo() {
  dfs( root , 0 );
}

BIT bit;
vector<pli> leaves;
minheap<pli> heap;

int cnt[ MAXN ];
int ans[ MAXN ];
ll dp[ MAXN ];

inline void add( int u , ll x ) {
  debug( "add %d %lld\n" , u , x );
  bit.upd( st[ u ] , 1 );
  bit.upd( ed[ u ] , -1 );
  heap.push( { x , u } );
}

inline pli pop() {
  pli p = heap.top();heap.pop();
  bit.upd( st[ p.second ] , -1 );
  bit.upd( ed[ p.second ] , 1 );
  return p;
}

void solve() {
  bit.init( tot*2 );

  REP( i , 1 , tot ) cnt[ i ] = SZ( g[ i ] );

  REP( i , 1 , tot ) dp[ i ] = INF;
  
  REP( i , 1 , n ) leaves.push_back( { dep[ i ] , i } );
  sort( ALL( leaves ) );

  REP( i , 1 , n ) {
    add( i , c[ i ] );
  }

  for( pli pr : leaves ) {
    ll tdep = pr.first;
    int u = pr.second;

    debug( "now %d with %lld\n" , u , tdep );

    while( SZ( heap ) && heap.top().first <= tdep ) {
      ll len;int v;
      tie( len , v ) = pop();
      debug( "pop %d %lld\n" , v , len );
      int p = mom[ v ];
      dp[ p ] = min( dp[ p ] , len );
      cnt[ p ]--;
      if( cnt[ p ] == 0 ) {
        add( p , dp[ p ]+c[ p ] );
      }
    }

    debug( "sz of heap %d\n" , SZ( heap ) );

    ans[ u ] = SZ( heap )-bit.qry( st[ u ] )+1;
    //ans[ u ] = SZ( heap )+1;
  }

  REP( i , 1 , n ) printf( "%s %d\n" , in[ i ] , ans[ i ] );

}

int main()
{
  read();
  predo();
  solve();
}
