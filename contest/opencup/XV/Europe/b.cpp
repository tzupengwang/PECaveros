
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

const int N = 3e5+10;

#define X first
#define Y second

int n, m;
pii buf[N], fen[N];

struct XD {
  int x, y, id, tp;
  bool operator<(const XD& xd) const {
    return tie(x, y, tp) > tie(xd.x, xd.y, xd.tp);
  }
};

int cnt[N], nxt[N];
int mom[N];

int find(int x) {
  if (mom[x] == x) return x;
  return mom[x] = find(mom[x]);
}

void merge(int a, int b) {
  //printf("merge %d %d\n", a, b);
  a = find(a);
  b = find(b);
  if (a == b) return;
  mom[a] = b;
  cnt[b] += cnt[a];
}

void predo() {
  vector<XD> events;
  REP(i, 1, n) {
    events.push_back({buf[i].X, buf[i].Y, i, 1});
  }
  REP(i, 1, m) {
    events.push_back({fen[i].X, fen[i].Y, i, 2});
  }
  sort(ALL(events));
  set<pii> active_fen;
  for (XD xd: events) {
    if (xd.tp == 1) {
      auto it = active_fen.lower_bound({xd.y, -1});
      if (it != active_fen.end()) {
        //printf("buf %d -> fen %d\n", xd.id, it->second);
        cnt[it->second]++;
      }
    } else {
      {
        auto it = active_fen.upper_bound({xd.y, -1});
        if (it != active_fen.end()) {
          //printf("nxt %d %d\n", xd.id, it->second);
          nxt[xd.id] = it->second;
        }
      }
      {
        auto it = active_fen.upper_bound({xd.y, -1});
        vector<pii> del;
        while (it != active_fen.begin()) {
          it--;
          if (xd.id < it->second) {
            del.push_back(*it);
          } else {
            break;
          }
        }
        for (auto p: del) active_fen.erase(p);
      }

      active_fen.insert({xd.y, xd.id});
    }
  }
}

int ans[N];

void solve() {
  REP(i, 1, m) mom[i] = i;
  REPD(i, m, 1) {
    ans[i] = cnt[find(i)];
    merge(i, nxt[i]);
  }
  REP(i, 1, m) printf("%d\n", ans[i]);
}

int main() {
  R(n);
  REP(i, 1, n) R(buf[i].X, buf[i].Y);
  R(m);
  REP(i, 1, m) R(fen[i].X, fen[i].Y);
  predo();
  solve();
}
