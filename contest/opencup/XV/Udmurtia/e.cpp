
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

struct MinCostMaxFlow{
typedef int Tcost;
  static const int MAXV = 20010;
  static const int INFf = 1000000;
  static const Tcost INFc  = 1e9;
  struct Edge{
    int v, cap;
    Tcost w;
    int rev;
    Edge(){}
    Edge(int t2, int t3, Tcost t4, int t5)
    : v(t2), cap(t3), w(t4), rev(t5) {}
  };
  int V, s, t;
  vector<Edge> g[MAXV];
  void init(int n){
    V = n+2;
    s = n+1, t = n+2;
    for(int i = 0; i <= V; i++) g[i].clear();
  }
  void addEdge(int a, int b, int cap, Tcost w){
    g[a].push_back(Edge(b, cap, w, (int)g[b].size()));
    g[b].push_back(Edge(a, 0, -w, (int)g[a].size()-1));
  }
  Tcost d[MAXV];
  int id[MAXV], mom[MAXV];
  bool inqu[MAXV];
  queue<int> q;
  Tcost solve(){
    int mxf = 0; Tcost mnc = 0;
    while(1){
      fill(d, d+1+V, INFc);
      fill(inqu, inqu+1+V, 0);
      fill(mom, mom+1+V, -1);
      mom[s] = s;
      d[s] = 0;
      q.push(s); inqu[s] = 1;
      while(q.size()){
        int u = q.front(); q.pop();
        inqu[u] = 0;
        for(int i = 0; i < (int) g[u].size(); i++){
          Edge &e = g[u][i];
          int v = e.v;
          if(e.cap > 0 && d[v] > d[u]+e.w){
            d[v] = d[u]+e.w;
            mom[v] = u;
            id[v] = i;
            if(!inqu[v]) q.push(v), inqu[v] = 1;
          }
        }
      }
      if(mom[t] == -1) break ;
      int df = INFf;
      for(int u = t; u != s; u = mom[u])
        df = min(df, g[mom[u]][id[u]].cap);
      for(int u = t; u != s; u = mom[u]){
        Edge &e = g[mom[u]][id[u]];
        e.cap             -= df;
        g[e.v][e.rev].cap += df;
      }
      mxf += df;
      mnc += df*d[t];
    }
    return mnc;
  }
} flow;

inline int bit(int x, int i) {
  return (x>>i)&1;
}

const int N = 20;
const int K = 222;
const int MX = 5000;
const int TH = 220;

typedef pair<int,int> pii;
typedef pair<int, pii> Dat;

int dx[] = {0, -1, 0, 1};
int dy[] = {1, 0, -1, 0};

int n, k, ix[N], iy[N], c[K];

void input() {
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", ix+i, iy+i);
  }
  for (int i = 0; i < k; ++i) scanf("%d", c+i);
}

bool ban[MX+5][MX+5];
set<pii> cand[N];
priority_queue<Dat, vector<Dat>, greater<Dat>> pq[N];
int ta[MX];

inline int kdis(int tk, int x, int y) {
  for (int i = 0; i < n; ++i)
    ta[i] = abs(x-ix[i]) + abs(y-iy[i]);
  sort(ta, ta+n);
  int res = 0;
  for (int i = 0; i < tk; ++i) res += ta[i];
  return res;
}

int vis[MX+5][MX+5];

void expand(int tk, pii p) {
  int cx, cy; tie(cx, cy) = p;
  for (int t = 0; t < 4; ++t) {
    int tx = cx+dx[t];
    int ty = cy+dy[t];
    if (0 <= tx && tx <= MX && 0 <= ty && ty <= MX) {
      if (vis[tx][ty] != tk) {
        vis[tx][ty] = tk;
        int td = kdis(tk, tx, ty);
        pq[tk].push({td, {tx, ty}});
      }
    }
  }
}

void predo() {
  for (int i = 0; i < n; ++i) ban[ix[i]][iy[i]] = 1;
  for (int msk = 1; msk < (1<<n); ++msk) {
    int tk = __builtin_popcount(msk);
    int t = 0;
    for (int i = 0; i < n; ++i) if (bit(msk, i)) ta[t++] = ix[i];
    sort(ta, ta+t);
    int cx = ta[t/2];
    t = 0;
    for (int i = 0; i < n; ++i) if (bit(msk, i)) ta[t++] = iy[i];
    sort(ta, ta+t);
    int cy = ta[t/2];
    pq[tk].push({kdis(tk, cx, cy), {cx, cy}});
  }
  //puts("pq done");
  for (int tk = 1; tk <= n; ++tk) {
    //printf("tk %d\n", tk);
    while (pq[tk].size() and cand[tk].size() < TH) {
      int _; pii p;
      tie(_, p) = pq[tk].top(); pq[tk].pop();
      if (!ban[p.first][p.second]) {
        cand[tk].insert(p);
      }
      expand(tk, p);
    }
  }
}

map<pii, int> pid;
int m;
int cnt[N];

void solve() {
  for (int tk = 1; tk <= n; ++tk) {
    for (auto p: cand[tk]) if (!pid.count(p)) {
      pid[p] = ++m;
    }
  }
  for (int i = 0; i < k; ++i) cnt[c[i]]++;
  flow.init(n + m);
  for (int tk = 1; tk <= n; ++tk) {
    flow.addEdge(flow.s, tk, cnt[tk], 0);
    for (auto p: cand[tk]) {
      int id = pid[p];
      int x = p.first;
      int y = p.second;
      flow.addEdge(tk, n+id, 1, kdis(tk, x, y));
    }
  }
  for (auto pp: pid) {
    flow.addEdge(n+pp.second, flow.t, 1, 0);
  }
  int ans = flow.solve();
  cout << ans << endl;
}

int main(){
  input();
  predo();
  solve();
}
