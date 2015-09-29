
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

const int MAXN = 50010;

int n , w[ MAXN ];
vector< pii > g[ MAXN ];
ll dis[ MAXN ] , dp[ MAXN ] , sz[ MAXN ];

void dfs1( int u , int p )
{
    sz[ u ] = w[ u ];
    dis[ u ] = 0ll;
    for( pii e : g[ u ] )
    {
        int v = e.first , c = e.second;
        if( v == p ) continue ;
        dfs1( v , u );
        sz[ u ] += sz[ v ];
        dis[ u ] += dis[ v ] + c * sz[ v ];
    }
}

void dfs2( int u , int p , ll resSz , ll resDis )
{
    dp[ u ] = dis[ u ] + resDis;
    for( pii e : g[ u ] )
    {
        int v = e.first , c = e.second;
        if( v == p ) continue ;
        ll tsz = resSz + sz[ u ] - sz[ v ];
        ll tdis = resDis + dis[ u ] - dis[ v ] - c * sz[ v ] + tsz * c;
        dfs2( v , u , tsz , tdis );
    }
}

int main()
{
    int tc;scanf("%d",&tc);while(tc--)
    {
        scanf( "%d" , &n );
        REP( i , 1 , n )
        {
            w[ i ] = 0;
            g[ i ].clear();
        }
        REP( i , 1 , n - 1 )
        {
            int u , v , c;
            scanf( "%d%d%d" , &u , &v , &c );
            g[ u ].push_back( pii( v , c ) );
            g[ v ].push_back( pii( u , c ) );
        }
        int m;scanf("%d",&m);
        while( m-- )
        {
            int u , f;scanf( "%d%d" , &u , &f );
            w[ u ] += f;
        }
        dfs1( 1 , -1 );
        dfs2( 1 , -1 , 0 , 0 );
        ll mn = dp[ 1 ];
        vector< int > ans;
        REP( i , 1 , n )
        {
            if( dp[ i ] == mn ) ans.push_back( i );
            else if( dp[ i ] < mn )
            {
                ans.clear();
                ans.push_back( i );
                mn = dp[ i ];
            }
        }
        cout << mn*2 << '\n';
        REP( i , 0 , SZ( ans ) - 1 )
            printf( "%d%c" , ans[ i ] , " \n"[ i+1 == SZ( ans ) ] );
    }
}
