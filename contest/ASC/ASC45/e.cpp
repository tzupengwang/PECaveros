
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

const int MAXN = 5010;
const int INF  = 1e9;

int n , a , b , c , m;
int bt[ MAXN ];
int w[ MAXN ][ MAXN ];
int dp[ MAXN ][ MAXN ];
int prv[ MAXN ][ MAXN ];

void main2() {
  R( n );
  if( !n ) exit( 0 );
  R( a , b , c , m );
  FOR( i , n ) FOR( j , n ) {
    w[ i ][ j ] = ( a*i+b*j+c*(i^j) ) % m;
  }
  FOR( j , n ) dp[ 0 ][ j ] = 0;
  REP( i , 1 , n-1 ) FOR( j , n ) {
    dp[ i ][ j ] = INF;
    int psz = i&(-i);
    int oft = ( ( j^psz ) >> bt[ psz ] ) << bt[ psz ];
    FOR( k , psz ) {
      int p = k+oft;
      if( dp[ i-1 ][ p ] + w[ p ][ j ] < dp[ i ][ j ] ) {
        dp[ i ][ j ] = dp[ i-1 ][ p ] + w[ p ][ j ];
        prv[ i ][ j ] = p;
      }
    }
  }
  int mx = 0;
  FOR( j , n ) if( dp[ n-1 ][ j ] < dp[ n-1 ][ mx ] ) {
    mx = j;
  }
  int now = mx;
  vector<int> ans;
  FOR( j , n ) {
    ans.push_back( now );
    now = prv[ n-1-j ][ now ];
  }
  reverse( ALL( ans ) );
  printf( "%d\n" , dp[ n-1 ][ mx ] );
  out( ALL( ans ) , [&](int x){printf("%d",x);} );
}

int main()
{
  FOR( i , 13 ) bt[ 1<<i ] = i;
  FILE( "elegant" );
  while( 1 ) {
    main2();
  }
}
