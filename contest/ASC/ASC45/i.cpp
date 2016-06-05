
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

const int MAXN = 110;

int n , m , t;
int iter[ MAXN ];
int par[ MAXN ];
int cap_p[ MAXN ] , cap_t[ MAXN ];
vector<int> pref_s[ MAXN ] , pref_t[ MAXN ];
vector<int> own_t[ MAXN ];

int like_ts[ MAXN ][ MAXN ];
int like_sp[ MAXN ][ MAXN ];
vector<pii> propo[ MAXN ];
int ass[ MAXN ];

void R_vec( vector<int>& vec ) {
  int l;R( l );
  vec.resize( l );
  FOR( i , l ) R( vec[ i ] );
}

bool go() {
  debug( "go\n" );
  REP( i , 1 , t ) propo[ i ].clear();
  int cnt_propo = 0;
  REP( i , 1 , n ) {
    if( ass[ i ] ) continue ;
    for( int& j = iter[ i ] ; j < SZ( pref_s[ i ] ) ; j++ ) {
      int prj = pref_s[ i ][ j ];
      if( cap_t[ par[ prj ] ] && cap_p[ prj ] ) {
        cnt_propo++;
        if( like_ts[ par[ prj ] ][ i ] ) {
          debug( "  %d -> %d\n" , i , prj );
          propo[ par[ prj ] ].push_back( { i , prj } );
        }
        break ;
      }
    }
  }
  if( !cnt_propo ) return 0;
  int cnt_ass = 0;
  REP( i , 1 , t ) {
    if( !cap_t[ i ] ) continue ;
    debug( "  now teacher %d\n" , i );
    sort( ALL( propo[ i ] ) , [&]( pii a , pii b ) {
      return like_sp[ i ][ a.first ] > like_sp[ i ][ b.first ];
    } );
    for( pii p : propo[ i ] ) {
      if( !cap_t[ i ] ) break ;
      int s_id , p_id;
      tie( s_id , p_id ) = p;
      if( cap_p[ p_id ] ) {
        debug( "    ass %d %d\n" , s_id , p_id );
        cap_p[ p_id ]--;
        cap_t[ i ]--;
        ass[ s_id ] = p_id;
        cnt_ass++;
      }
    }
  }
  if( !cnt_ass ) return 0;
  return 1;
}

bool go2() {
  debug( "go2\n" );
  REP( i , 1 , n ) propo[ i ].clear();
  int cnt_propo = 0;
  int cnt_ass = 0;
  REP( i , 1 , t ) {
    if( !cap_t[ i ] ) continue ;
    for( int j = 0 ; j < SZ( pref_t[ i ] ) ; j++ ) {
      int s_id = pref_t[ i ][ j ];
      //if( ass[ s_id ] ) continue;
      int id = -1;
      for( int x : own_t[ i ] ) {
        if( !cap_p[ x ] ) continue ;
        if( id == -1 || like_sp[ s_id ][ x ] > like_sp[ s_id ][ id ] ) {
          id = x;
        }
      }
      if( id > 0 && like_sp[ s_id ][ id ] ) {
        if( !ass[ s_id ] || like_sp[ s_id ][ id ] > like_sp[ s_id ][ ass[ s_id ] ] ) {
          debug( "  %d -> %d with %d\n" , i , s_id , id );
          //propo[ s_id ].push_back( { id , i } );
          if( ass[ s_id ] ) {
            cap_p[ ass[ s_id ] ]++;
            cap_t[ par[ ass[ s_id ] ] ]++;
          }
          ass[ s_id ] = id;
          cap_p[ id ]--;
          cap_t[ i ]--;
          cnt_ass++;
          cnt_propo++;
          break ;
        }
      }
    }
  }
  if( !cnt_propo ) return 0;
  return 1;
  
  REP( i , 1 , n ) {
    //if( ass[ i ] ) continue ;
    debug( "  stud %d\n" , i );
    if( !SZ( propo[ i ] ) ) continue;
    sort( ALL( propo[ i ] ) , [&]( pii a , pii b ) {
      return like_sp[ i ][ a.first ] > like_sp[ i ][ b.first ];
    } );
    int p_id , t_id;
    tie( p_id , t_id ) = propo[ i ][ 0 ];
    if( !ass[ i ] || like_sp[ i ][ p_id ] > like_sp[ i ][ ass[ i ] ] ) {
      debug( "    choose %d of teacher %d\n" , p_id , t_id );
      if( ass[ i ] ) {
        cap_p[ ass[ i ] ]++;
        cap_t[ par[ ass[ i ] ] ]++;
      }
      cap_p[ p_id ]--;
      cap_t[ t_id ]--;
      ass[ i ] = p_id;
      cnt_ass++;
    }
  }
  
  if( !cnt_ass ) return 0;
  return 1;
  
}

void main2() {
  REP( i , 1 , n ) {
    ass[ i ] = 0;
    R_vec( pref_s[ i ] );
    fill( like_sp[ i ] , like_sp[ i ]+m+1 , 0 );
    int now = 100000;
    for( int x : pref_s[ i ] ) like_sp[ i ][ x ] = --now;
  }
  REP( i , 1 , m ) R( cap_p[ i ] );
  REP( i , 1 , t ) {
    iter[ i ] = 0;
    R( cap_t[ i ] );
    R_vec( pref_t[ i ] );


    fill( like_ts[ i ] , like_ts[ i ]+n+1 , 0 );
    int now = 100000;
    for( int x : pref_t[ i ] ) like_ts[ i ][ x ] = --now;

    R_vec( own_t[ i ] );
    for( int x : own_t[ i ] ) par[ x ] = i;
  }

//0 2 3 6 0 6 5 4 7
//4 2 3 6 0 6 5 0 7 

  while( 1 ) {
    bool flag = go2();
    if( !flag ) break ;
  }

  REP( i , 1 , n ) printf( "%d%c" , ass[ i ] , " \n"[ i == n ] );

}

int main()
{
  FILE( "informatics" );
  while( 1 ) {
    R( n , m , t );
    if( !n ) break ;
    main2();
  }
}
