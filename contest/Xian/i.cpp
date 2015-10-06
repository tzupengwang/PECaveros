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

const int MAXN = 30010;
typedef pair< ll , ll > pll;
int tot , root , ch[ MAXN * 100 ][ 2 ] , isend[ MAXN * 100 ];

inline int newNode()
{
    int res = ++tot;
    ch[ res ][ 0 ] = ch[ res ][ 1 ] = 0;
    isend[ res ] = 0;
    return res;
}

int n;
ll nw[ MAXN ];
int sz[ MAXN ];

void dfs( int np , ll tnw , int l , vector< pli >&ans )
{
    if( isend[ np ] )
        return ;
    if( !np )
    {
        ans.push_back( pli( tnw , l ) );
        return ;
    }
    dfs( ch[ np ][ 0 ] , tnw , l+1 , ans );
    dfs( ch[ np ][ 1 ] , tnw + ( 1ll << ( 32 - l - 1 )  ), l+1 , ans );
    return ;
}

int main()
{
    int cs = 0;
    int tc;scanf("%d",&tc);while(tc--)
    {printf("Case #%d:\n" , ++cs);
        scanf( "%d" , &n );
        REP( i , 1 , n )
        {
            int a , b , c , d , l;
            scanf( "%d.%d.%d.%d/%d" , &a , &b , &c , &d , &l );
            //printf( "%d %d %d %d %d\n" , a , b , c , d , l );
            nw[ i ] = ( (ll)a << 24 ) + ((ll)b<<16)+((ll)c<<8)+(ll)d;
            sz[ i ] = l;
        }
        tot = 0;
        root = 0;
        REP( i , 1 , n )
        {
            if( !root ) root = newNode();
            int np = root;
            //printf( "np %d sz %d\n" , np , sz[ i ] ) ;
            REP( j , 1 , sz[ i ] )
            {
                int b = ( nw[ i ] >> ( 32 - j ) ) & 1;
                //printf("%d",b);
                if( !ch[ np ][ b ] ) ch[ np ][ b ] = newNode();
                np = ch[ np ][ b ];
            }
            //puts("");
            isend[ np ] = 1;
        }
        vector< pli > ans;
        dfs( root , 0ll , 0 , ans );
        printf( "%d\n" , SZ( ans ) );
        for( pli p : ans )
        {
            int a = (p.first >> 24) & 0xff;
            int b = (p.first >> 16) & 0xff;
            int c = (p.first >> 8) & 0xff;
            int d = (p.first >> 0) & 0xff;
            int l = p.second;
            printf( "%d.%d.%d.%d/%d\n" , a , b , c , d , l );
        }
    }
}
