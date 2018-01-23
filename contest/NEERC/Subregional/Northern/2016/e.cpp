#pragma GCC optimize("O3")
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
const double EPS = 1e-8;
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

const ll A   = 13131;
const ll B   = 31313;
const ll iA  = 147437363;
const ll iB  = 982275739;
const ll MOD = 1000000007;
//const ll A   = 2;
//const ll B   = 3;
//const ll iA  = 500000004;
//const ll iB  = ( MOD+1 ) / 3;

const int MAXN = 1e5+10;

inline ll mul( ll a , ll b ){
  a *= b;
  return a >= MOD ? a % MOD : a;
}
inline ll add( ll a , ll b ){
  a += b;
  return a >= MOD ? a - MOD : a;
}
inline ll sub( ll a , ll b ){
  a -= b;
  return a < 0 ? a + MOD : a;
}

ll pwA[ MAXN ] , pwB[ MAXN ];
int l , n , m;
char ip[ MAXN ];
vector<string> pic;

int totX;
ll TARGET;

void predo() {
  pwA[ 0 ] = pwB[ 0 ] = 1;
  FOR( i , MAXN-1 ) {
    pwA[ i+1 ] = mul( A , pwA[ i ] );
    pwB[ i+1 ] = mul( B , pwB[ i ] );
  }
  int mnx = MAXN , mny = MAXN;
  FOR( i , n ) FOR( j , m )
    if( pic[ i ][ j ] == 'X' ) {
      totX++;
      mnx = min( mnx , i );
      mny = min( mny , j );
    }
  REP( i , mnx , n-1 ) {
    REP( j , mny , m-1 ) {
      if( pic[ i ][ j ] == 'X' ) {
        //cout << "  TARGET has " << i-mnx << ' ' << j-mny << endl;
        TARGET = add( TARGET , mul( pwA[ i-mnx ] , pwB[ j-mny ] ) );
      }
    }
  }
  //cout << "  TARGET " << TARGET << endl;
}

ll curHash;
int mnx , mny;
int sz;
multiset<pii> xs , ys;

inline void ins( int x , int y ) {
  //cout << "  ins " << x << ' ' << y << endl;
  if( x < mnx ) {
    curHash = mul( curHash , A );
    mnx = x;
  }
  if( y < mny ) {
    curHash = mul( curHash , B );
    mny = y;
  }
  int i = x-mnx;
  int j = y-mny;
  if( !xs.count( { x , y } ) ) {
    sz++;
    //cout << "  ins " << x << ' ' << y << " -> " << i << ' ' << j << endl;
    curHash = add( curHash , mul( pwA[ i ] , pwB[ j ] ) );
  }
  xs.insert( { x , y } );
  ys.insert( { y , x } );
}

inline void del( int x , int y ) {

  //cout << "  del " << x << ' ' << y << endl;
  //cout << "HAHA" << endl;
  xs.erase( xs.find( { x , y } ) );
  ys.erase( ys.find( { y , x } ) );
  //cout << "HAHA" << endl;

  int i = x-mnx;
  int j = y-mny;

  if( !xs.count( { x , y } ) ) {
    //cout << "  del " << i << ' ' << j << endl;
    sz--;
    curHash = sub( curHash , mul( pwA[ i ] , pwB[ j ] ) );
  }
  
  int tmnx = xs.begin()->first;
  int tmny = ys.begin()->first;

  if( tmnx > mnx ) {
    curHash = mul( curHash , iA );
  }
  if( tmny > mny ) {
    curHash = mul( curHash , iB );
  }

  mnx = tmnx;
  mny = tmny;
}

inline bool cmd( char c ) {
  return c == 'u' || c == 'd' || c == 'l' || c == 'r';
}

inline pii nxt( pii p , char c ) {
  pii res = p;
  if( c == 'u' ) {
    res.first --;
  } else if( c == 'd' ) {
    res.first ++;
  } else if( c == 'l' ) {
    res.second --;
  } else if( c == 'r' ) {
    res.second ++;
  }
  return res;
}

pii pos[ MAXN ];

void solve() {

  pii np{ 0 , 0 };
  FOR( i , l ) {
    if( cmd( ip[ i ] ) )
      np = nxt( np , ip[ i ] );
    pos[ i ] = np;
  }


  mnx = mny = 0;
  curHash = 0;
  ins( 0 , 0 );

  int j = 0;
  FOR( i , l ) {
    //cout << "{i " << i << endl;
    while( j < l && sz < totX ) {
      if( cmd( ip[ j ] ) ) {
        ins( pos[ j ].first , pos[ j ].second );
      }
      j++;
    }
    //cout << " j " << j << " hash " << curHash  <<  " }" << endl;
    if( curHash == TARGET ) {
      printf( "YES\n%d %d\n" , i+1 , j );
      exit( 0 );
    }
    if( cmd( ip[ i ] ) ) {
      if( i > 0 )
        del( pos[ i-1 ].first , pos[ i-1 ].second );
      else del( 0 , 0 );
    }
  }

}

int main() {
  static char buf[ MAXN ];
  FILE( "easy" );
  //IOS;
  //cin.tie( 0 );
  scanf( "%d" , &l );
  fgets( ip , MAXN , stdin );
  fgets( ip , MAXN , stdin );
  scanf( "%d%d" , &n , &m );
  pic.resize( n );
  FOR( i , n ) {
    scanf( "%s" , buf );
    pic[ i ] = string( buf , buf+m );
  }

  //return 0 ;
  
  predo();
  //return 0 ;
  solve();

  puts( "NO" );
}
