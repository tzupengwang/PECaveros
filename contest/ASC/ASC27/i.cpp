
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

const int MAXN = 3e5+10;
const ll  BASE = 1313131313ll;
const ll  MOD  = 1e9+7;
const ll  MOD2 = 1e9+9;

typedef pair<ll,ll> pll;

inline pll add( pll a , pll b ) {
  return {(a.first+b.first)%MOD,(a.second+b.second)%MOD2};
}
inline pll mul( pll a , pll b ) {
  return {(a.first*b.first)%MOD,(a.second*b.second)%MOD2};
}
pll pw[ MAXN ];

int n , t , col;
ll in[ MAXN ];
int mxid[ MAXN<<2 ];
pll hsh[ MAXN<<2 ];
set<pll> cfgs;

inline void pull( int id , int l , int r ) {
  int mid = ( l + r ) / 2;
  if( in[ mxid[ id*2 ] ] >= in[ mxid[ id*2+1 ] ] )
    mxid[ id ] = mxid[ id*2 ];
  else
    mxid[ id ] = mxid[ id*2+1 ];

  hsh[ id ] = add( hsh[ id*2+1 ] , mul( hsh[ id*2 ] , pw[ mid-l+1 ] ) );
}

void init( int id , int l , int r ) {
  if( l == r ) {
    mxid[ id ] = l;
    hsh[ id ] = { in[ l ]%MOD , in[ l ]%MOD2 };
    return ;
  }
  int mid = ( l + r ) / 2;
  init( id*2 , l , mid );
  init( id*2+1 , mid+1 , r );
  pull( id , l , r );
}

void upd( int id , int l , int r , int pos , ll x ) {
  if( l == r ) {
    in[ pos ] = x;
    hsh[ id ] = { x%MOD , x%MOD2 };
    return ;
  }
  int mid = ( l + r ) / 2;
  if( pos <= mid )
    upd( id*2 , l , mid , pos , x );
  else
    upd( id*2+1 , mid+1 , r , pos , x );
  pull( id , l , r );
}

int main()
{
  FILE( "segments" );
  pw[ 0 ] = { 1 , 1 };
  FOR( i , MAXN-1 ) pw[ i+1 ] = mul( { BASE , BASE } , pw[ i ] );

  char tp[ 11 ];
  R( n , t , tp );
  col = tp[ 0 ] == 'w';
  REP( i , 100004 , 100004+n-1 ) R( in[ i ] );
  init( 1 , 0 , 3e5+5 );
  cfgs.insert( hsh[ 1 ] );
  int ans = 0;
  for( ans = 1 ; ans < t ; ans++ ) {
    int id = mxid[ 1 ];

    int tcol = (id&1)^col;
    ll len = in[ id ];
    if( tcol == 1 ) { // white
      upd( 1 , 0 , 3e5+5 , id , (len+1)/2 );
      upd( 1 , 0 , 3e5+5 , id+1 , in[ id+1 ]+len/2 );
    } else {
      upd( 1 , 0 , 3e5+5 , id , (len+1)/2 );
      upd( 1 , 0 , 3e5+5 , id-1 , in[ id-1 ]+len/2 );
    }

    //REP( i , 100004 , 100004+n-1 ) printf( "%lld " , in[ i ] );
    //puts( "" );

    if( cfgs.count( hsh[ 1 ] ) ) break ;
    if( in[ mxid[ 1 ] ] == 1 ) break ;
    cfgs.insert( hsh[ 1 ] );
  }
  printf( "%d\n" , ans );
}
