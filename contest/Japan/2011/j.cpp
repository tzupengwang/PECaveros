#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 55
#define FOR(i, c) for (int i = 0; i < (c); ++i)
#define REP(i, l, r) for (int i = (l); i <= (r); ++i)
const int INF = 1e9+10;
typedef pair<int, int> PII;
typedef long long LL;
int n , m, d[N] , e[ N ];
int g1[N][N], g2[N][N];
vector<int> vs[1010];
void init(){
  fill(vs, vs+1001, vector<int>());
  vs[0].push_back(1);
  vs[1000].push_back(n);
  d[n] = 0;
  e[n] = 1000;
  REP(i, 2, n-1) {
    cin >> d[i] >> e[i];
    vs[e[i]].push_back(i);
  }
  REP(i, 1, n) REP(j, 1, n) {
    g1[i][j] = g2[i][j] = INF;
  }
  REP(i, 1, n) g1[i][i] = g2[i][i] = 0;
  FOR(i, m) {
    int a, b, c;
    cin >> a >> b >> c;
    if (e[a] <= e[b]) {
      g1[a][b] = c;
    }
    if (e[a] >= e[b]) {
      g2[b][a] = c;
    }
  }
}
LL d1[N][N], d2[N][N];
LL s1[N][N], s2[N][N];
LL dpi[N][N], dpo[N][N];
LL d1S[N][N], d2S[N][N];
void solve(){
  REP(i, 1, n) REP(j, 1, n) {
    d1[i][j] = g1[i][j];
    d2[i][j] = g2[i][j];
    if (i != j) {
      d1[i][j] += d[j];
      d2[i][j] += d[j];
    }
    dpi[i][j] = INF;
    dpo[i][j] = INF;
  }
  REP(k, 1, n) REP(i, 1, n) REP(j, 1, n) {
    d1[i][j] = min(d1[i][j], d1[i][k] + d1[k][j]);
    d2[i][j] = min(d2[i][j], d2[i][k] + d2[k][j]);
  }
  REP(i, 1, n) REP(j, 1, n) {
    s1[i][j] = s2[i][j] = INF;
    REP(k, 1, n) if(e[k] < e[j]) {
      s1[i][j] = min(s1[i][j], d1[i][k] + g1[k][j]);
      s2[i][j] = min(s2[i][j], d2[i][k] + g2[k][j]);
    }
  }
  dpi[1][1] = dpo[1][1] = 0;
  vector<PII> prv{{1, 1}};
  REP(h, 1, 1000) {
    for (int u: vs[h]) for (int v: vs[h]) {
      for (auto p: prv) {
        int a, b;
        tie(a, b) = p;
        LL tmp = dpo[a][b] + s1[a][u] + s2[b][v];
        dpi[u][v] = min(dpi[u][v], tmp);
        //printf("  s1 %d %d %lld\n", a, u, s1[a][u]);
        //printf("  s1 %d %d %lld\n", b, v, s2[b][v]);
        //printf("  dpo %d %d %lld\n", a, b, dpo[a][b]);
        //printf("dpi %d %d %lld\n", u, v, dpi[u][v]);
      }
    }
    FOR(cmb, (1 << vs[h].size())) {
      vector<int> S;
      FOR(i, (int)vs[h].size()) if ((cmb>>i) & 1) {
        S.push_back(vs[h][i]);
      }
      LL fee = 0;
      for (int u: S) {
        fee += d[u];
      }
      for (int u: S) for (int v: S) {
        d1S[u][v] = g1[u][v];
        d2S[u][v] = g2[u][v];
      }
      for (int w: S) for (int u: S) for (int v: S) {
        d1S[u][v] = min(d1S[u][v], d1S[u][w] + d1S[w][v]);
        d2S[u][v] = min(d2S[u][v], d2S[u][w] + d2S[w][v]);
      }
      vector<PII> tprv;
      for (int u: S) for (int v: S) if (dpi[u][v] < INF) {
        tprv.push_back({u, v});
      }
      for (int u: S) for (int v: S) {
        for (auto p: tprv) {
          int a, b;
          tie(a, b) = p;
          dpo[u][v] = min(dpo[u][v], dpi[a][b] + d1S[a][u] + d2S[b][v] + fee);
        }
      }
    }
    for (int u: vs[h]) for (int v: vs[h]) if (dpo[u][v] < INF) {
      //printf("dpo %d %d %lld\n", u, v, dpo[u][v]);
      prv.push_back({u, v});
    }
  }
  if (dpo[n][n] >= INF) puts("-1");
  else printf("%lld\n", dpo[n][n]);
}
void clear(){
}
int main(){
  while( scanf( "%d%d" , &n , &m ) == 2 && n ){
    init();
    solve();
    clear();
  }
}
