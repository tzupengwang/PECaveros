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
  scanf( "%d" , &x );
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

const int MAXM = 400010;

int n1 , n2 , m , r;
int X[ MAXM ] , Y[ MAXM ];
int llast[ MAXM ] , rlast[ MAXM ];
ll lans[ MAXM ] , rans[ MAXM ];

inline ll f( int x , int k )
{
  ll sz = x / k;
  ll rst = x % k;
  ll s = ( sz * ( sz - 1 ) ) / 2;
  s *= k;
  return s + rst * sz;
}

int main()
{
  FILE( "lanes" );
  RI( n1 , n2 , m , r );
  REP( i , 1 , m ) RI( X[ i ] , Y[ i ] );

  m += r;

  {
    REP( i , 1 , m+r )
    {
      int tmp = min( X[ i ] , n1 + 1 );
      lans[ m+r ] += X[ i ] - tmp;
      X[ i+1 ] += X[ i ] - tmp;
      X[ i ] = tmp;
    }
    llast[ m+r ] = X[ m+r+1 ];

    vector< int > notfull{ m+r+1 };
    REPD( i , m+r , 1 )
    {
      lans[ i-1 ] = lans[ i ];
      if( X[ i ] == n1+1 )
      {
        X[ i ] = n1;
        int tid = notfull.back();
        lans[ i-1 ] += tid - i;
        X[ tid ]++;
        if( X[ tid ] >= n1 && tid <= m+r ) notfull.pop_back();
      }
      else if( X[ i ] < n1 )
        notfull.push_back( i );
      llast[ i-1 ] = X[ m+r+1 ];
    }

    REP( i , 0 , m+r )
      lans[ i ] += f( llast[ i ] , n1 );

    //REP( i , 0 , m+r )
      //cout << "lans " << i << " " << lans[ i ] << endl;
  }


  {
    REP( i , 1 , m+r )
    {
      int tmp = min( Y[ i ] , n2+1 );
      rans[ 0 ] += Y[ i ] - tmp;
      Y[ i+1 ] += Y[ i ] - tmp;
      Y[ i ] = tmp;
    }

    rlast[ 0 ] = Y[ m+r+1 ];

    vector< int > notfull{ m+r+1 };
    REPD( i , m+r , 1 )
      if( Y[ i ] < n2+1 )
        notfull.push_back( i );

    REP( i , 1 , m+r )
    {
      rans[ i ] = rans[ i-1 ];
      if( Y[ i ] == n2+1 )
      {
        Y[ i ] = n2;
        while( SZ( notfull ) && notfull.back() <= i )
          notfull.pop_back();
        int tid = notfull.back();
        rans[ i ] += tid - i;
        Y[ tid ]++;
        if( Y[ tid ] >= n2+1 && tid <= m+r ) notfull.pop_back();
      }
      rlast[ i ] = Y[ m+r+1 ];
    }

    REP( i , 0 , m+r )
      rans[ i ] += f( rlast[ i ] , n2+1 );

    //REP( i , 0 , m+r )
      //cout << "rans " << i << " " << rans[ i ] << endl;

  }

  ll mn = 100000000000000000ll;
  int id = -1;
  REP( i , 1 , m-r )
  {
    if( mn > lans[ i-1 ] + rans[ i+r-1 ] )
    {
      id = i;
      mn = lans[ i-1 ] + rans[ i+r-1 ];
    }
  }
  printf( "%d\n" , id );

}
