
// default code for competitive programming
// ver 3.141 {{{

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

void RI() {}

template< typename... T >
void RI( int& x , T&... tail )
{
  assert( scanf( "%d" , &x ) == 1 );
  RI( tail... );
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

const int MAXN = 500010;
const int MAXV = 1000010;

struct BIT
{
  int sz;
  ll *dat;
  void init( int _sz )
  {
    sz = _sz;
    dat = new ll[ sz + 1 ];
  }
  void upd( int id , ll x )
  {
    for( int i = id ; i <= sz ; i += i&-i )
      dat[ i ] += x;
  }
  ll qry( int id )
  {
    ll res = 0ll;
    for( int i = id ; i > 0 ; i -= i & -i )
      res += dat[ i ];
    return res;
  }
} bit;

int n , m;
int mx;
int a[ MAXN ];
ll f[ MAXN ];
set< int > st[ MAXV ];

inline void ins( int id , int x )
{
  for( int i = id ; i <= mx+10 ; i += i&-i )
    st[ i ].insert( x );
}

inline void del( int id , int x )
{
  for( int i = id ; i <= mx+10 ; i += i&-i )
    st[ i ].erase( x );
}

inline ll qry( int id , int x )
{
  static int buf[ MAXN ];
  ll res = 0ll;
  int cnt = 0;
  for( int i = id ; i > 0 ; i -= i&-i )
  {
    auto it = st[ i ].lower_bound( x );
    while( it != st[ i ].end() )
    {
      res += f[ *it ];
      buf[ cnt++ ] = *it;
      it++;
    }
  }
  FOR( j , cnt ) del( a[ buf[ j ] ] , buf[ j ] );//st[ i ].erase( buf[ j ] );
  return res;
}

vector< int > R;
inline int id( int x ) { return lower_bound( ALL( R ) , x ) - R.begin() + 1; }

int main()
{
  RI( n , m );
  bit.init( MAXV );
  REP( i , 1 , n ) RI( a[ i ] );
  R = vector< int >( a+1 , a+1+n );
  sort( ALL( R ) );
  R.resize( unique( ALL( R ) ) - R.begin() );
  mx = SZ( R );
  REP( i , 1 , n ) a[ i ] = id( a[ i ] );
  ll ans = 0ll;
  REPD( i , n , 1 )
  {
    f[ i ] = bit.qry( a[ i ] - 1 );
    ans += f[ i ];
    bit.upd( a[ i ] , 1 );
    ins( a[ i ] , i );
  }
  printf( "%" PRId64 "\n" , ans );
  REP( i , 1 , m )
  {
    int p;RI( p );
    ans -= qry( a[ p ] , p );
    printf( "%" PRId64 "\n" , ans );
  }
}

[close]
