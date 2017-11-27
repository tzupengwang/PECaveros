
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

const int N = 1e5+10;

int n, a[N], q;
struct Q {
  int l, r, i;
  void read(int id) {
    R(l, r);
    i = id;
  }
} qs[N];
pii ans[N];

int iv[N];

pii merge(pii x, pii y) {
  return {min(x.first, y.first), max(x.second, y.second)};
}

struct SPT {
  int sz;
  pii dat[20][N];
  int lg[N];
  void init(int _sz, int *arr) {
    sz = _sz;
    REP(i, 1, sz) dat[0][i] = {arr[i], arr[i]};
    lg[1] = 0;
    REP(i, 2, sz) lg[i] = 1 + lg[i/2];
    FOR(j, 19) REP(i, 1, sz) {
      int nxt = i+(1<<j);
      if (nxt > sz) nxt = i;
      dat[j+1][i] = merge(dat[j][i], dat[j][nxt]);
    }
  }
  pii qry(int l, int r) {
    int j = lg[r-l+1];
    pii res = merge(dat[j][l], dat[j][r-(1<<j)+1]);
    return res;
  }
} st1, st2;

inline pii expand(int l, int r, int xl=0, int xr=N) {
  while (1) {
    int mn, mx;
    tie(mn, mx) = st1.qry(l, r);
    if (mx-mn+1 == r-l+1) break;
    tie(l, r) = st2.qry(mn, mx);
    if (l < xl or xr < r) return {-1, -1};
  }
  return {l, r};
}

void predo() {
  REP(i, 1, n) iv[a[i]] = i;
  st1.init(n, a);
  st2.init(n, iv);
}

inline void update(int i, pii it) {
  if (it.first == -1 or it.second == -1) return;
  if (it.second - it.first + 1 < ans[i].second - ans[i].first + 1)
    ans[i] = it;
}

void dq(int l, int r, vector<Q> &cqs) {
  static pii itv[N];
  if (l >= r) return;
  int mid = (l+r) / 2;
  vector<Q> lq, rq;
  for (Q& qq: cqs)
    if (qq.r <= mid) lq.push_back(qq);
    else if(mid < qq.l) rq.push_back(qq);
  dq(l, mid, lq);
  dq(mid+1, r, rq);

  {
    int tl = mid+1, tr = mid+1;
    REPD(i, mid, l) {
      // expand [i, mid+1]
      if (tl != -1 and i < tl) {
        tie(tl, tr) = expand(i, tr, l, r);
      }
      itv[i] = {tl, tr};
    }
  }
  {
    int tl = mid, tr = mid;
    REP(i, mid+1, r) {
      // expand [mid, i]
      if (tl != -1 and tr < i) {
        tie(tl, tr) = expand(tl, i, l, r);
      }
      itv[i] = {tl, tr};
    }
  }

  for (Q& qq: cqs) {
    if (qq.r <= mid) {
      update(qq.i, itv[qq.l]);
    } else if (mid < qq.l) {
      update(qq.i, itv[qq.r]);
    } else {
      update(qq.i, merge(itv[qq.l], itv[qq.r]));
    }
  }
  return;
}

void solve() {
  //REP(i, 1, q) {
    //ans[i] = expand(qs[i].l, qs[i].r);
    //printf("%d %d\n", ans[i].first, ans[i].second);
  //}
  //return;
  vector<Q> allq;
  REP(i, 1, q) allq.push_back(qs[i]);
  dq(1, n, allq);
  REP(i, 1, q) {
    //ans[i] = expand(qs[i].l, qs[i].r);
    printf("%d %d\n", ans[i].first, ans[i].second);
  }
}

int main() {
  R(n);
  REP(i, 1, n) R(a[i]);
  R(q);
  REP(i, 1, q) qs[i].read(i);

  REP(i, 1, q)
    if (qs[i].l == qs[i].r) ans[i] = {qs[i].l, qs[i].l};
    else ans[i] = {1, n};

  predo();
  solve();
}
