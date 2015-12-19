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

const int MAXN = 200010;

int n , in[ MAXN ] , pos[ MAXN ];
set< int > bst;
int ans[ MAXN ];

void fail(){cout<<"-1\n";exit(0);}

int main()
{
  FILE( "restore" );
  IOS;
  scanf( "%d" , &n );
  REP( i , 1 , n ) scanf( "%d" , in+i );
  REP( i , 1 , n ) pos[ in[ i ] ] = i;
  REP( i , 1 , n+n ) bst.insert( i );
  REP( i , 1 , n )
  {
    int p = pos[ i ];
    int p1 = p*2-1 , p2 = p*2;
    int use = *bst.begin();bst.erase( bst.begin() );
    int alt = (use&1)?use+1:use-1;
    if( ans[ p2 ] )
    {
      ans[ p1 ] = use;
      bst.erase( use );
      bst.erase( alt );
      ans[ alt ] = alt;
    }
    else
    {
      ans[ p2 ] = use;
      ans[ p1 ] = p1;
      bst.erase( use );
      bst.erase( p1 );
      bst.erase( alt );
      ans[ alt ] = alt;
    }
  }
  set< int > shit;
  int cntfix = 0;
  ans[ n+n+1 ] = MAXN;
  REP( i , 1 , n+n )
  {
    if( !ans[ i ] ) fail();
    if( ans[ i ] == i ) cntfix++;
    shit.insert( ans[ i ] );
  }
  if( SZ( shit ) != n+n ) fail();
  for( int i = 2 ; i <= n+n ; i += 2 )
  {
    if( !( ans[ i-1 ] > ans[ i ] && ans[ i ] < ans[ i+1 ] ) ) fail();
  }
  REP( i , 1 , n+n )
    printf( "%d%c" , ans[ i ] , " \n"[ i == n+n ] );
}
