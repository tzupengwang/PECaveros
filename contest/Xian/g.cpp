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

const int MAXN = 200010;


struct PalT{
    struct Node{
        int nxt[ 33 ] , len , fail;
        ll cnt;
    };
    int tot , lst;
    Node nd[ MAXN * 2 ];
    char* s;
    int newNode( int l , int _fail ){
        int res = ++tot;
        memset( nd[ res ].nxt , 0 , sizeof nd[ res ].nxt );
        nd[ res ].len = l;
        nd[ res ].cnt = 0;
        nd[ res ].fail = _fail;
        return res;
    }
    void push( int p ){
        //printf( "  push %d\n" , p );
        int np = lst;
        int c = s[ p ] - 'a';
        while( p - nd[ np ].len - 1 < 0
            || s[ p ] != s[ p - nd[ np ].len - 1 ]
        )
            np = nd[ np ].fail;

        //puts( "jizzz1" );
        if( nd[ np ].nxt[ c ] ){
            nd[ nd[ np ].nxt[ c ] ].cnt++;
            lst = nd[ np ].nxt[ c ];
            return ;
        }

        int nq = newNode( nd[ np ].len + 2 , 0 );
        nd[ nq ].cnt++;
        nd[ np ].nxt[ c ] = nq;
        lst = nq;
        if( nd[ nq ].len == 1 ){
            nd[ nq ].fail = 2;
            return ;
        }

        int tf = nd[ np ].fail;
        while( p - nd[ tf ].len - 1 < 0
            || s[ p ] != s[ p - nd[ tf ].len - 1 ]
        )
            tf = nd[ tf ].fail;
        //puts( "jizzz2" );

        nd[ nq ].fail = nd[ tf ].nxt[ c ];
        return ;
    }
    void init( char* _s ){
        s = _s;
        tot = 0;
        newNode( -1 , 1 );
        newNode( 0 , 1 );
        lst = 2;
        for( int i = 0 ; s[ i ] ; i++ )
        {
            push( i );
            //printf( "suf pal len %d id %d fail %d\n" , nd[ lst ].len , lst , nd[ lst ].fail );
        }
    }
    void yutruli(){
        REPD( i , tot , 1 )
        {
            //printf( "cnt %d %lld\n" , i , nd[ i ].cnt );
            nd[ nd[ i ].fail ].cnt += nd[ i ].cnt;
        }
        nd[ 1 ].cnt = nd[ 2 ].cnt = 0ll;
    }
} pA , pB;

char sa[ MAXN ] , sb[ MAXN ];

ll dfs( int u , int v )
{
    //printf( "  dfs %d %d\n" , u , v );
    if( !u || !v ) return 0ll;
    ll res = pA.nd[ u ].cnt * pB.nd[ v ].cnt;
    REP( i , 0 , 25 )
        res += dfs( pA.nd[ u ].nxt[ i ] , pB.nd[ v ].nxt[ i ] );
    return res;
}

int main(){
    int cs=0;
    int tc;scanf("%d",&tc);while(tc--)
    {printf("Case #%d: ",++cs);
        scanf("%s%s", sa , sb);
        pA.init( sa );
        pA.yutruli();
        //puts( "AAAAAAAAAAAAABBBBBBBBBBBBB" );
        pB.init( sb );
        pB.yutruli();
        ll ans = 0ll;
        ans += dfs( 1 , 1 );
        ans += dfs( 2 , 2 );
        cout << ans << '\n';
        //break ;
    }
}
