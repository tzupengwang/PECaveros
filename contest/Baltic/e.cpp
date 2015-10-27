// default code for competitive programming
// c2251393 ver 3.141 {{{

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
  scanf( "%d" , &x );
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

const int MAXN = 100010;

struct SGT
{
  struct Node
  {
    ll sum;
    int lc , rc;
  };
  int tot , root[ MAXN ];
  Node nod[ MAXN * 20 ];
  int init( int l , int r )
  {
    int res = ++tot;
    nod[ res ] = { 0 , 0 , 0 };
    if( l == r ) return res;
    int mid = ( l + r ) / 2;
    nod[ res ].lc = init( l , mid );
    nod[ res ].rc = init( mid+1 , r );
    return res;
  }
  int upd( int tr , int l , int r , int x )
  {
    int res = ++tot;
    nod[ res ] = nod[ tr ];
    nod[ res ].sum++;
    if( l == r ) return res;
    int mid = ( l + r ) / 2;
    if( x <= mid ) nod[ res ].lc = upd( nod[ tr ].lc , l , mid , x );
    else nod[ res ].rc = upd( nod[ tr ].rc , mid+1 , r , x );
    return res;
  }
  ll qry( int tr , int l , int r , int a , int b )
  {
    if( b < l || r < a ) return 0ll;
    if( a <= l && r <= b ) return nod[ tr ].sum;
    int mid = ( l + r ) / 2;
    ll r1 = qry( nod[ tr ].lc , l , mid , a , b );
    ll r2 = qry( nod[ tr ].rc , mid+1 , r , a , b );
    return r1 + r2;
  }
} seg;

int n , p[ MAXN ];

int main()
{
  RI( n );
  REP( i , 1 , n ) RI( p[ i ] );
  seg.init( 1 , n );
  REP( i , 1 , n )
    seg.root[ i ] = seg.upd( seg.root[ i-1 ] , 1 , n , p[ i ] );
  ll ans = 0ll;
  REP( i , 1 , n )
  {
    int l = i , r = p[ i ];
    if( l > r ) swap( l , r );
    //cout << l << ' ' << r << endl;
    ll r1 = seg.qry( seg.root[ r-1 ] , 1 , n , r+1 , n ) - seg.qry( seg.root[ l ] , 1 , n , r+1 , n );
    ll r2 = seg.qry( seg.root[ r-1 ] , 1 , n , 1 , l-1 ) - seg.qry( seg.root[ l ] , 1 , n , 1 , l-1 );
    //cout << r1 + r2 << endl;
    ans += r1 + r2;
    ll r3 = seg.qry( seg.root[ n ] , 1 , n , l+1 , r-1 ) - seg.qry( seg.root[ r ] , 1 , n , l+1 , r-1 );
    ll r4 = seg.qry( seg.root[ l-1 ] , 1 , n , l+1 , r-1 ) - seg.qry( seg.root[ 0 ] , 1 , n , l+1 , r-1 );
    ans += r3 + r4;
    //cout << r3 + r4 << endl;
  }
  ans /= 2;
  cout << ans << endl;
}
