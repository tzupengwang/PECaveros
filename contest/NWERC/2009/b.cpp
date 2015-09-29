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

typedef pair< ll , ll > pll;

const int MAXN = 500010;

int n;
char s[ MAXN ];

struct Hsh
{
    ll MOD;
    ll BASE;
    ll pw[ MAXN ];
    ll hsh[ MAXN ];

    inline ll add(ll a,ll b){return (a+b)%MOD;}
    inline ll sub(ll a,ll b){return (a-b+MOD)%MOD;}
    inline ll mul(ll a,ll b){return (a*b)%MOD;}

    inline void init( ll _B , ll _M )
    {
        BASE = _B , MOD = _M;
        pw[ 0 ] = 1;
        REP( i , 1 , MAXN-1 ) pw[ i ] = mul( BASE , pw[ i-1 ] );
    }

    inline void makeHsh()
    {
        REP( i , 1 , n )
            hsh[ i ] = add( s[ i ] , mul( BASE , hsh[ i-1 ] ) );
    }

    inline ll get( int l , int r )
    {return sub(hsh[r],mul(pw[r-l+1],hsh[l-1]));}

} hsh1 , hsh2;

int cnt;
map< pll , int > mp;
map< pii , int > spl;

int dfs1( int l )
{
    //printf( "dfs1 %d\n" , l );
    int tsp = -1 , r = -1;
    for( int i = l ; i <= n + 1 ; i++ )
    {
        if( s[ i ] == '(' )
        {
            int nxt = dfs1( i+1 );
            tsp = nxt + 1;
            int nnxt = dfs1( tsp+1 );
            r = nnxt+1;
            spl[ pii( l , r ) ] = tsp;
            break ;
        }
        if( i == n + 1 || s[ i ] == ',' || s[ i ] == ')' )
        {
            r = i-1;
            break ;
        }
    }
    //printf( "%d %d\n" , l , r );
    return r;
}

void dfs2( int l , int r )
{
    ll h1 = hsh1.get( l , r ) , h2 = hsh2.get( l , r );
    if( mp.count( pll( h1 , h2 ) ) )
    {
        printf( "%d" , mp[ pll( h1 , h2 ) ] );
        return ;
    }
    mp[ pll( h1 , h2 ) ] = ++cnt;
    if( spl.count( pii( l , r ) ) )
    {
        int tsp = spl[ pii( l , r ) ];
        for( int i = l ; i <= r ; i++ )
        {
            printf( "%c" , s[ i ] );
            if( s[ i ] == '(' )
            {
                dfs2( i+1 , tsp-1 );
                printf(",");
                dfs2( tsp+1 , r-1 );
                printf(")");
                return ;
            }
        }
    }
    else
    {
        for( int i = l ; i <= r ; i++ )
            printf( "%c" , s[ i ] );
    }

}

int main()
{
    hsh1.init( 13131 , 1000000007 );
    hsh2.init( 13131 , 1000000009 );
    int tc;scanf("%d",&tc);while(tc--)
    {
        scanf( "%s" , s+1 );
        n = strlen( s+1 );
        hsh1.makeHsh();
        hsh2.makeHsh();
        spl.clear();
        assert( dfs1( 1 ) == n );
        mp.clear();
        cnt = 0;
        dfs2( 1 , n );
        puts( "" );
    }
}
