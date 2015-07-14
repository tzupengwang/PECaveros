
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

const int MAXN = 70;

int n;
ll k;

ll dp[ MAXN ];

inline int bit( ull x , int i )
{
  if( x & ( 1ll << i ) ) return 1;
  return 0;
}

bool check( ull msk , int l )
{
  REP( i , 1 , l - 1 )
  {
    bool fl = 1;
    REP( j , 0 , i - 1 )
      if( bit( msk , j ) != bit( msk , l - i + 1 + j ) )
        fl = 0;
    if( fl ) return 0;
  }
  return 1;
}

void print( ull msk , int l )
{
  REP( i , 0 , l - 1 ) printf( "%d" , bit( msk , i ) );
  puts( "" );
}

ll go( int nl , ull msk )
{
  //printf( "  go %d %llu\n" , nl , msk );
  //printf( "    " );print( msk , nl );
  REP( i , 1 , n )
  {
    dp[ i ] = 1ll << max( 0 , i - nl );
    for( int j = 1 ; j * 2 <= i ; j++ )
    {
      ll tmp = dp[ j ];
      int l = 1 , r = i - j + 1;
      while( l <= nl && r <= nl && l <= j && r <= i )
      {
        if( bit( msk , l - 1 ) != bit( msk , r - 1 ) )
        {
          tmp = 0ll;
          break ;
        }
        l++ , r++;
      }
      int unkn = max( 0 , i - j - nl ) - max( 0 , j - nl );
      dp[ i ] -= tmp * ( 1ll << unkn );
    }
  }
  //printf( "  res %lld\n" , dp[ n ] );
  return dp[ n ];
}

int main()
{
  FILE( "borderless" );
  while( cin >> n >> k )
  {
    if( n == 0 && k == 0 ) break ;
    string ans;
    ull msk = 0ll;
    REP( i , 1 , n )
    {
      ll cnt = go( i , msk );
      if( cnt < k )
      {
        msk |= ( 1ll << ( i - 1 ) );
        k -= cnt;
        ans.push_back( 'b' );
      }
      else ans.push_back( 'a' );
    }
    cout << ans << endl;
  }
}
