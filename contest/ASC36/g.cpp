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

struct XD
{int i , j , c;};

int n , in[ MAXN ];
vector< XD > ans;

int main()
{
  FILE( "magic" );
  scanf( "%d" , &n );
  REP( i , 1 , n ) scanf( "%d" , in + i );
  set< pii > bst;
  REP( i , 1 , n ) bst.insert( pii( i , in[ i ] ) );
  while( SZ( bst ) )
  {
    pii np = *bst.begin();bst.erase( bst.begin() );
    int now = np.first , lft = np.second;
    while( lft && SZ( bst ) )
    {
      pii tp = *bst.begin();bst.erase( bst.begin() );
      int tn = tp.first , tl = tp.second;
      int use = min( lft , tl );
      assert( use > 0 );
      ans.push_back( XD{ now , tn , use } );
      lft -= use , tl -= use;
      if( tl )
      {
        bst.insert( pii( tn , tl ) );
        assert( lft <= 0 );
      }
    }
    if( lft )
    {
      assert( SZ( bst ) == 0 );
      REPD( i , SZ( ans ) - 1 , 0 )
      {
        if( lft <= 0 ) break ;
        if( ans[ i ].i == now || ans[ i ].j == now )
          continue ;
        int use = min( lft/2 , ans[ i ].c );
        //assert( use > 0 );
        ans[ i ].c -= use;
        lft -= use*2;
        ans.push_back( XD{ ans[ i ].i , now , use } );
        ans.push_back( XD{ ans[ i ].j , now , use } );
        assert( ans[ i ].i < now );
        assert( ans[ i ].j < now );
      }
    }
  }
  map< pii , int > mp;
  for( XD xd : ans )
    if( xd.c )
      mp[ pii( xd.i , xd.j ) ] += xd.c;
  printf( "%d\n" , SZ( mp ) );
  for( auto xd : mp )
    printf( "%d %d %d\n" , xd.first.first , xd.first.second , xd.second );
}
