
// default code for competitive programming
// ver 3.14159 {{{
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
int _R( char c ) { return scanf( "%c" , &c ); }
int R() { return 0; }

template< typename T , typename... U > int R( T& x , U&... tail ) { return _R(x) + R(tail...); }

template<class T> void _W(const T &x) { cout << x; }
void _W(const int &x) { printf("%d", x); }
void _W(const int64_t &x) { printf("%" PRId64, x); }
void _W(const double &x) { printf("%.16f", x); }
void _W(const char &x) { putchar(x); }
void _W(const char *x) { printf("%s", x); }
template<class T> void _W(const vector<T> &x) { for (auto i = x.begin(); i != x.end(); _W(*i++)) if (i != x.cbegin()) putchar(' '); }
void W() {}
template<class T, class... U> void W(const T &head, const U &... tail) { _W(head); putchar(sizeof...(tail) ? ' ' : '\n'); W(tail...); }

// }}}
// start ~~QAQ~~

struct MaxCostCirc {
  static const int MAXN = 333;
  struct Edge { int w , c; };
  int n;
  Edge g[MAXN][MAXN];
  int dis[MAXN],prv[MAXN];
  bool vis[MAXN];
  int ans;
  void init(int _n) { n=_n,ans=0;REP(i,1,n)REP(j,1,n)g[i][j]={0,0}; }
  void adde(int u,int v,int w,int c) {
    g[u][v] = {w, c}; g[v][u] = {-w, 0};
  }
  bool poscyc() {
    fill(dis,dis+n+1,0);
    fill(prv,prv+n+1,0);
    fill(vis,vis+n+1,0);
    int tmp = -1;
    FOR(t, n+1) {
      REP(i, 1, n) REP(j, 1, n) {
        Edge& e = g[i][j];
        if (e.c && dis[j] < dis[i]+e.w) {
          dis[j] = dis[i]+e.w;
          prv[j] = i;
          if ( t==n ) { tmp=i;break; }
        }
      }
    }
    if (tmp == -1) return 0;
    int cur = tmp;
    for (;!vis[cur];cur=prv[cur]) vis[cur] = 1;
    int now = cur;
    int cost = 0 , df = 100000;
    do {
      Edge &e = g[prv[now]][now];
      df = min(df, e.c);
      cost += e.w;
      now = prv[now];
    } while (now != cur);
    ans += df*cost;
    now = cur;
    do{
      Edge &e = g[prv[now]][now];
      Edge &re = g[now][prv[now]];
      e.c -= df;
      re.c += df;
      now = prv[now];
    }while (now != cur);
    return 1;
  }
} circ;

const int N = 111;

int n, A, B, cntc;
char ip[N][N];

inline int chk(int lim) {
  while (circ.poscyc());
  //debug("calc %d ans %d\n", lim, circ.ans);
  int res = circ.ans;
  if (res / 100000 != cntc) return -1;
  int tot = cntc + res % 100000;
  if (lim * B <= A*tot) return tot - cntc;
  return -1;
}

int main() {
  int cs = 0;
  while (1) {
    R(n, A, B);
    if (!n) break;
    REP(i, 1, n) scanf("%s", ip[i]+1);
    circ.init(n+n+n);
    REP(i, 1, n) circ.adde(i, n+i, 0, 0), circ.adde(n+i, n+n+i, 0, 0);
    cntc = 0;
    REP(i, 1, n) REP(j, 1, n) {
      if (ip[i][j] == 'C') {
        circ.adde(n+n+i, j, 100000, 1);
        cntc++;
      }
      if (ip[i][j] == '.') {
        circ.adde(n+n+i, j, 1, 1);
      }
    }
    int ans = -1;
    REP(x, 0, n) {
      ans = max(ans, chk(x));
      REP(i, 1, n) {
        circ.g[i][n+i].c++;
        circ.g[n+i][n+n+i].c++;
      }
    }
    if (ans == -1) printf("Case %d: impossible\n", ++cs);
    else printf("Case %d: %d\n", ++cs, ans);
  }
}
