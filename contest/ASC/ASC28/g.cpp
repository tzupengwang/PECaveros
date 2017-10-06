#include <bits/stdc++.h>
using namespace std;
const int MXN = 1e4+10;
#define PB push_back
struct Scc{
  int n, nScc, vst[MXN], bln[MXN];
  vector<int> E[MXN], rE[MXN], vec;
  void init(int _n){
    n = _n;
    for (int i=0; i<MXN; i++){
      E[i].clear();
      rE[i].clear();
    }
  }
  void add_edge(int u, int v){
    E[u].PB(v);
    rE[v].PB(u);
  }
  void DFS(int u){
    vst[u]=1;
    for (auto v : E[u])
      if (!vst[v]) DFS(v);
    vec.PB(u);
  }
  void rDFS(int u){
    vst[u] = 1;
    bln[u] = nScc;
    for (auto v : rE[u])
      if (!vst[v]) rDFS(v);
  }
  void solve(){
    nScc = 0;
    vec.clear();
    fill(vst, vst+n, 0);
    for (int i=0; i<n; i++)
      if (!vst[i]) DFS(i);
    reverse(vec.begin(),vec.end());
    fill(vst, vst+n, 0);
    for (auto v : vec){
      if (!vst[v]){
        rDFS(v);
        nScc++;
      }
    }
  }
};
struct SAT2 {
  int n;
  Scc scc;
  int x[MXN];
  inline int neg(int i) {
    if (i > n) return i - n;
    else return i + n;
  }
  void init(int _n) {
    n = _n;
    scc.init(2 * n);
    fill(x, x+n+1, 0);
  }
  void add_cls(int a, int b) {
    scc.add_edge(neg(a) - 1, b - 1);
    scc.add_edge(neg(b) - 1, a - 1);
  }
  void add_cls2(int a, int b) {
    add_cls(neg(a), neg(b));
  }
  bool solve() {
    scc.solve();
    for (int i = 1; i <= n; ++i) {
      int u = i-1;
      int v = neg(i)-1;
      if (scc.bln[u] == scc.bln[v]) return 0;
      x[i] = scc.bln[u] > scc.bln[v];
    }
    return 1;
  }
} sat2;
const int N = 444;

int n, m;
int a[N];
int ph[N][N];
int r[N][2];
bool bad[N][N];

void fail() {
  puts("NO");
  exit(0);
}

int main(){
#ifdef ONLINE_JUDGE
  freopen( "show.in" , "r" , stdin );
  freopen( "show.out" , "w" , stdout );
#endif
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", a+i);
  }
  scanf("%d", &m);
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      scanf("%d", ph[i]+j);
    }
  }
  for (int i = 1; i <= m; ++i) {
    for (int j = i; j <= m; ++j) {
      bad[i][j] = bad[j][i] = 0;
      for (int k = 1; k <= n; ++k) {
        if (ph[i][k] == ph[j][k]) {
          bad[i][j] = bad[j][i] = 1;
          break;
        }
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) if (ph[j][i] == a[i]) {
      r[i][0] = j;
      break;
    }
    for (int j = m; j >= 1; --j) if (ph[j][i] == a[i]) {
      r[i][1] = j;
      break;
    }
    if (r[i][0] == 0) fail();
  }
  sat2.init(n+n);
  for (int i = 1; i <= n; ++i) {
    // r[i][0] : i
    // r[i][1] : i + n
    sat2.add_cls(i, i+n);
    for (int j = i + 1; j <= n; ++j) {
      if (bad[r[i][0]][r[j][0]])
        sat2.add_cls2(i, j);
      if (bad[r[i][0]][r[j][1]])
        sat2.add_cls2(i, j + n);
      if (bad[r[i][1]][r[j][0]])
        sat2.add_cls2(i + n, j);
      if (bad[r[i][1]][r[j][1]])
        sat2.add_cls2(i + n, j + n);
    }
  }
  if (!sat2.solve()) fail();
  puts("YES");
  for (int i = 1; i <= n; ++i) {
    if (sat2.x[i]) printf("%d", r[i][0]);
    else if (sat2.x[i + n]) printf("%d", r[i][1]);
    printf("%c", " \n"[ i == n ]);
  }
}
