
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
/*
 * sfail: compressed fail links with same diff
 * O(lgn): length of sfail link path
 */
const int MAXN = 2e5+10;
const int LOG = 20;
struct PalT{
  int tot,lst;
  int n, ans;
  int nxt[MAXN][26], len[MAXN];
  int fail[MAXN], diff[MAXN], sfail[MAXN];
  int full[MAXN], half[MAXN];
  int even_jp[LOG][MAXN];
  char* s;
  inline int go(int x) { // find deepest parent p of x s.t. len[p]: even and len[p]*2 <= len[x]
    int tlen = len[x];
    REPD(k, LOG-1, 0) {
      int y = even_jp[k][x];
      if (len[y]*2 > tlen) x = y;
    }
    return even_jp[0][x];
  }
  int newNode(int l, int _fail) {
    int res = ++tot;
    fill(nxt[res], nxt[res]+26, 0);

    len[res] = l, fail[res] = _fail;
    diff[res] = l - len[_fail];
    if (diff[res] == diff[_fail]) {
      sfail[res] = sfail[_fail];
    } else {
      sfail[res] = _fail;
    }

    full[res] = half[res] = MAXN;
    if (len[fail[res]] % 2 == 0) even_jp[0][res] = fail[res];
    else even_jp[0][res] = even_jp[0][fail[res]];
    FOR(k, LOG-1)
      even_jp[k+1][res] = even_jp[k][even_jp[k][res]];

    return res;
  }

  void push(int p) {
    int np = lst;
    int c = s[p]-'a';
    while (p-len[np]-1 < 0 || s[p] != s[p-len[np]-1])
      np = fail[np];
    if ((lst=nxt[np][c])) {
      return;
    }
    int nq_f = 0;
    if (len[np]+2 == 1) {
      nq_f = 2;
    } else {
      int tf = fail[np];
      while (p-len[tf]-1 < 0 || s[p] != s[p-len[tf]-1])
        tf = fail[tf];
      nq_f = nxt[tf][c];
    }
    int nq = newNode(len[np]+2, nq_f);
    nxt[np][c] = nq;
    lst=nq;
    if (len[nq] % 2 == 0) {
      half[nq] = 1 + half[np];
      int pt = go(nq);
      half[nq] = min(half[nq], full[pt] + len[nq] / 2 - len[pt]);

      full[nq] = min(half[nq] + 1, len[nq] - len[fail[nq]] + full[fail[nq]]);
      full[nq] = min(full[nq], 2 + full[np]);

      ans = min(ans, full[nq] + n - len[nq]);
    }
  }
  void init(char* _s){
    s = _s;
    tot = 0;
    ans = n = strlen(s);
    newNode(-1, 1);
    newNode(0, 1);

    diff[2] = 0;
    half[2] = full[2] = 0;
    FOR(k, LOG) even_jp[k][2] = 2;

    lst = 2;
  }
} palt;

const int N = 1e5+10;

int n;
char ip[N];

void main2() {
  R(ip); n = strlen(ip);
  FOR(i, n) ip[i] = ip[i] - 'A' + 'a';
  palt.init(ip);
  FOR(i, n) {
    palt.push(i);
  }
  W(palt.ans);
}

int main() {
  int tc; R(tc); while (tc--) main2();
}
