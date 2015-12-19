
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

const int MAXN = 3010;

struct Pt
{
  ll x , y;
  Pt operator-( const Pt& rhs ) const
  {return Pt{ x - rhs.x , y - rhs.y };}
  ll operator%( const Pt& rhs ) const
  { return x * rhs.y - y*rhs.x; }
  void print() const
  {printf( "( %lld , %lld )" , x , y );}
};
inline ll getll()
{
  ll x;
  cin >> x;
  return x;
  //return rand();
}
inline void outll( ll x )
{
  cout << x;
}

struct XD
{
  Pt p;int tp;
  double ang;
};

int n , m , t;
XD DT[ MAXN * 2 ] , pp[ MAXN * 2 ];
Pt F[ MAXN ];

ll sum0[ MAXN * 2 ];
ll sum1[ MAXN * 2 ];

inline ll cnt0( int i , int j )
{
  if( i > j ) return sum0[ n ] - sum0[ i - 1 ] + sum0[ j ];
  return sum0[ j ] - sum0[ i - 1 ];
}

inline ll cnt1( int i , int j )
{
  if( i > j ) return sum1[ n ] - sum1[ i - 1 ] + sum1[ j ];
  return sum1[ j ] - sum1[ i - 1 ];
}

inline ll calc( const Pt& O )
{
  //printf( "calc " );O.print();puts("");
  static auto nxt = [ & ]( int id ) {
    return ( id == n ) ? 1 : ( id + 1 );
  };
  static auto prv = [ & ]( int id ) {
    return ( id == 1 ) ? n : ( id - 1 );
  };
  REP( i , 1 , n ) pp[ i ] = XD{ DT[ i ].p - O , DT[ i ].tp , 0.0 };
  REP( i , 1 , n ) pp[ i ].ang = atan2( ( double ) pp[ i ].p.y , ( double ) pp[ i ].p.x );
  sort( pp + 1 , pp + 1 + n , [ & ]( XD a , XD b ) {
    return a.ang < b.ang;
  } );
  REP( i , 1 , n ) sum0[ i ] = sum0[ i - 1 ] + ( pp[ i ].tp == 0 );
  REP( i , 1 , n ) sum1[ i ] = sum1[ i - 1 ] + ( pp[ i ].tp == 1 );
  ll res = 0ll , acc = 0ll;
  int r = 1;
  REP( i , 1 , n )
  {
    r = nxt( r );
    while( r != i && pp[ i ].p % pp[ r ].p >= 0ll )
    {
      if( pp[ r ].tp == 1 )
        acc += cnt0( i , r );
      r = nxt( r );
    }
    r = prv( r );
    if( pp[ i ].tp == 1 ) res += acc;
    else acc -= cnt1( i , r );
    if( i == r ) r = i + 1;
  }
  return res;
}

int main()
{
  FILE( "ambitious" );
  srand( 514514 );
  //REP( _ , 1 , 5 )
  while( scanf( "%d" , &n ) != EOF )
  {
    //n = 10;
    if( n == 0 ) break ;
    REP( i , 1 , n )
      DT[ i ] = XD{ Pt{ getll() , abs( getll() ) } , 0 , 0.0 };
    scanf( "%d" , &m );
    //m = 10;
    REP( i , 1 , m )
      F[ i ] = Pt{ getll() , -abs( getll() ) };
    scanf( "%d" , &t );
    //t = 10;
    REP( i , 1 , t )
      DT[ i + n ] = XD{ Pt{ getll() , -abs( getll() ) } , 1 , 0.0 };
    n = n + t;
    ll ans = 0ll;
    REP( i , 1 , m )
      ans += calc( F[ i ] );
    outll( ans );puts( "" );
  }
}
