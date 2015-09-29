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

int n , d , in[ MAXN ];

int main()
{
    int tc;scanf("%d",&tc);while(tc--)
    {
        scanf( "%d%d" , &d , &n );
        REP( i , 1 , n ) scanf( "%d" , in+i );
        ll ans = 0ll;
        map< int , int > cnt;
        int s = 0;
        cnt[ 0 ] = 1;
        REP( i , 1 , n )
        {
            s = ( s + in[ i ] ) % d;
            ans += cnt[ s ];
            cnt[ s ]++;
        }
        cout << ans << '\n';
    }
}
