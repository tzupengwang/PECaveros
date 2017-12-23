
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

typedef long long LL;
template<LL P, LL root, int MAXN>
struct NTT{
  static LL bigmod(LL a, LL b) {
    LL res = 1;
    for (LL bs = a; b; b >>= 1, bs = (bs * bs) % P) {
      if(b&1) res=(res*bs)%P;
    }
    return res;
  }
  static LL inv(LL a, LL b) {
    if(a==1)return 1;
    return (((LL)(a-inv(b%a,a))*b+1)/a)%b;
  }
  LL omega[MAXN+1], iv[MAXN+1];
  NTT() {
    omega[0] = 1;
    LL r = bigmod(root, (P-1)/MAXN);
    for (int i=1; i<=MAXN; i++) {
      omega[i] = (omega[i-1]*r)%P;
      iv[i] = inv(i, P);
    }
  }
  // n must be 2^k
  void tran(int n, LL a[], bool inv_ntt=false){
    int basic = MAXN / n;
    int theta = basic;
    for (int m = n; m >= 2; m >>= 1) {
      int mh = m >> 1;
      for (int i = 0; i < mh; i++) {
        LL w = omega[i*theta%MAXN];
        for (int j = i; j < n; j += m) {
          int k = j + mh;
          LL x = a[j] - a[k];
          if (x < 0) x += P;
          a[j] += a[k];
          if (a[j] > P) a[j] -= P;
          a[k] = (w * x) % P;
        }
      }
      theta = (theta * 2) % MAXN;
    }
    int i = 0;
    for (int j = 1; j < n - 1; j++) {
      for (int k = n >> 1; k > (i ^= k); k >>= 1);
      if (j < i) swap(a[i], a[j]);
    }
    if (inv_ntt) {
      LL ni = iv[n];
      reverse( a+1 , a+n );
      for (i = 0; i < n; i++)
        a[i] = (a[i] * ni) % P;
    }
  }
  void operator()(int n, LL a[], bool inv_ntt=false) {
    tran(n, a, inv_ntt);
  }
};

const LL P=998244353,root=3;
const int MAXN=(1<<20);

struct PolyOp {
  NTT<P, root, MAXN> ntt;
  static int nxt2k(int x) {
    int i = 1; for (; i < x; i <<= 1); return i;
  }
  void Mul(int n, LL a[], int m, LL b[], LL c[]) {
    static LL aa[MAXN], bb[MAXN];
    int N = nxt2k(n+m);
    copy(a, a+n, aa); fill(aa+n, aa+N, 0);
    copy(b, b+m, bb); fill(bb+m, bb+N, 0);
    ntt(N, aa); ntt(N, bb);
    FOR(i, N) c[i] = aa[i] * bb[i] % P;
    ntt(N, c, 1);
  }
  void Inv(int n, LL a[], LL b[]) {
    static LL tmp[MAXN];
    if (n == 1) {b[0] = ntt.inv(a[0], P); return;}
    Inv((n+1)/2, a, b);
    int N = nxt2k(n*2);
    copy(a, a+n, tmp);
    fill(tmp+n, tmp+N, 0);
    fill(b+n, b+N, 0);
    ntt(N, tmp); ntt(N, b);
    FOR(i, N) {
      LL t1 = (2 - b[i] * tmp[i]) % P; if (t1 < 0) t1 += P;
      b[i] = b[i] * t1 % P;
    }
    ntt(N, b, 1);
    fill(b+n, b+N, 0);
  }
  void Div(int n, LL a[], int m, LL b[], LL d[], LL r[]) {
    static LL aa[MAXN], bb[MAXN], ta[MAXN], tb[MAXN];
    if (n < m) {copy(a, a+n, r); fill(r+n, r+m, 0); return;}
    // d: n-1 - (m-1) = n-m (n-m+1 terms)
    copy(a, a+n, aa); copy(b, b+m, bb);
    reverse(aa, aa+n); reverse(bb, bb+m);
    Inv(n-m+1, bb, tb);
    Mul(n-m+1, ta, n-m+1, tb, d);
    fill(d+n-m+1, d+n, 0); reverse(d, d+n-m+1);
    // r: m-1 - 1 = m-2 (m-1 terms)
    Mul(m, b, n-m+1, d, ta);
    FOR(i, n) { r[i] = a[i] - ta[i]; if (r[i] < 0) r[i] += P; }
  }
  void dx(int n, LL a[], LL b[]) { REP(i, 1, n-1) b[i-1] = i * a[i] % P; }
  void Sx(int n, LL a[], LL b[]) {
    b[0] = 0;
    FOR(i, n) b[i+1] = a[i] * ntt.iv[i+1] % P;
  }
  void Ln(int n, LL a[], LL b[]) { // S a' a^-1 dx
    static LL a1[MAXN], a2[MAXN], b1[MAXN];
    int N = nxt2k(n*2);
    dx(n, a, a1); Inv(n, a, a2);
    Mul(n-1, a1, n, a2, b1);
    Sx(n+n-1-1, b1, b);
    fill(b+n, b+N, 0);
  }
  void Exp(int n, LL a[], LL b[]) { // Newton solve ln b(x) - a(x) = 0
    // expa = b (1 - lnb + a)
    static LL lnb[MAXN], c[MAXN], tmp[MAXN];
    assert(a[0] == 0); // dont know exp(a[0]) mod P
    if (n == 1) {b[0] = 1; return;}
    Exp((n+1)/2, a, b);
    fill(b+(n+1)/2, b+n, 0);
    Ln(n, b, lnb);
    fill(c, c+n, 0); c[0] = 1;
    FOR(i, n) {
      c[i] += a[i] - lnb[i];
      if (c[i] < 0) c[i] += P;
      if (c[i] >= P) c[i] -= P;
    }
    Mul(n, b, n, c, tmp);
    copy(tmp, tmp+n, b);
  }
} polyop;

