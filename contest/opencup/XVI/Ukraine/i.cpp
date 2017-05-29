
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

const int MAXM = 1000010;
struct SAM{
  int tot, root, lst, mom[MAXM], mx[MAXM];
  int acc[MAXM], nxt[MAXM][33];
  int newNode(){
    int res = ++tot;
    fill(nxt[res], nxt[res]+33, 0);
    mom[res] = mx[res] = acc[res] = 0;
    return res;
  }
  void init(){
    tot = 0;
    root = newNode();
    mom[root] = 0, mx[root] = 0;
    lst = root;
  }
  void push(int c){
    int p = lst;
    int np = newNode();
    mx[np] = mx[p]+1;
    for(; p && nxt[p][c] == 0; p = mom[p])
      nxt[p][c] = np;
    if(p == 0) mom[np] = root;
    else{
      int q = nxt[p][c];
      if(mx[p]+1 == mx[q]) mom[np] = q;
      else{
        int nq = newNode();
        mx[nq] = mx[p]+1;
        for(int i = 0; i < 33; i++)
          nxt[nq][i] = nxt[q][i];
        mom[nq] = mom[q];
        mom[q] = nq;
        mom[np] = nq;
        for(; p && nxt[p][c] == q; p = mom[p])
          nxt[p][c] = nq;
      }
    }
    lst = np;
  }
  void push(char *str){
    for(int i = 0; str[i]; i++)
      push(str[i]-'a'+1);
  }
} sam;


typedef set<pii> set_t;

const int N = 2e5+10;
const int L = 20;

char ip[N];
int pos[N];
int mom[L][N];
vector<int> ch[N];
int tL[N], tR[N], timestamp;

void dfs(int u) {
  tL[u] = ++timestamp;
  for (int v: ch[u]) dfs(v);
  tR[u] = timestamp;
}

void predo() {
  sam.init();
  sam.push( ip );
  int cur = sam.root;
  FOR( i , N ) {
    int c = ip[i] - 'a' + 1;
    cur = sam.nxt[cur][c];
    pos[i] = cur;
  }
  REP( i , 1 , sam.tot ) {
    mom[0][i] = sam.mom[i];
    ch[mom[0][i]].push_back(i);
  }
  FOR( j , L-1 ) REP( i , 1 , sam.tot ) {
    mom[j+1][i] = mom[j][mom[j][i]];
  }
  dfs(1);
}

inline pii tran(int x, int p) {
  int cur = pos[p];
  REPD( j , L-1 , 0 ) {
    int tn = mom[j][cur];
    if ( sam.mx[tn] >= x ) cur = tn;
  }
  return {x, cur};
}

set_t dat[N<<2];

void ins( int id , int l , int r , int i , pii p ) {
  dat[id].insert(p);
  if ( l == r ) return;
  int mid = (l+r)/2;
  if ( i <= mid ) ins( id*2 , l , mid , i , p );
  else ins( id*2+1 , mid+1 , r , i , p );
}

void del( int id , int l , int r , int i , pii p ) {
  if ( dat[id].count(p) ) dat[id].erase(p);
  if ( l == r ) return;
  int mid = (l+r)/2;
  if ( i <= mid ) del( id*2 , l , mid , i , p );
  else del( id*2+1 , mid+1 , r , i , p );
}

void qry( int id , int l , int r , int a , int b , vector<pair<set_t::iterator,int>>& its , int mn ) {
  if ( b < l || r < a ) return;
  if ( a <= l && r <= b ) {
    its.push_back( { dat[id].lower_bound({mn, -1}) , id } );
    return;
  }
  int mid = (l+r)/2;
  qry( id*2 , l , mid , a , b , its , mn );
  qry( id*2+1 , mid+1 , r , a , b , its , mn );
}

inline void calc( int X , int P , pii pa , int K ) {
  static vector<pair<set_t::iterator,int>> its;
  static priority_queue<pii> pq;
  its.clear();
  while ( !pq.empty() ) pq.pop();
  int ans = -1;
  qry( 1 , tL[1] , tR[1] , tL[pa.second] , tR[pa.second] , its , X );
  FOR( i , SZ( its ) ) {
    auto p = its[i];
    auto it = p.first;
    int id = p.second;
    if ( it != dat[id].end() ) {
      pq.push( { -(it->first) , i } );
    }
  }
  FOR(_, K-1) {
    if ( !SZ( pq ) ) break;
    auto tp = pq.top();pq.pop();
    int i = tp.second;
    its[i].first++;
    if ( its[i].first != dat[its[i].second].end() ) {
      pq.push( { -(its[i].first->first) , i } );
    }
  }
  if ( SZ( pq ) ) {
    ans = -pq.top().first;
  }
  printf("%d\n", ans);
}

void solve() {
  int q;R(q);
  while (q--) {
    int tp , x , p; R(tp , x , p);
    pii pa = tran( x , p );
    if ( tp == 1 ) {
      ins( 1 , tL[1] , tR[1] , tL[pa.second] , pa );
    } else if ( tp == 2 ) {
      del( 1 , tL[1] , tR[1] , tL[pa.second] , pa );
    } else {
      int K;R( K );
      calc( x , p , pa , K );
    }
  }
}

int main() {
  R(ip);
  predo();
  solve();
}
