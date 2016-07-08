
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

const int MAXN = 30010;
const int MAXD = 400;

int n;
struct E {
  long long u , v , c;
} es[ MAXN ];

int mom[ MAXN ] , dep[ MAXN ];
vector<long long> g[ MAXN ];
long long buf[ MAXN ][ MAXD*2+20 ];
long long *cnt[ MAXN ];
bool upded[ MAXN ];

void dfs( int u , int p , long long d ) {
  mom[ u ] = p;
  dep[ u ] = d;
  for( int v : g[ u ] )
    if( v != p ) dfs( v , u , d+1 );
}

void input() {
  R( n );
  REP( i , 1 , n-1 ) {
    R( es[ i ].u , es[ i ].v , es[ i ].c );
    g[ es[ i ].u ].push_back( es[ i ].v );
    g[ es[ i ].v ].push_back( es[ i ].u );
  }
}

void predo() {
  dfs( 1 , 0 , 1 );
  REP( i , 1 , n-1 ) {
    if( dep[ es[ i ].u ] < dep[ es[ i ].v ] )
      swap( es[ i ].u , es[ i ].v );
  }
  sort( es+1 , es+n , [&]( const E& a , const E& b ) {
    return a.c < b.c;
  } );
  REP( i , 1 , n ) cnt[ i ] = buf[ i ] + MAXD+10;
  REP( i , 1 , n ) {
    int now = i , tlen = 0;
    while( now ) {
      cnt[ now ][ tlen ]++;
      now = mom[ now ];
      tlen++;
    }
  }
}

inline void upd( int u ) {
  debug( "upd %d\n" , u );
  int now = u;
  while( mom[ now ] ) {
    //debug( "now %d\n" , now );
    int p = mom[ now ];
    REP( d , -MAXD , MAXD ) {
      int del = 1;
      if( upded[ now ] ) del = -1;
      cnt[ p ][ d + del ] -= cnt[ now ][ d ];
    }
    now = mom[ now ];
  }
  upded[ u ] = 1;
  now = u;
  while( mom[ now ] ) {
    //debug( "now %d\n" , now );
    int p = mom[ now ];
    REP( d , -MAXD , MAXD ) {
      int del = 1;
      if( upded[ now ] ) del = -1;
      cnt[ p ][ d + del ] += cnt[ now ][ d ];
    }
    now = mom[ now ];
  }

  REP( i , 1 , n ) {
    printf( "cnt %d\n" , i );
    REP( j , -4 , 4 ) printf( "  %d %d\n" , j , cnt[ i ][ j ] );
  }
}

inline ll qry( int u ) {
  ll res = 0;
  long long prv = u , now = mom[ u ] , prv_path = 0 , cur_path = 0;
  while( now ) {
    //debug( "now %d\n" , now );

    REP( d , -MAXD , MAXD ) {
      long long inv_cnt =  ( cnt[ now ][ -( cur_path + d ) ] - cnt[ prv ][ -( cur_path + d ) - ( cur_path-prv_path ) ] );
      res += cnt[ u ][ d ] * inv_cnt;
    }

    prv_path = cur_path;
    if( upded[ now ] ) cur_path--; // now -> p small
    else cur_path++; // now -> p large
    prv = now;
    now = mom[ now ];

  }
  return res;
}

void solve() {
  REP( i , 1 , n ) {
    printf( "cnt %d\n" , i );
    REP( j , -4 , 4 ) printf( "  %d %d\n" , j , cnt[ i ][ j ] );
  }
  ll ans = 0;
  REP( i , 1 , n-1 ) {
    upd( es[ i ].u );
    ll tcnt = qry( es[ i ].u );
    debug( "tcnt %d %lld\n" , es[ i ].u , tcnt );
    ans += (long long)tcnt * es[ i ].c;
  }
  double ac = ans;
  printf( "%.9f\n" , ac );
}

int main(){
  FILE( "hidden" );
  input();
  predo();
  solve();
}
