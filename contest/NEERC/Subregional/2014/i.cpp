// default code for competitive programming
// ver 3.141 {{{

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

#ifdef AKAI
#define debug( ... ) fprintf( stderr , __VA_ARGS__ )
#else
#define debug( ... )
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

const int MAXN = 5010;

int n , a , b;

vector< pii > item[ 4 ];
vector< int > sum[ 4 ];

int dp[ MAXN ][ MAXN ];

int main()
{
  RI( n , a , b );
  REP( i , 1 , n )
  {
    int tp , w;
    RI( tp , w );
    item[ tp ].push_back( { w , i } );
  }
  REP( i , 1 , 3 ) item[ i ].push_back( { 0 , 0 } );
  REP( i , 1 , 3 ) sort( ALL( item[ i ] ) );
  REP( i , 1 , 3 )
  {
    sum[ i ].resize( SZ( item[ i ] ) );
    REP( j , 1 , SZ( item[ i ] ) - 1 )
      sum[ i ][ j ] = sum[ i ][ j-1 ] + item[ i ][ j ].first;
  }


  int usea = -1 , useb = -1 , mxcnt , mncst;
  REP( i , 0 , SZ( item[ 3 ] ) - 1 ) REP( j , 0 , i )
  {
    int na = j , nb = i-j;
    if( na > a || nb > b ) continue ;

    int use1 = min( SZ( item[ 1 ] )-1 , a-na );
    int use2 = min( SZ( item[ 2 ] )-1 , b-nb );

    int tcnt = use1 + use2 + i;
    int tcst = sum[ 1 ][ use1 ] + sum[ 2 ][ use2 ] + sum[ 3 ][ i ];
    //printf( "tcnt %d tcst %d\n" , tcnt , tcst );
    if( usea == -1 || ( tii( -tcnt , tcst ) < tii( -mxcnt , mncst ) ) )
    {
      usea = na , useb = nb;
      mxcnt = tcnt;
      mncst = tcst;
    }
  }
  printf( "%d %d\n" , mxcnt , mncst );

  int na = usea , nb = useb;

  int use1 = min( SZ( item[ 1 ] )-1 , a-na );
  int use2 = min( SZ( item[ 2 ] )-1 , b-nb );

  vector< pii > ans;
  int nowa = 0 , nowb = a;
  REP( i , 1 , na ) ans.push_back( { item[ 3 ][ i ].second , ++nowa } );
  REP( i , 1 , use1 ) ans.push_back( { item[ 1 ][ i ].second , ++nowa } );

  REP( i , na+1 , na+nb ) ans.push_back( { item[ 3 ][ i ].second , ++nowb } );
  REP( i , 1 , use2 ) ans.push_back( { item[ 2 ][ i ].second , ++nowb } );

  for( pii p : ans )
    printf( "%d %d\n" , p.first , p.second );

}
