
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXM = 200010;
struct SAM{
  int tot, root, lst, mom[MAXM], mx[MAXM];
  int acc[MAXM], nxt[MAXM][33];
  int newNode(){
    tot++;
    int res = tot;
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
#define SZ(c) (int)(c).size()
#define ALL(c) (c).begin(), (c).end()
#define REP(i, s, e) for(int i = (s); i <= (e); i++)
#define REPD(i, s, e) for(int i = (s); i >= (e); i--)
typedef tuple< int , int > tii;
const int MAXN = 200010;
const int LOG  = 19;
struct HLD{
  int n;
  vector<int> g[MAXN];
  int sz[MAXN], dep[MAXN];
  int ts, tid[MAXN], tdi[MAXN], tl[MAXN], tr[MAXN];
  //  ts : timestamp , useless after yutruli
  //  tid[ u ] : pos. of node u in the seq.
  //  tdi[ i ] : node at pos i of the seq.
  //  tl , tr[ u ] : subtree interval in the seq. of node u
  int mom[MAXN][LOG], head[MAXN];
  // head[ u ] : head of the chain contains u
  void dfssz(int u, int p){
    dep[u] = dep[p] + 1;
    mom[u][0] = p;
    sz[u] = 1;
    head[u] = u;
    for(int& v:g[u]) if(v != p){
      dep[v] = dep[u] + 1;
      dfssz(v, u);
      sz[u] += sz[v];
    }
  }
  void dfshl(int u){
    //printf("dfshl %d\n", u);
    ts++;
    tid[u] = tl[u] = tr[u] = ts;
    tdi[tid[u]] = u;
    sort(ALL(g[u]),
         [&](int a, int b){return sz[a] > sz[b];});
    bool flag = 1;
    for(int& v:g[u]) if(v != mom[u][0]){
      if(flag) head[v] = head[u], flag = 0;
      dfshl(v);
      tr[u] = tr[v];
    }
  }
  inline int lca(int a, int b){
    if(dep[a] > dep[b]) swap(a, b);
    //printf("lca %d %d\n", a, b);
    int diff = dep[b] - dep[a];
    REPD(k, LOG-1, 0) if(diff & (1<<k)){
      //printf("b %d\n", mom[b][k]);
      b = mom[b][k];
    }
    if(a == b) return a;
    REPD(k, LOG-1, 0) if(mom[a][k] != mom[b][k]){
      a = mom[a][k];
      b = mom[b][k];
    }
    return mom[a][0];
  }
  void init( int _n ){
    n = _n;
    REP( i , 1 , n ) g[ i ].clear();
  }
  void addEdge( int u , int v ){
    g[ u ].push_back( v );
    g[ v ].push_back( u );
  }
  void yutruli(){
    dfssz(1, 0);
    ts = 0;
    dfshl(1);
    REP(k, 1, LOG-1) REP(i, 1, n)
      mom[i][k] = mom[mom[i][k-1]][k-1];
  }
  vector< tii > getPath( int u , int v ){
    vector< tii > res;
    while( tid[ u ] < tid[ head[ v ] ] ){
      res.push_back( tii(tid[ head[ v ] ] , tid[ v ]) );
      v = mom[ head[ v ] ][ 0 ];
    }
    res.push_back( tii( tid[ u ] , tid[ v ] ) );
    reverse( ALL( res ) );
    return res;
    /*
     * res : list of intervals from u to v
     * u must be ancestor of v
     * usage :
     * vector< tii >& path = tree.getPath( u , v )
     * for( tii tp : path ) {
     *   int l , r;tie( l , r ) = tp;
     *   upd( l , r );
     *   uu = tree.tdi[ l ] , vv = tree.tdi[ r ];
     *   uu ~> vv is a heavy path on tree
     * }
     */
  }
} tree;
const int N = 2e5+10;

struct SEG {
  LL add[N<<2], s0[N<<2], s1[N<<2], s2[N<<2];
#define lc(i) ((i)*2)
#define rc(i) ((i)*2+1)
#define mid ((l+r)/2)
  void init(int i, int l, int r, int *a) {
    if (l == r) {
      s0[i] = a[l];
      return;
    }
    init(lc(i), l, mid, a);
    init(rc(i), mid+1, r, a);
    s0[i] = s0[lc(i)] + s0[rc(i)];
  }
  void ADD(int i, LL x) {
    add[i] += x;
    s2[i] += 2*x*s1[i] + x*x*s0[i];
    s1[i] += x*s0[i];
  }
  void push(int i) {
    ADD(lc(i), add[i]);
    ADD(rc(i), add[i]);
    add[i] = 0;
  }
  void inc(int i, int l, int r, int a, int b) {
    if (r < a || b < l) return;
    if (a <= l && r <= b) {
      ADD(i, 1);
      return;
    }
    push(i);
    inc(lc(i), l, mid, a, b);
    inc(rc(i), mid+1, r, a, b);
    s1[i] = s1[lc(i)] + s1[rc(i)];
    s2[i] = s2[lc(i)] + s2[rc(i)];
  }
} seg;

int n;
char ip[N];
int state[N], len[N];

int main(){
  scanf("%s", ip+1);
  n = strlen(ip+1);

  sam.init();
  for (int i = 1; i <= n; ++i) {
    sam.push(ip[i] - 'a' + 1);
  }

  //printf("tot %d\n", sam.tot);

  tree.init(sam.tot);
  for (int i = 1; i <= sam.tot; ++i) {
    int p = sam.mom[i];
    //printf("ae %d %d\n", p, i);
    if (p) {
      tree.addEdge(p, i);
    }
  }
  tree.yutruli();
  for (int i = 1; i <= sam.tot; ++i) {
    int p = sam.mom[i];
    len[tree.tid[i]] = sam.mx[i] - sam.mx[p];
    //printf("len %d %d %d\n", i, tree.tid[i], len[tree.tid[i]]);
  }

  seg.init(1, 1, sam.tot, len);

  for (int i = 1, np = 1; i <= n; ++i) {
    int c = ip[i] - 'a' + 1;
    np = sam.nxt[np][c];
    state[i] = np;
  }

  LL ans = 0;
  for (int i = 1; i <= n; ++i) {
    auto path = tree.getPath(1, state[i]);
    for (tii tp: path) {
      int l, r;tie(l,r) = tp;
      //printf("inc %d %d\n", l, r);
      seg.inc(1, 1, sam.tot, l, r);
    }
    ans = seg.s2[1];
    printf("%lld\n", ans);
    /*
     * vector< tii >& path = tree.getPath( u , v )
     * for( tii tp : path ) {
     *   int l , r;tie( l , r ) = tp;
     *   upd( l , r );
     *   uu = tree.tdi[ l ] , vv = tree.tdi[ r ];
     *   uu ~> vv is a heavy path on tree
     * }
     * 
     */
  }

}
