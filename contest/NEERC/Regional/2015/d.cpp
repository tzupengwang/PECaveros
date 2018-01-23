#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

#define SZ(c) ((int)(c).size())

const int N = 50010;
const int Q = 1e5+10;

struct XD {
  int id, u, v;
};

int n, nq;

int ans[Q];

int id[N];
int di[N];
int m;
vector<int> g[N];

inline int small_side(pii &e) {
  int a = id[e.first];
  int b = id[e.second];
  if (a > b) swap(a, b);
  int cnt = b-a+1;
  int other = m - cnt + 2;
  return min(cnt, other);
}

inline void add_e(pii &e) {
  int a = id[e.first];
  int b = id[e.second];
  g[a].push_back(b);
  g[b].push_back(a);
}

void divide(pii e, vector<int>& lvs, vector<int>& rvs) {
  int a = e.first;
  int b = e.second;
  int cur = a;
  while (cur != b) {
    lvs.push_back(cur);
    cur = di[(id[cur] + 1) % m];
  }
  lvs.push_back(cur);

  cur = b;
  while (cur != a) {
    rvs.push_back(cur);
    cur = di[(id[cur] + 1) % m];
  }
  rvs.push_back(cur);
}

int d[2][N];

int vis[N], ts;
void bfs(int s, int dis[]) {
  ++ts;
  queue<int> qu;
  qu.push(s);
  dis[s] = 0;
  vis[s] = ts;
  while (SZ(qu)) {
    int u = qu.front();
    qu.pop();
    for (int v: g[u]) if (vis[v] != ts) {
      qu.push(v);
      vis[v] = ts;
      dis[v] = dis[u] + 1;
    }
  }
}

bool lft[N];
bool rgt[N];

void dq(vector<int>& vs, vector<pii>& es, vector<XD>& qs) {
  if (vs.size() <= 3 or SZ(es) <= 0) return;
  m = SZ(vs);
  //for (int u: vs) printf("%d ", u); puts("");
  //printf("  ");
  //for (auto e: es) printf("(%d, %d)", e.first, e.second); puts("");
  for (int i = 0; i < m; ++i) {
    id[vs[i]] = i;
    di[i] = vs[i];
  }

  auto pivot_e = es[0];
  int ss = small_side(pivot_e);
  for (auto e: es) if (small_side(e) > ss) {
    pivot_e = e;
    ss = small_side(e);
  }

  for (int i = 0; i < m; ++i) {
    g[i].clear();
  }
  for (int i = 0; i < m; ++i) {
    g[i].push_back((i+1)%m);
    g[i].push_back((i-1+m)%m);
  }
  for (auto e: es) {
    add_e(e);
  }

  bfs(id[pivot_e.first], d[0]);
  bfs(id[pivot_e.second], d[1]);

  for (auto q: qs) {
    ans[q.id] = min(ans[q.id], d[0][id[q.u]] + d[0][id[q.v]]);
    ans[q.id] = min(ans[q.id], d[1][id[q.u]] + d[1][id[q.v]]);
  }

  vector<int> lvs, rvs;
  vector<pii> les, res;
  vector<XD> lqs, rqs;

  divide(pivot_e, lvs, rvs);

  for (int u: vs) lft[u] = rgt[u] = 0;
  for (int u: lvs) lft[u] = 1;
  for (int u: rvs) rgt[u] = 1;

  for (pii e: es) if (e != pivot_e) {
    if (lft[e.first] and lft[e.second]) les.push_back(e);
    else res.push_back(e);
  }

  int a = pivot_e.first;
  int b = pivot_e.second;

  for (XD q: qs) {
    if (q.u != a and q.u != b and q.v != a and q.v != b) {
      if (lft[q.u] and lft[q.v]) lqs.push_back(q);
      if (rgt[q.u] and rgt[q.v]) rqs.push_back(q);
    }
  }

  dq(lvs, les, lqs);
  dq(rvs, res, rqs);

}

int main(){
#ifndef EDDY
  freopen( "distance.in" , "r" , stdin );
  freopen( "distance.out" , "w" , stdout );
#endif
  vector<pii> diags;
  scanf("%d", &n);
  for (int i = 0; i < n-3; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    diags.push_back({u,v});
  }
  vector<XD> qs;
  scanf("%d", &nq);
  for (int i = 0; i < nq; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    qs.push_back({i, u, v});
    ans[i] = min(abs(u-v), n-abs(u-v));
  }
  vector<int> vs;
  for (int i = 1; i <= n; ++i) vs.push_back(i);

  dq(vs, diags, qs);
  //puts("");

  for (int i = 0; i < nq; ++i) {
    printf("%d\n", ans[i]);
  }
}
