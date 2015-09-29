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

const int MAXN = 110;
const int MAXP = 110;

int n , l[ MAXN ] , a[ MAXN ][ 11 ];
int p , s[ MAXP ] , d[ MAXP ] , t[ MAXP ];
bool good[ MAXP ];

vector< pii > rt[ MAXP ];

int main()
{
  FILE( "hot" );
  //IOS;
  cin >> n;
  REP( i , 1 , n )
  {
    cin >> l[ i ];
    REP( j , 0 , l[ i ] - 1 ) cin >> a[ i ][ j ];
  }
  cin >> p;
  REP( i , 1 , p )
  {
    cin >> s[ i ] >> d[ i ] >> t[ i ];
    int now = s[ i ];
    good[ i ] = 0;
    REP( nt , t[ i ] , 200000 )
    {
      if( now == d[ i ] )
      {
        rt[ i ].push_back( pii( nt , now ) );
        good[ i ] = 1;
        break ;
      }
      rt[ i ].push_back( pii( nt , now ) );
      now = a[ now ][ nt % l[ now ] ];
    }
    if( good[ i ] ) sort( ALL( rt[ i ] ) );
  }
  vector< int > sol;   
  vector< int > candi;
  REP( i , 1 , p ) if( good[ i ] ) candi.push_back( i );
  sort( ALL( candi ) , [&](int A,int B){
    return tii( rt[ A ].back().first , -t[ A ] )
         < tii( rt[ B ].back().first , -t[ B ] );
  } );
  //for( int x : candi )
    //printf( "  %d %d %d\n" , x , rt[ x ].back().first , rt[ x ].back().second );
  set< pii > shit;
  for( int x : candi )
  {
    bool fl = 1;
    
    for( pii pp : rt[ x ] )
      if( shit.count( pp ) )
      {
        fl = 0;
        break ;
      }
    if( fl )
    {
      sol.push_back( x );
      for( pii pp : rt[ x ] )
        shit.insert( pp );
    }
    
  }
  
  sort( ALL( sol ) );
  cout << SZ( sol ) << '\n';
  for( int x : sol ) cout << x << " \n"[ x == sol.back() ];
}
