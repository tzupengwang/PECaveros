
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

namespace SPLX{
const int maxn = 5555;
const int maxm = 111;
const double eps = 1E-10;

double a[maxn][maxm], b[maxn], c[maxm], d[maxn][maxm];
double x[maxm];
int ix[maxn + maxm]; // !!! array all indexed from 0
// max{cx} subject to {Ax<=b,x>=0}
// n: constraints, m: vars !!!
// x[] is the optimal solution vector
//
// usage : 
// value = simplex(a, b, c, N, M);
double simplex(double a[maxn][maxm], double b[maxn], double c[maxm], int n, int m) {
    ++m;
    int r = n, s = m - 1;
    memset(d, 0, sizeof(d));
    for (int i = 0; i < n + m; ++i) ix[i] = i;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m - 1; ++j) d[i][j] = -a[i][j];
        d[i][m - 1] = 1;
        d[i][m] = b[i];
        if (d[r][m] > d[i][m]) r = i;
    }
    for (int j = 0; j < m - 1; ++j) d[n][j] = c[j];
    d[n + 1][m - 1] = -1;
    for (double dd;; ) {
        if (r < n) {
            int t = ix[s]; ix[s] = ix[r + m]; ix[r + m] = t;
            d[r][s] = 1.0 / d[r][s];
            for (int j = 0; j <= m; ++j) if (j != s) d[r][j] *= -d[r][s];
            for (int i = 0; i <= n + 1; ++i) if (i != r) {
                for (int j = 0; j <= m; ++j) if (j != s) d[i][j] += d[r][j] * d[i][s];
                d[i][s] *= d[r][s];
            }
        }
        r = -1; s = -1;
        for (int j = 0; j < m; ++j) if (s < 0 || ix[s] > ix[j]) {
            if (d[n + 1][j] > eps || (d[n + 1][j] > -eps && d[n][j] > eps)) s = j;
        }
        if (s < 0) break;
        for (int i = 0; i < n; ++i) if (d[i][s] < -eps) {
            if (r < 0 || (dd = d[r][m] / d[r][s] - d[i][m] / d[i][s]) < -eps || (dd < eps && ix[r + m] > ix[i + m])) r = i;
        }
        if (r < 0) return -1; // not bounded
    }
    if (d[n + 1][m] < -eps) return -1; // not executable
    double ans = 0;
    for(int i=0; i<m; i++) x[i] = 0;
    for (int i = m; i < n + m; ++i) { // the missing enumerated x[i] = 0
        if (ix[i] < m - 1)
        {
            ans += d[i - m][m] * c[ix[i]];
            x[ix[i]] = d[i-m][m];
        }
    }
    return ans; 
}
}

const int MAXN = 33;
const int MAXM = 110;
const int INF = 1e9+10;

struct Edge {
  int u , v , c;
} es[ MAXM ];

int n , m , r , q;
int g[ MAXN ][ MAXN ];

int dis[ MAXN ][ MAXN ] , prv[ MAXN ][ MAXN ];

inline void bellman( int s ) {
  fill( dis[ s ] , dis[ s ] + n , INF );
  fill( prv[ s ] , prv[ s ] + n , -1 );
  dis[ s ][ s ] = 0;
  FOR( _ , n ) FOR( i , m ) {
    int u = es[ i ].u;
    int v = es[ i ].v;
    int c = es[ i ].c;
    if( dis[ s ][ u ]+c < dis[ s ][ v ] ) {
      dis[ s ][ v ] = dis[ s ][ u ]+c;
      prv[ s ][ v ] = i;
    }
  }
}

vector<int> getpath( int s , int t ) {
  vector<int> res;
  if( dis[ s ][ t ] >= INF ) return res;
  for( int now = t ; now != s ; ) {
    int id = prv[ s ][ now ];
    now = es[ id ].u;
    res.push_back( id );
  }
  return res;
}

int n_var , n_con;

int main()
{
  R( n );
  FOR( i , n ) FOR( j , n ) {
    R( g[ i ][ j ] );
    if( g[ i ][ j ] > 0 )
      es[ m++ ] = { i , j , g[ i ][ j ] };
  }

  //FOR( i , m )
    //printf( "%d -- %d --> %d\n" , es[ i ].u , es[ i ].c , es[ i ].v );
  FOR( s , n ) bellman( s );

  n_var = m;

  R( r );

  n_con = m+m+r+r;

  FOR( i , m ) {
    SPLX::a[ i ][ i ] = 1;
    SPLX::b[ i ] = 2;
    SPLX::a[ i+m ][ i ] = -1;
    SPLX::b[ i+m ] = -1;
  }

  int oft = m+m;

  FOR( i , r ) {
    int s , t , w;R( s , t , w );
    vector<int> path = getpath( s , t );
    //printf( "path %d %d\n" , s , t );
    //out( ALL( path ) , [&](int x){printf("%d",x);} );
    for( int id : path ) {
      SPLX::a[ oft+i*2 ][ id ] = es[ id ].c;
      SPLX::a[ oft+i*2+1 ][ id ] = -es[ id ].c;
    }
    SPLX::b[ oft+i*2 ] = w;
    SPLX::b[ oft+i*2+1 ] = -w;
  }

  R( q );

  while( q-- ) {
    int s , t;R( s , t );

    vector<int> path = getpath( s , t );
    //printf( "path %d %d\n" , s , t );
    //out( ALL( path ) , [&](int x){printf("%d",x);} );

    fill( SPLX::c , SPLX::c + n_var , 0 );
    for( int id : path ) {
      SPLX::c[ id ] = es[ id ].c;
    }
    double mx = SPLX::simplex( SPLX::a , SPLX::b , SPLX::c , n_con , n_var );

    //printf( "mx %.9f\n" , mx );
    //FOR( i , m ) printf( "x %d %.9f\n" , i , SPLX::x[ i ] );

    fill( SPLX::c , SPLX::c + n_var , 0 );
    for( int id : path ) {
      SPLX::c[ id ] = -es[ id ].c;
    }
    double mn = -SPLX::simplex( SPLX::a , SPLX::b , SPLX::c , n_con , n_var );
    //printf( "mn %.9f\n" , mn );
    //FOR( i , m ) printf( "x %d %.9f\n" , i , SPLX::x[ i ] );

    printf( "%d %d %.9lf %.9lf\n" , s , t , mn , mx );

  }
  
}