ll a[MAXN], b[MAXN], c[MAXN];
ll aa[MAXN], bb[MAXN], cc[MAXN];
ll d[MAXN], r[MAXN];

bool check_inv(int n) {
  FOR(_, 10) {
    FOR(i, n) a[i] = (rand() + 1) % P;
    polyop.Inv(n, a, b);
    int N = polyop.nxt2k(n+n);
    polyop.ntt(N, a); polyop.ntt(N, b);
    FOR(i, N) a[i] = a[i] * b[i] % P;
    polyop.ntt(N, a, 1);
    fill(a+n, a+N, 0);
    printf("%d ok\n", _);
    if (a[0] != 1) return 0;
    if (*max_element(a+1, a+n) != 0) return 0;
  }
  return 1;
}

bool check_div(int n) {
  int N = polyop.nxt2k(n);
  FOR(_, 10) {
    fill(a, a+N, 0);
    fill(b, b+N, 0);
    fill(d, d+N, 0);
    fill(r, r+N, 0);
    FOR(i, n) a[i] = (rand()) % P; a[n-1] = (rand()) % (P-1) + 1;
    FOR(i, n/2) b[i] = (rand()) % P; b[n/2-1] = (rand()) % (P-1) + 1;
    polyop.Div(n, a, n/2, b, d, r);
    polyop.Mul(n/2, b, n-n/2+1, d, c);
    FOR(i, n) if (a[i] != (c[i] + r[i]) % P) return 0;
    printf("%d ok\n", _);
  }
  return 1;
}

bool check_Ln(int n) {
  int N = polyop.nxt2k(n);
  FOR(_, 10) {
    fill(a, a+N, 0);
    fill(b, b+N, 0);
    fill(c, c+N, 0);
    fill(aa, aa+N, 0);
    fill(bb, bb+N, 0);
    fill(cc, cc+N, 0);
    FOR(i, n) a[i] = (rand() % 5) % P; a[0] = (rand() % 5) % (P-1) + 1;
    FOR(i, n) b[i] = (rand() % 5) % P; b[0] = (rand() % 5) % (P-1) + 1;
    polyop.Ln(n, a, aa);
    polyop.Ln(n, b, bb);
    polyop.Mul(n, a, n, b, c);
    polyop.Ln(n, c, cc);
    //FOR(i, n) printf("%lld ", a[i]); puts("");
    //FOR(i, n) printf("%lld ", b[i]); puts("");
    //FOR(i, n) printf("%lld ", c[i]); puts("");
    //FOR(i, n) printf("%lld ", aa[i]); puts("");
    //FOR(i, n) printf("%lld ", bb[i]); puts("");
    //FOR(i, n) printf("%lld ", cc[i]); puts("");
    FOR(i, n) if ((aa[i] + bb[i]) % P != cc[i]) return 0;
    printf("%d Ln ok\n\n", _);
  }
  return 1;
}

bool check_Ln_Exp(int n) {
  int N = polyop.nxt2k(n);
  FOR(_, 10) {
    fill(a, a+N, 0);
    fill(b, b+N, 0);
    fill(c, c+N, 0);
    FOR(i, n) a[i] = (rand()) % P; a[0] = (rand()) % (P-1) + 1;
    polyop.Ln(n, a, b);
    polyop.Exp(n, b, c);
    //FOR(i, n) printf("%lld ", a[i]); puts("");
    //FOR(i, n) printf("%lld ", b[i]); puts("");
    //FOR(i, n) printf("%lld ", c[i]); puts("");
    LL offset = a[0] * polyop.ntt.inv(c[0], P);
    FOR(i, n) if (a[i] != c[i] * offset % P) return 0;
    printf("%d Ln Exp ok\n\n", _);
  }
  return 1;
}

void solve(int k, ll f[], ll g[], ll h[]) {
  static LL lnf[MAXN], lng[MAXN], lnh[MAXN];
  polyop.Ln(k, f, lnf);
  polyop.Ln(k, g, lng);
  REP(i, 1, k-1) {
    ll coef = polyop.ntt.iv[i];
    if (!(i&1)) coef = P - coef;
    ll icoef = polyop.ntt.inv(coef, P);
    ll ai = lnf[i] * icoef % P;
    ll bi = lng[i] * icoef % P;
    lnh[i] = (ai * bi % P) * coef % P;
  }
  polyop.Exp(k, lnh, h);
}

int n, m, k;
LL f[MAXN], g[MAXN], h[MAXN];

int main() {
  R(n, m, k);
  REP(i, 0, n) R(f[i]);
  REP(i, 0, m) R(g[i]);
  solve(k, f, g, h);
  FOR(i, k) printf("%lld%c", h[i], " \n"[i+1 == k]);
  //srand(time(0) ^ 0xc2251393);
  //assert(check_Ln(100000));
  //assert(check_inv(100000));
  //assert(check_div(100000));
  //assert(check_Ln_Exp(100000));
}
