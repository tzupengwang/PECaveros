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

int n , m , K;
vector< int > g[ MAXN ];
int deg[ MAXN ];

int main()
{
  RI( n , m , K );
  REP( i , 1 , m )
  {
    int u , v ; RI( u , v );
    g[ u ].push_back( v );
    g[ v ].push_back( u );
    deg[ u ]++;
    deg[ v ]++;
  }
  set< pii > heap;
  REP( i , 1 , n )
    heap.insert( pii( deg[ i ] , i ) );
  vector< int > ans;
  while( SZ( heap ) )
  {
    pii p = *heap.rbegin();heap.erase( p );
    int u = p.second;
    ans.push_back( u );
    for( int v : g[ u ] )
    {
      heap.erase( pii( deg[ v ] , v ) );
      for( int w : g[ v ] )
        heap.erase( pii( deg[ w ] , w ) );
    }
  }
  printf( "%d\n" , SZ( ans ) );
  FOR( i , SZ( ans ) )
    printf( "%d%c" , ans[ i ] , " \n"[ i == SZ( ans ) - 1 ] );
  //out( ALL( ans ) , [&](int x){printf("%d",x);} );
}
