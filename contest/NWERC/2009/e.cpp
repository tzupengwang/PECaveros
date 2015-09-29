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

typedef pair< ll , ll > pll;

const int MAXN = 210;
const int INF  = 1000000000;

struct XD
{int t , d;};

int n , m;
vector< XD > tp[ 2 ];
int dp[ 2 ][ MAXN ][ MAXN ];

int main()
{
  int tc;scanf("%d",&tc);while(tc--)
  {
    //puts( "::::::::::::::::::::::::::::::::::::::::::::::" );
    scanf( "%d" , &n );
    tp[ 0 ].clear();
    tp[ 1 ].clear();
    tp[ 0 ].push_back( { -INF , -INF } );
    tp[ 1 ].push_back( { -INF , -INF } );
    REP( i , 1 , n )
    {
      char typ[ 2 ];int t , d;
      scanf( "%s%d%d" , typ , &t , &d );
      tp[ *typ - 'A' ].push_back( { t , d } );
    }
    n = SZ( tp[ 0 ] ) - 1 , m = SZ( tp[ 1 ] ) - 1;
    
    REP( i , 0 , n ) REP( j , 0 , m ) REP( t , 0 , 1 )
      dp[ t ][ i ][ j ] = INF;

    dp[ 0 ][ 0 ][ 0 ] = dp[ 1 ][ 0 ][ 0 ] = 0;
    REP( i , 0 , n ) REP( j , 0 , m )
    {
      //printf( "dp 1 %d %d %d\n" , i , j , dp[ 1 ][ i ][ j ] );
      int ts = dp[ 1 ][ i ][ j ] - 10;
      int te = -INF;
      REP( k , 1 , n - i )
      {
        ts = max( ts + 10 , tp[ 0 ][ i+k ].t );
        te = max( te + 10 , ts + tp[ 0 ][ i+k ].d );
        //printf( "te %d\n" , te );
        dp[ 0 ][ i+k ][ j ] = min( dp[ 0 ][ i+k ][ j ] , te );
      }
      //printf( "dp 0 %d %d %d\n" , i , j , dp[ 0 ][ i ][ j ] );
      ts = dp[ 0 ][ i ][ j ] - 10;
      te = -INF;
      REP( k , 1 , m - j )
      {
        ts = max( ts + 10 , tp[ 1 ][ j+k ].t );
        te = max( te + 10 , ts + tp[ 1 ][ j+k ].d );
        //printf( "te %d\n" , te );
        dp[ 1 ][ i ][ j+k ] = min( dp[ 1 ][ i ][ j+k ] , te );
      }
    }

    //printf( "%d\n" , dfs( 0 , 1 , 1 ) );
    //printf( "%d\n" , dfs( 1 , 1 , 1 ) );
    //printf( "%d\n" , dfs( 0 , 3 , 1 ) );
    //printf( "%d %d\n" , ans1 , ans2 );
    printf( "%d\n" , min( dp[ 0 ][ n ][ m ] , dp[ 1 ][ n ][ m ] ) );

  }
}
