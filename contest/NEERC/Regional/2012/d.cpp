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

const int MAXN = 10010;
const int MAXL = 44;

struct Trie
{
    int tot , root;
    int nxt[ MAXN * MAXL * 2 ][ 26 ];
    int cnt[ MAXN * MAXL * 2 ];
    inline int newNode()
    {
        int res = ++tot;
        memset( nxt[ res ] , 0 , sizeof nxt[ res ] );
        cnt[ res ] = 0;
        return res;
    }
    void init()
    {
        tot = 0;
        root = newNode();
    }
    inline void insert( char *s )
    {
        int np = root;
        for( int i = 0 ; s[ i ] ; i++ )
        {
            int c = s[ i ] - 'a';
            if( !nxt[ np ][ c ] )
                nxt[ np ][ c ] = newNode();
            np = nxt[ np ][ c ];
            cnt[ np ] = 1;
        }
    }
    inline void yutruli()
    {
        REPD( i , tot , 1 )
        {
            REP( j , 0 , 25 )
                cnt[ i ] += cnt[ nxt[ i ][ j ] ];
        }
    }
    inline void doSuf( ll dp[ 33 ] )
    {
        REP( i , 2 , tot )
        {
            REP( j , 0 , 25 ) if( nxt[ i ][ j ] )
                dp[ j ]++;
        }
    }
} t1 , t2;

int n;
char ts[ MAXL ];
ll dp[ 33 ];
ll shit[ 33 ];

ll dfs( int np , int c )
{
    if( !np ) return 0ll;
    ll res = dp[ c ];
    REP( j , 0 , 25 )
        res += dfs( t1.nxt[ np ][ j ] , j );
    return res;
}

int main()
{
    FILE( "dictionary" );
    t1.init();
    t2.init();
    scanf( "%d" , &n );
    REP( i , 1 , n )
    {
        scanf( "%s" , ts );
        int l = strlen( ts );
        if( l == 1 ) shit[ ts[ 0 ] - 'a' ] = 1ll;
        t1.insert( ts );
        reverse( ts , ts+l );
        t2.insert( ts );
    }
    t1.yutruli();
    t2.yutruli();
    ll ans = (ll)t1.cnt[ 1 ] * (ll)t2.cnt[ 1 ];
    //cout << ans << endl;
    t2.doSuf( dp );
    REP( j , 0 , 25 )
        ans -= dfs( t1.nxt[ 1 ][ j ] , 30 );
    REP( i , 0 , 25 ) ans += shit[ i ];
    cout << ans << endl;
}
