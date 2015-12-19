// default code for competitive programming
// c2251393 ver 3.141 {{{

// Includes
#include <bits/stdc++.h>

// Defines
#define NAME(x) #x
#define SZ(c) (int)(c).size()
#define ALL(c) (c).begin(), (c).end()
#define FOR(it, c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); it++)
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

// }}}
// start ~~QAQ~~

const int MAXN = 100010;

int n , m;
int deg[ MAXN ];
int dep[ MAXN ];
vector< int > g[ MAXN ];
bool vis[ MAXN ];
int cap[ MAXN ];
priority_queue< pii > shit;

int dfs( int u )
{
  if( vis[ u ] ) return dep[ u ];
  vis[ u ] = 1;
  dep[ u ] = 0;
  for( int v : g[ u ] )
    dep[ u ] = max( dep[ u ] , 1 + dfs( v ) );
  return dep[ u ];
}

inline void relax( int u )
{
  for( int v : g[ u ] )
    if( --deg[ v ] == 0 ) shit.push( pii( dep[v]*2+cap[v] , v ) );
}

int main()
{
  FILE( "documents" );
  scanf( "%d%d" , &n , &m );
  REP( i , 1 , m )
  {
    int u , v;
    scanf( "%d%d" , &u , &v );
    g[ u ].push_back( v );
    deg[ v ]++;
  }
  REP( i , 1 , n )
    if( deg[ i ] == 0 ) dfs( i );
  REP( i , 1 , n ) cap[ i ] = 2;
  REP( i , 1 , n )
    if( deg[ i ] == 0 )
      shit.push( pii( dep[ i ]*2+cap[ i ] , i ) );
  int tot = 0;
  while( SZ( shit ) )
  {
    tot++;
    int p = shit.top().second;shit.pop();
    if( SZ( shit ) )
    {
      int q = shit.top().second;shit.pop();
      if( --cap[ p ] == 0 ) relax( p );
      else shit.push( pii( dep[p]*2+cap[p] , p ) );
      if( --cap[ q ] == 0 ) relax( q );
      else shit.push( pii( dep[q]*2+cap[q] , q ) );
    }
    else
    {
      if( --cap[ p ] == 0 ) relax( p );
      else shit.push( pii( dep[p]*2+cap[p] , p ) );
    }
  }
  double ans = tot / 2.0;
  printf( "%.1f\n" , ans );
}
