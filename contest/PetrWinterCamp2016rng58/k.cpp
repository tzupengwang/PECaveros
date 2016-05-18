
// default code for competitive programming
// ver 3.1415 {{{

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
#define PB push_back
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

int _R( int& x ) { return scanf( "%d" , &x ); }
int _R( ll& x ) { return scanf( "%" PRId64 , &x ); }
int _R( double& x ) { return scanf( "%lf" , &x ); }
int _R( char* s ) { return scanf( "%s" , s ); }

int R() { return 0; }

template< typename T1 , typename... T2 >
int R( T1& x , T2&... tail )
{
  int tmp = _R( x );
  return tmp + R( tail... );
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

typedef complex<ll> Zi;

Zi operator%( Zi a , Zi b ) {
  Zi q = a/b;
  Zi res = a - b*q;
  REP( i , -1 , 1 ) REP( j , -1 , 1 ) {
    Zi tr = a - b*( q+Zi(i,j) );
    if( norm( tr ) < norm( res ) ) res = tr;
  }
  return res;
}

Zi gcd( Zi a , Zi b ) {
  if( norm( a ) <= norm( b ) ) swap( a , b );
  if( b == Zi{0,0} ) return a;
  return gcd( b , a%b );
}

const int MAXN = 1e5+10;

int n;
Zi in[ MAXN ];

int main()
{
  R( n );
  REP( i , 1 , n ) {
    ll x,y;R(x,y);
    in[ i ] = { x , y };
  }

  REP( i , 2 , n ) in[ i ] -= in[ 1 ];
  in[ 1 ] = { 0 , 0 };

  Zi g = in[ 1 ];
  REP( i , 2 , n ) g = gcd( g , in[ i ] );

  ll min_x , max_x , min_y , max_y;
  min_x = max_x = min_y = max_y = 0;

  REP( i , 2 , n ) {
    Zi tmp = in[ i ] / g;
    min_x = min( min_x , tmp.real() );
    max_x = max( max_x , tmp.real() );
    min_y = min( min_y , tmp.imag() );
    max_y = max( max_y , tmp.imag() );
  }

  ll len = max( max_x-min_x+1 , max_y-min_y+1 );

  ll tot = len*len;

  //cout << g.real() << " " << g.imag() << endl;

  //cout << tot << endl;

  cout << tot-n << endl;


}
