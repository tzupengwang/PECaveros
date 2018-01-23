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

typedef pair<int,int> pll;

const int MAXN = 2002;

const ll MOD1 = 1e9+7;
const ll MOD2 = 1e9+9;
const ll BASE = 131313;

int n1 , n2;
char ip1[ MAXN ] , ip2[ MAXN ];

pll pw[ MAXN ];
pll hsh1[ MAXN ] , hsh2[ MAXN ];

inline int add( int a , int b , int mod ){
  a += b;
  return a >= mod ? a - mod : a;
}
inline int sub( int a , int b , int mod ){
  a -= b;
  return a < 0 ? a + mod : a;
}
inline int mul( ll a , ll b , ll mod ){
  a *= b;
  return a >= mod ? a % mod : a;
}

inline pll operator*( const pll& a , const pll& b ) {
  return { mul( a.first , b.first , MOD1 ) , mul( a.second , b.second , MOD2 ) };
}
inline pll operator+( const pll& a , const pll& b ) {
  return { add( a.first , b.first , MOD1 ) , add( a.second , b.second , MOD2 ) };
}
inline pll operator-( const pll& a , const pll& b ) {
  return { sub( a.first , b.first , MOD1 ) , sub( a.second , b.second , MOD2 ) };
}


inline pll get_s( pll hsh[ MAXN ] , int l , int r ) {
  if( l > r ) return { 0 , 0 };
  return hsh[ r ] - hsh[ l-1 ] * pw[ r-l+1 ];
}

map<pll, int> subs1 , subs2;

int tid;
vector< vector<short> > vecs;
bool ok[ MAXN ][ MAXN ];
short cnt[ MAXN ][ MAXN ];
short len1[ MAXN ][ MAXN ];
short len2[ MAXN ][ MAXN ];
pll dp1[ MAXN ][ MAXN ];
pll hsh3[ MAXN ][ MAXN ];
pll dp2[ MAXN ][ MAXN ];

inline void predo() {
  pw[ 0 ] = { 1 , 1 };
  REP( i , 1 , 2001 ) {
    pw[ i ] = pw[ i-1 ] * pll{ BASE , BASE };
  }

  REP( i , 1 , n1 ) {
    hsh1[ i ] = pll{ ip1[ i ] , ip1[ i ] } + hsh1[ i-1 ] * pll{ BASE , BASE };
  }
  REP( i , 1 , n1 ) REP( j , i , n1 ) {
    pll h = get_s( hsh1 , i , j );
    if( subs1.count( h ) ) {
      vecs[ subs1[ h ] ].push_back( i );
    } else {
      vecs.push_back( vector<short>() );
      vecs[ subs1[ h ] = tid++ ].push_back( i );
    }
  }
  REPD( i , n1 , 1 ) REP( j , i , n1 ) {
    int len = j-i+1;
    pll h = get_s( hsh1 , i , j );
    vector<short> &pos = vecs[ subs1[ h ] ];
    int nxt_pos = n1+1;
    if( j < pos.back() ) {
      nxt_pos = *upper_bound( ALL( pos ) , j );
    }
    if( i == pos[ 0 ] ) ok[ i ][ j ] = 1;
    pll th = get_s( hsh1 , j+1 , nxt_pos-1 );
    if( nxt_pos <= n1 ) {
      int plen = len1[ nxt_pos ][ nxt_pos+len-1 ];
      len1[ i ][ j ] = nxt_pos-j-1 + plen;
      hsh3[ i ][ j ] = th*pw[ plen ] + hsh3[ nxt_pos ][ nxt_pos+len-1 ];
      dp1[ i ][ j ] = th*pll{BASE,BASE} + dp1[ nxt_pos ][ nxt_pos+len-1 ] * pw[ nxt_pos-j ];
      cnt[ i ][ j ] = 1 + cnt[ nxt_pos ][ nxt_pos+len-1 ];
    } else {
      len1[ i ][ j ] = n1-j;
      hsh3[ i ][ j ] = th;
      dp1[ i ][ j ] = th;
      cnt[ i ][ j ] = 1;
    }
  }


  REP( i , 1 , n2 ) {
    hsh2[ i ] = pll{ ip2[ i ] , ip2[ i ] } + hsh2[ i-1 ] * pll{ BASE , BASE };
  }
  REP( i , 1 , n2 ) REP( j , i , n2 ) {
    pll h = get_s( hsh2 , i , j );
    if( subs2.count( h ) ) {
      vecs[ subs2[ h ] ].push_back( i );
    } else {
      vecs.push_back( vector<short>() );
      vecs[ subs2[ h ] = tid++ ].push_back( i );
    }
  }
  REPD( i , n2 , 1 ) REP( j , i , n2 ) {
    int len = j-i+1;
    pll h = get_s( hsh2 , i , j );
    vector<short> &pos = vecs[ subs2[ h ] ];
    int nxt_pos = n2+1;
    if( j < pos.back() ) {
      nxt_pos = *upper_bound( ALL( pos ) , j );
    }
    pll th = get_s( hsh2 , j+1 , nxt_pos-1 );
    if( nxt_pos <= n2 ) {
      int plen = len2[ nxt_pos ][ nxt_pos+len-1 ];
      len2[ i ][ j ] = nxt_pos-j-1 + plen;
      dp2[ i ][ j ] = th*pll{BASE,BASE} + dp2[ nxt_pos ][ nxt_pos+len-1 ] * pw[ nxt_pos-j ];
    } else {
      len2[ i ][ j ] = n2-j;
      dp2[ i ][ j ] = th;
    }
  }
}

int main() {
  FILE( "curiosity" );
  fgets( ip1+1 , 2000 , stdin );
  fgets( ip2+1 , 2000 , stdin );
  n1 = strlen( ip1+1 );
  ip1[ n1 ] = 0;
  n1--;
  n2 = strlen( ip2+1 );
  ip2[ n2 ] = 0;
  n2--;
  predo();

  int ans = -1;
  int i1 = -1 , j1 = -1;
  int i2 = -1 , j2 = -1;
  REP( i , 1 , n1 ) REP( j , i , n1 ) {
    if( i > n2+1 ) continue;
    if( !ok[ i ][ j ] ) continue;
    int nn = cnt[ i ][ j ];
    int clen = j-i+1;
    int diff = n2-n1;
    if( diff % nn != 0 ) continue;
    int nlen = clen + diff/nn;
    if( i+nlen-1 > n2 ) continue;
    pll shit1 = get_s( hsh1 , 1 , i-1 );
    pll shit2 = get_s( hsh2 , 1 , i-1 );
    if( shit1 != shit2 ) continue;
    if( nlen == 0 ) {
      if( hsh3[ i ][ j ] != get_s( hsh2 , i , n2 ) ) continue;
    } else {
      if( dp1[ i ][ j ] != dp2[ i ][ i+nlen-1 ] ) continue;
    }
    if( ans == -1 || clen+nlen < ans ) {
      ans = clen+nlen;
      i1 = i , j1 = j;
      i2 = i , j2 = i+nlen-1;
    }
  }
  ip1[ j1+1 ] = 0;
  ip2[ j2+1 ] = 0;
  printf( "s/%s/%s/g\n" , ip1+i1 , ip2+i2 );
}
