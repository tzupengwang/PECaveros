
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1010;
const int M = 1e5+10;
const int V = M*20;
const int W = 1e6;

typedef pair<int,int> pii;

struct E {
  int u, v, c;
  bool operator<(E e) const {
    return tie(c, u, v) < tie(e.c, e.u, e.v);
  }
};

int n, m;
E es[M];
vector<pii> g[N];

struct DJS {
  int mom[N];
  void init() { for (int i = 1; i <= n; ++i) mom[i] = i; }
  int find(int x) { return mom[x] = x == mom[x] ? x: find(mom[x]); }
  void uni(int x, int y) { mom[find(y)] = find(x); }
} djs;


struct Nd{
  LL sum;
  Nd *tl , *tr;
  Nd(){
    tl = tr = NULL;
    sum = 0;
  }
};
vector<Nd*> rec;
Nd* copy( Nd* x ){
  Nd* ret = new Nd();
  rec.push_back( ret );
  if( x ){
    ret->sum = x->sum;
    ret->tl = x->tl;
    ret->tr = x->tr;
  }
  return ret;
}
#define bmid ((l+r)>>1)
LL Sum( Nd* now ){ return now ? now->sum : 0; }
void modify( Nd* now , int l , int r , int p , int x ){
  if( l == r ){
    now->sum += p * x;
    return;
  }
  if( p <= bmid ){
    now->tl = copy( now->tl );
    modify( now->tl , l , bmid , p , x );
  }else{
    now->tr = copy( now->tr );
    modify( now->tr , bmid + 1 , r , p , x );
  }
  now->sum = Sum( now->tl ) + Sum( now->tr );
}
LL query( Nd* now , int l , int r , int ql , int qr ){
  if( !now or r < ql or l > qr )  return 0;
  if( ql <= l and r <= qr ) return now->sum;
  return query( now->tl , l , bmid , ql , qr ) +
         query( now->tr , bmid + 1 , r , ql , qr );
}

Nd* root[ M ];

//int rt[M], tot;
//int lc[V], rc[V];
//LL sum[V];

//int ins(int i, int l, int r, int p, int x) {
  //int res;
  //res = ++tot;
  //lc[res] = lc[i];
  //rc[res] = rc[i];
  //sum[res] = sum[i];
  //sum[res] += p*x;
  //if (l < r) {
    //int mid = (l+r) / 2;
    //if (mid <= p) lc[res] = ins(lc[i], l, mid, p, x);
    //else rc[res] = ins(rc[i], mid+1, r, p, x);
  //}
  //return res;
//}

//LL qry(int i, int l, int r, int a, int b) {
  ////printf("qry %d %d %d\n", i, l, r);
  //if (b < l || r < a || i == 0) return 0;
  //if (a <= l && r <= b) return sum[i];
  //int mid = (l+r) / 2;
  //return qry(lc[i], l, mid, a, b) + qry(rc[i], mid+1, r, a, b);
//}

void dfs(int u, int p, int tgt, E ce, int &a, int &b, int &c) {
  //printf("dfs %d %d\n", u, p);
  if (u == tgt) {
    a = ce.u;
    b = ce.v;
    c = ce.c;
    return;
  }
  for (pii e: g[u]) if (e.first != p) {
    E te = max(ce, E{u, e.first, e.second});
    dfs(e.first, u, tgt, te, a, b, c);
  }
}

inline bool repl(int u, int v, int &a, int &b, int &c) {
  if (djs.find(u) != djs.find(v)) {
    djs.uni(u, v);
    return 0;
  }
  dfs(u, -1, v, {0,0,0}, a, b, c);
  return 1;
}

int pos[W+10];

void predo() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; ++i) {
    scanf("%d%d%d", &es[i].u, &es[i].v, &es[i].c);
  }
  sort(es+1, es+1+m);
  fill(pos, pos+W+1, 0);
  for (int i = 1; i <= n; ++i) g[i].clear();
  djs.init();
  //tot = 0;
  //rt[m+1] = 0;
  root[ m + 1 ] = NULL;
  for (int i = m; i > 0; --i) {
    root[ i ] = copy( root[ i + 1 ] );

    //rt[i] = rt[i+1];
    int u, v, c;
    u = es[i].u;
    v = es[i].v;
    c = es[i].c;
    //printf("doing i=%d (%d, %d, %d)\n", i, u, v, c);
    int tu, tv, tc;
    if (repl(es[i].u, es[i].v, tu, tv, tc)) {
      //printf("  repl %d %d %d\n", tu, tv, tc);
      //printf("  ins %d %d\n", tc, -1);
      //rt[i] = ins(rt[i], 1, W, tc, -1);
      modify( root[ i ] , 1 , W , tc , -1 );

      for (int j = 0; j < (int)g[tu].size(); ++j) if (g[tu][j].first == tv) {
        swap(g[tu][j], g[tu].back());
        g[tu].pop_back();
        break;
      }
      for (int j = 0; j < (int)g[tv].size(); ++j) if (g[tv][j].first == tu) {
        swap(g[tv][j], g[tv].back());
        g[tv].pop_back();
        break;
      }
    }
    g[u].push_back({v, c});
    g[v].push_back({u, c});
    //printf("  ins %d %d\n", c, 1);
    //rt[i] = ins(rt[i], 1, W, c, 1);
    modify( root[ i ] , 1 , W , c , + 1 );
    pos[c] = i;
  }
  for (int i = W; i > 0; --i) if (!pos[i]) pos[i] = pos[i+1];
}

void solve() {
  int q;
  scanf("%d", &q);
  LL lst = 0;
  while (q--) {
    LL l, h; scanf("%lld%lld", &l, &h);
    l -= lst;
    h -= lst;
    //printf("qry %d %d at %d\n", l, h, pos[l]);
    //LL ans = qry(rt[pos[l]], 1, W, 1, h);
    LL ans = query( root[ pos[ l ] ] , 1 , W , 1 , h );
    lst = ans;
    printf("%lld\n", ans);
  }
  for( auto i : rec )
    delete i;
  rec.clear();
}

void main2() {
  predo();
  solve();
}
int main(){
  int tc;scanf("%d", &tc);
  while (tc--) main2();
}
