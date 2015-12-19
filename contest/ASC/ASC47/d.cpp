
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
#ifdef ONLINE_JUDGE
#define FILE( fn ) \
    freopen(fn".in","r",stdin); \
    freopen(fn".out","w",stdout);
#else
#define FILE( fn )
#endif 

const int MAXN = 55;

int n;
char in[ MAXN ];

void go( int pos )
{
  static int delta[ MAXN ][ 33 ];
  //printf( "go %d\n" , pos );
  int sz = n + 2 - 1;
  int s = 1 , t = sz - 1;
  REP( i , 1 , sz ) REP( j , 1 , 26 )
    delta[ i ][ j ] = sz;
  int now = 1;
  REP( i , 1 , n )
  {
    int c = in[ i ] - 'a' + 1;
    if( i == pos )
    {
      delta[ now ][ c ] = now;
    }
    else
    {
      delta[ now ][ c ] = now + 1;
      now++;
    }
  }
  printf( "%d\n%d\n%d\n" , sz , s , t );
  REP( i , 1 , sz )
    REP( j , 1 , 26 ) printf( "%d%c" , delta[ i ][ j ] , " \n"[ j == 26 ] );
}

int main()
{
  FILE( "decomposable" );
  while( scanf( "%s" , in + 1 ) != EOF )
  {
    n = strlen( in + 1 );
    int p1 = 1 , p2 = 1;
    REP( i , 1 , n ) if( in[ i ] != in[ 1 ] )
    {
      for( p2 = i ; in[ i ] == in[ p2 ] && p2 <= n ; p2++ );
      p2--;
      break ;
    }
    else p1 = i;
    if( in[ p2 ] == in[ p1 ] )
    {
      puts( "NO" );
      continue ;
    }
    puts( "YES" );
    go( p1 );
    go( p2 );
  }
}
