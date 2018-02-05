
// default code for competitive programming
// ver 3.14159 {{{
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx2,sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
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

const int S = 53;
const int MOD = 1e9+7;
const int N = 1e6+10;

inline int add(int a,int b) { a+=b;return a>=MOD?a-MOD:a; }
inline int sub(int a,int b) { a-=b;return a<0?a+MOD:a; }
inline int mul(ll a,int b) { a*=b;return a>=MOD?a%MOD:a; }

inline int enc(char c) {
  if (isupper(c)) return c-'A';
  if (islower(c)) return 26+c-'a';
  return 52;
}

int n;
char ip[N];
int s[N][S], b[S][S];
int d[N][S], c[S][S];

void build() {
  FOR(i, S) b[i][i] = 1, s[0][i] = 1;
  REP(i, 1, n) {
    int ch = enc(ip[i]);
    // S_i = 2S_{i-1} - b_{i-1, ch}
    FOR(j, S) s[i][j] = sub(mul(s[i-1][j], 2), b[ch][j]);
    // b_{i, ch} = S_{i-1}
    FOR(j, S) b[ch][j] = s[i-1][j];
    // b_{i, c} = b_{i-1, c} if c != ch
  }

  FOR(i, S) c[i][i] = 1;
  REP(i, 1, n) {
    int ch = enc(ip[i]);
    // D_i = C_{i-1, ch}
    FOR(j, S) d[i][j] = c[ch][j];
    // C_{i, ch} = 2C_{i-1, ch} - D_{i-1}
    FOR(j, S) c[ch][j] = sub(mul(2, c[ch][j]), d[i-1][j]);
    // C_{i, c} = C_{i-1, c} if c != ch
  }
}

inline int calc(int l, int r) {
  int res = 0;
  FOR(j, S) {
    int srj = s[r][j];
    int csdl1j = sub(j + 1 == S ? 1: 0, d[l-1][j]);
    res = add(res, mul(srj, csdl1j));
  }
  return res;
}

void solve() {
  int Q, a0, b0, p, q, r, z = 0;
  R(Q, a0, b0, p, q, r);
  FOR(i, Q) {
    int ta, tb;
    ta = add(add(mul(p, a0), mul(q, b0)), add(z, r));
    tb = add(add(mul(p, b0), mul(q, a0)), add(z, r));
    int x = min(ta%n, tb%n)+1;
    int y = max(ta%n, tb%n)+1;
    z = calc(x, y);
    a0 = ta;
    b0 = tb;
  }
  W(z);
}

int main() {
  scanf("%s", ip+1); n = strlen(ip+1);
  build();
  solve();
}
