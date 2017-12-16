
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

const int N = 2e5+10;
const int MX = 27;

inline int enc(char c) {
  switch(c) {
    case 'r':
      return 1;
    case 'a':
      return 2;
    case 't':
      return 3;
  }
  return -1;
}

inline ll enc(char *s, int len) {
  ll res = 0;
  FOR(i, len) {
    if (!s[i]) break;
    res = res * 4 + enc(s[i]);
  }
  return res;
}

struct LI {
  vector<int> xs;
  void init() {
    sort(ALL(xs));
    xs.resize(unique(ALL(xs)) - xs.begin());
  }
  int get(int x) {
    return lower_bound(ALL(xs), x) - xs.begin();
  }
} li;

struct SEGT {
#define L(X) ((X)<<1)
#define R(X) (1|((X)<<1))
#define mid ((l+r)>>1)
  int cov[N<<3];
  void push(int id) {
    if (cov[id] != -1) {
      cov[L(id)] = cov[R(id)] = cov[id];
    }
    cov[id] = -1;
  }
  void upd(int id, int l, int r, int a, int b, int x) {
    if (a > b) return;
    if (b < l || r < a) return;
    if (a <= l && r <= b) {
      cov[id] = x;
      return;
    }
    push(id);
    upd(L(id), l, mid, a, b, x);
    upd(R(id), mid+1, r, a, b, x);
  }
  int get(int id, int l, int r, int p) {
    if (l == r) return cov[id];
    if (cov[id] != -1) return cov[id];
    if (p <= mid) return get(L(id), l, mid, p);
    else return get(R(id), mid+1, r, p);
  }
#undef L
#undef R
#undef mid
} segt;

int n, m, q;
pii ip[N];
int r[N];
char ch[N];
map<pii, int> id;
int mom[N];
int dep[N];

void init_tree() {
  R(n);
  REP(i, 1, n) {
    int x, y;char s[2];
    R(x, y, r[i], s);
    ip[i] = {x, y};
    id[{x, y}] = i;
    ch[i] = *s;
  }
  vector<pii> events;
  REP(i, 1, n) {
    events.push_back({ip[i].first - r[i], i});
    events.push_back({ip[i].first + r[i], -i});
    li.xs.push_back(ip[i].second + r[i]);
    li.xs.push_back(ip[i].second - r[i]);
  }
  li.init();
  sort(ALL(events));
  for (auto p: events) {
    int i = abs(p.second);
    //printf("event %d\n", i);
    if (p.second > 0) {
      int L = li.get(ip[i].second - r[i]);
      int R = li.get(ip[i].second + r[i]) - 1;
      mom[i] = segt.get(1, 0, SZ(li.xs)-1, L);
      dep[i] = 1 + dep[mom[i]];
      assert(dep[i] <= MX);
      //printf("%d %d %d\n", L, R, i);
      segt.upd(1, 0, SZ(li.xs)-1, L, R, i);
    } else {
      int L = li.get(ip[i].second - r[i]);
      int R = li.get(ip[i].second + r[i]) - 1;
      //printf("%d %d %d\n", L, R, mom[i]);
      segt.upd(1, 0, SZ(li.xs)-1, L, R, mom[i]);
    }
  }
  //REP(i, 1, n) printf("%d -> %d\n", i, mom[i]);
}

char s[N];
#include <bits/extc++.h>
using namespace __gnu_pbds;
#include <ext/pb_ds/assoc_container.hpp>
typedef cc_hash_table<ll,int> umap_t;
//unordered_map<ll, int> cnt;
umap_t cnt;

void init_str() {
  R(m);
  FOR(i, m) {
    R(s);
    int tlen = strlen(s);
    umap_t subs;
    FOR(j, tlen) {
      int mxlen = min(MX, tlen - j);
      REP(l, 1, mxlen) {
        subs[enc(s+j, l)] = 1;
        //subs.insert(enc(s+j, l));
      }
    }
    for (auto p: subs) ++cnt[p.first];
    //for (ll hsh: subs) ++cnt[hsh];
  }
}

void init() {
  init_tree();
  init_str();
}

bool act[N];

inline int qry(int u) {
  static char str[N];
  int i = 0;
  while (u > 0) {
    if (act[u]) str[i++] = ch[u];
    u = mom[u];
  }
  str[i] = 0;
  reverse(str, str+i);
  //printf("%d %s\n", u, str);
  ll hsh = enc(str, i);
  return cnt[hsh];
}

void solve() {
  fill(act, act+n+1, 1);
  R(q);
  while (q--) {
    char tp[2]; int x;
    R(tp, x);
    switch (*tp) {
      case '+':
        act[x] = 1;
        break;
      case '-':
        act[x] = 0;
        break;
      case '?':
        printf("%d\n", qry(x));
    }
  }
}

int main() {
  init();
  solve();
}
