
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

const int MAXN = 1e6+10;

int n , m;
char txt[ MAXN ] , pat[ MAXN ];
int q , ip[ MAXN ];
bool no[ MAXN ];

void build_fail_function(char *B , int len, int *fail) {
    int pos;
    pos = fail[0] = -1;
    for (int i = 1; i < len; i ++) {
        while (pos != -1 and B[pos + 1] != B[i])
            pos = fail[pos];
        if (B[pos + 1] == B[i]) pos ++;
        fail[i] = pos;
    }
}

int fail1[ MAXN ] , fail2[ MAXN ] , par_len[ MAXN ];
int mch_len[ MAXN ];
ll ans;

vector<int> ch2[ MAXN ];
int tL[ MAXN ] , tR[ MAXN ] , ts;

void dfs0( int u ) {
  tL[ u ] = ++ts;
  for( int v : ch2[ u ] ) dfs0( v );
  tR[ u ] = ts;
}

void predo() {
  build_fail_function( pat , m , fail1 );

  reverse( txt , txt+n );
  reverse( pat , pat+m );
  build_fail_function( pat , m , fail2 );
  int pos = -1;
  FOR( i , n ) {
    while( pos != -1 && pat[ pos+1 ] != txt[ i ] )
      pos = fail2[ pos ];
    if( pat[ pos+1 ] == txt[ i ] ) pos++;
    if( pos+1 == m ) {
      ans++;
      pos = fail2[ pos ];
    }
    mch_len[ i ] = pos+1;
  }

  reverse( pat , pat+m );
  reverse( txt , txt+n );
  reverse( mch_len , mch_len+n );

  FOR( i , m ) if( fail2[ i ] != -1 )
    ch2[ fail2[ i ] ].push_back( i );
  FOR( i , m ) if( fail2[ i ] == -1 )
    dfs0( i );
}

struct BIT {
  int sz;
  ll dat[ MAXN ];
  void init( int _sz ) { sz = _sz; }
  void upd( int id , ll x ) { for(int i=id;i<=sz;i+=i&-i)dat[i]+=x; }
  ll qry( int id ) { ll res=0;for(int i=id;i>0;i-=i&-i)res+=dat[i];return res; }
} bit;

vector<int> ch[ MAXN ] , qry[ MAXN ];

void dfs( int i ) {

  int need_l = m-(i+1);
  if( need_l == 0 ) return;

  bit.upd( tL[ need_l-1 ] , 1 );
  bit.upd( tR[ need_l-1 ]+1 , -1 );

  for( int j : ch[ i ] ) dfs( j );

  for( int rlen : qry[ i ] ) {
    ll tmp = bit.qry( tL[ rlen-1 ] );
    ans += tmp;
  }

  bit.upd( tL[ need_l-1 ] , -1 );
  bit.upd( tR[ need_l-1 ]+1 , +1 );
}

void solve() {
  FOR( i , m ) {
    if( fail1[ i ] != -1 )
      ch[ fail1[ i ] ].push_back( i );
  }
  int pos = -1;
  FOR( i , n ) {
    if( no[ i ] ) {
      if( pos != -1 && mch_len[ i+1 ] > 0 ) {
        //printf( "x @ %d: %d x %d\n" , i , pos+1 , mch_len[ i+1 ] );
        qry[ pos ].push_back( mch_len[ i+1 ] );
      }
    } else {
      while( pos != -1 && pat[ pos+1 ] != txt[ i ] )
        pos = fail1[ pos ];
      if( pat[ pos+1 ] == txt[ i ] ) pos++;
      if( pos+1 == m ) pos = fail1[ pos ];
    }
  }
  bit.init( m );
  FOR( i , m ) if( fail1[ i ] == -1 ) dfs( i );
  cout << ans << endl;
}

int main() {
  R( txt , pat , q );
  n = strlen( txt );
  m = strlen( pat );
  REP( i , 1 , q ) {
    R( ip[ i ] );
    ip[ i ]--;
    no[ ip[ i ] ] = 1;
  }

  predo();

  solve();

}
