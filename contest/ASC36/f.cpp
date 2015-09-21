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

const int MAXN = 55;
const int MAXC = 5010;

int n , w[ MAXN ] , C;
int ord[ MAXN ];
int dp1[ MAXN ][ MAXC ];
int dp2[ MAXN ][ MAXC ];
int chs[ MAXN ][ MAXC ];

inline void upd( int& x , int y )
{ x = min( x , y ); }

void get1( int i , int j , vector< int >& res )
{
  assert( dp1[ i ][ j ] <= n );
  if( i == 0 ) return ;
  if( dp1[ i ][ j ] == dp1[ i-1 ][ j ] )
    get1( i-1 , j , res );
  else
  {
    res.push_back( ord[ i ] );
    get1( i-1 , j - w[ ord[ i ] ] , res );
  }
}

void get2( int i , int j , vector< int >& res )
{
  //printf( "  get %d %d\n" , i , j );
  assert( dp2[ i ][ j ] <= n );
  if( i == n+1 ) return ;
  if( dp2[ i ][ j ] == dp2[ i+1 ][ j ] )
    get2( i+1 , j , res );
  else
  {
    res.push_back( ord[ i ] );
    get2( i+1 , j - w[ ord[ i ] ] , res );
  }
}

bool chk( vector< int > A , vector< int > B )
{
  if( SZ( A ) == 0 || SZ( B ) == 0 ) return 0;
  if( SZ( A ) <= SZ( B ) ) return 0;
  int sumb = 0;
  for( int id : B ) sumb += w[ id ];
  for( int a : A )
  {
    bool fl = 1;
    for( int b : B ) if( a == b ) fl = 0;
    if( !fl ) continue ;
    if( sumb + w[ a ] <= C ) return 0;
  }
  return 1;
}

int main()
{
  FILE( "knapsack" );
  IOS;
  cin >> n;
  REP( i , 1 , n ) cin >> w[ ord[ i ] = i ];
  cin >> C;


  //cout << n << '\n';
  //REP( i , 1 , n ) cout << w[ i ] << ' ';cout << '\n';
  //cout << C << '\n';


  sort( ord+1 , ord+1+n , [&](int a,int b){return w[a]<w[b];} );

  REP( i , 0 , MAXN-1 )
    fill( dp1[ i ] , dp1[ i ] + MAXC , MAXN );
  dp1[ 0 ][ 0 ] = 0;
  REP( i , 1 , n )
  {
    REP( j , 0 , C )
    {
      upd( dp1[ i ][ j ] , dp1[ i-1 ][ j ] );
      if( w[ ord[ i ] ] <= j )
        upd( dp1[ i ][ j ] , dp1[ i-1 ][ j-w[ ord[ i ] ] ] + 1 );
    }
  }

  REP( i , 0 , MAXN-1 )
    fill( dp2[ i ] , dp2[ i ] + MAXC , MAXN );
  dp2[ n+1 ][ 0 ] = 0;
  REPD( j , C , 0 )
  {
    int i = n+1;
    chs[ i ][ j ] = j;
    if( j < C && dp2[ i ][ chs[ i ][ j+1 ] ] < dp2[ i ][ j ] )
      chs[ i ][ j ] = chs[ i ][ j+1 ];
  }
  REPD( i , n , 1 )
  {
    REPD( j , C , 0 )
    {
      upd( dp2[ i ][ j ] , dp2[ i+1 ][ j ] );
      if( w[ ord[ i ] ] <= j )
        upd( dp2[ i ][ j ] , dp2[ i+1 ][ j-w[ ord[ i ] ] ] + 1 );
      chs[ i ][ j ] = j;
      if( j < C && dp2[ i ][ chs[ i ][ j+1 ] ] < dp2[ i ][ j ] )
        chs[ i ][ j ] = chs[ i ][ j+1 ];
    }
  }


  REP( i , 1 , n )
  {
    REP( j , 0 , C )
    {
      if( dp1[ i-1 ][ j ] > n ) continue ;
      if( j + w[ ord[ i ] ] > C ) continue ;
      int sum = j , cntA = 0;
      REP( k , i , n ) if( sum + w[ ord[ k ] ] <= C )
      {
        sum += w[ ord[ k ] ];
        cntA++;
      }

      int mn = C+1-w[ord[i]]-j;
      int cntB = dp2[ i+1 ][ chs[ i+1 ][ mn ] ];

      if( cntA <= cntB ) continue ;

      vector< int > A , B;
      get1( i - 1 , j , A );
      get1( i - 1 , j , B );
      sum = j;
      REP( k , i , n ) if( sum + w[ ord[ k ] ] <= C )
      {
        sum += w[ ord[ k ] ];
        A.push_back( ord[ k ] );
      }

      //printf( "pivot %d %d\n" , ord[ i ] , w[ ord[ i ] ] );
      //printf( "j %d\n" , j );

      get2( i+1 , chs[ i+1 ][ mn ] , B );

      if( SZ( A ) == 0 || SZ( B ) == 0 ) continue ;
      sort( ALL( A ) );
      sort( ALL( B ) );
      if( !chk( A , B ) ) while( 1 );



      int suma = 0;
      for( int a : A ) suma += w[ a ];
      int sumb = 0;
      for( int b : B ) sumb += w[ b ];

      //printf( "suma %d sumb %d\n" , suma , sumb );

      cout << "NO\n3\n";
      cout << SZ( A );
      for( int x : A ) cout << ' ' << x;
      cout << '\n';

      cout << SZ( B );
      for( int x : B ) cout << ' ' << x;
      cout << '\n';


      return 0;
    }
  }

  puts( "YES" );
}
