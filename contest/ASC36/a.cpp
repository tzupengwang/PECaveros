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

const int MAXN = 500010;

int n;
int col[ MAXN ] , sok[ MAXN ];
vector< int > chs[ MAXN ];
int ans[ MAXN ];

vector< int > g[ MAXN ] , rg[ MAXN ] , vs;
bool vis[ MAXN ];
int cmp[ MAXN ] , cnt;

inline void addEdge( int u , int v )
{
  g[ u ].push_back( v );
  rg[ v ].push_back( u );
}

void dfs( int u )
{
  vis[ u ] = 1;
  for( int v : g[ u ] ) if( !vis[ v ] )
    dfs( v );
  vs.push_back( u );
}

void rdfs( int u , int mk )
{
  cmp[ u ] = mk;
  vis[ u ] = 1;
  for( int v : rg[ u ] ) if( !vis[ v ] )
    rdfs( v , mk );
}

void scc()
{
  REP( i , 1 , 4*n ) if( !vis[ i ] )
    dfs( i );
  fill( vis , vis + MAXN , 0 );
  reverse( ALL( vs ) );
  for( int u : vs ) if( !vis[ u ] )
    rdfs( u , ++cnt );
}

int main()
{
  FILE( "chip" );
  scanf( "%d" , &n );
  REP( i , 1 , n ) scanf( "%d" , col+i );
  REP( i , 1 , n*2 ) scanf( "%d" , sok+i );
  REP( i , 1 , n*2 ) chs[ sok[ i ] ].push_back( i );
  REP( i , 1 , n*2 )
  {
    int nxt = i == 2*n ? 1 : i+1;
    if( col[ sok[ i ] ] == col[ sok[ nxt ] ] )
    {
      // !i || !nxt
      addEdge( i , nxt + 2*n );
      addEdge( nxt , i + 2*n );
    }
  }
  REP( i , 1 , n )
  {
    int c1 = chs[ i ][ 0 ];
    int c2 = chs[ i ][ 1 ];
    // !c1 || !c2
    addEdge( c1 , c2 + 2*n );
    addEdge( c2 , c1 + 2*n );
    // c1 || c2 : !c1 -> c2 and !c2 -> c1
    addEdge( c1 + 2*n , c2 );
    addEdge( c2 + 2*n , c1 );
  }

  scc();

  //REP( i , 1 , 4*n )
    //printf( "  %d %d\n" , i , cmp[ i ] );

  REP( i , 1 , 2*n )
    if( cmp[ i ] == cmp[ i + 2*n ] )
    {
      puts( "NO" );
      return 0;
    }

  puts( "YES" );
  REP( i , 1 , 2*n )
    if( cmp[ i ] > cmp[ i + 2*n ] )
      ans[ sok[ i ] ] = i;
  REP( i , 1 , n ) printf( "%d%c" , ans[ i ] , " \n"[ i == n ] );
}

