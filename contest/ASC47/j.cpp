
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

const int MAXN = 2010;

int h , w;
char in[ MAXN ][ MAXN ];

int lgo[ MAXN ][ MAXN ] , ugo[ MAXN ][ MAXN ];
int dp[ MAXN ][ MAXN ];
bool exi[ MAXN ][ MAXN ];

inline int calc()
{
  //printf( "h %d w %d\n" , h , w );
  //REP( i , 1 , h ) printf( "%s\n" , in[ i ] + 1 );
  REP( i , 1 , h ) REP( j , 1 , w )
    exi[ i ][ j ] = ( in[ i ][ j ] == '#' ) || exi[ i - 1 ][ j ] || exi[ i ][ j - 1 ];
  REP( i , 1 , h )
    REP( j , 1 , w ) if( in[ i ][ j ] == '#' )
    {
      if( in[ i ][ j - 1 ] == '#' )
        lgo[ i ][ j ] = lgo[ i ][ j - 1 ];
      else lgo[ i ][ j ] = j;
      if( in[ i - 1 ][ j ] == '#' )
        ugo[ i ][ j ] = ugo[ i - 1 ][ j ];
      else ugo[ i ][ j ] = i;
    }
  REP( i , 1 , h ) REP( j , 1 , w )
  {
    if( in[ i ][ j ] == '.' )
    {
      dp[ i ][ j ] = 0;
      continue ;
    }
    if( !exi[ i - 1 ][ j - 1 ] )
    {
      dp[ i ][ j ] = 0;
      continue ;
    }
    dp[ i ][ j ] = 1 + dp[ ugo[ i ][ j ] ][ lgo[ i ][ j ] ];
  }
  int res = 0;
  REP( i , 1 , h ) REP( j , 1 , w ) res = max( res , dp[ i ][ j ] );
  return res;
}

inline void rotate()
{
  static char tmp[ MAXN ][ MAXN ];
  REP( i , 1 , h ) REP( j , 1 , w )
    tmp[ i ][ j ] = in[ i ][ j ];
  REP( i , 1 , h ) REP( j , 1 , w )
    in[ w - j + 1 ][ i ] = tmp[ i ][ j ];
  swap( h , w );
  REP( i , 1 , h ) in[ i ][ w + 1 ] = 0;
}

int main()
{
  FILE( "jinxiety" );
  while( scanf( "%d%d" , &h , &w ) != EOF )
  {
    if( h == 0 && w == 0 ) break ;
    REP( i , 1 , h ) scanf( "%s" , in[ i ] + 1 );
    int ans = calc();
    rotate();
    ans = max( ans , calc() );
    rotate();
    ans = max( ans , calc() );
    rotate();
    ans = max( ans , calc() );
    printf( "%d\n" , ans );
  }
}
