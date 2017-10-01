#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> PII;
typedef long long LL;

const int N = 44;
const int P = 22;
const int TH = 21;

int n, m;
vector<PII> g[N];
LL adj[2][N];

inline int bit(LL x, int i) {
  return (x>>i) & 1;
}

namespace S1 {

int id[N], di[N];
LL fix[(1<<P)];
int dp[(1<<P)+5], prv[(1<<P)+5];

void init() {
  int k = g[0].size();
  for (int i = 0; i < k; ++i) {
    id[i] = g[0][i].first;
    di[id[i]] = i;
    if (g[0][i].second == 1) {
      swap(adj[0][id[i]], adj[1][id[i]]);
    }
  }

  fix[0] = 0;
  for (int cmb = 0; cmb < (1<<k); ++cmb) {
    fix[cmb] = (adj[0][0] | adj[1][0]);
    for (int i = 0; i < k; ++i) if (bit(cmb, i)) {
      fix[cmb] |= (adj[0][id[i]] | adj[1][id[i]]);
    }
  }
}

void solve() {
  init();
  int k = g[0].size();
  dp[0] = 0;
  for (int cmb = 0; cmb < (1<<k); ++cmb) {
    for (int i = 0; i < k; ++i) if ((cmb >> i)&1) {
      int pcmb = cmb ^ (1<<i);
      LL pfix = fix[pcmb];
      LL newf = adj[0][id[i]];

      int inc = __builtin_popcountll(newf & (~pfix));
      if (dp[cmb] < dp[pcmb] + inc) {
        prv[cmb] = i;
        dp[cmb] = dp[pcmb] + inc;
      }
    }
  }
  int S = max_element(dp, dp + (1<<k)) - dp;
  vector<int> ans;
  int cur = S;
  while (cur) {
    int i = prv[cur];
    ans.push_back(id[i]);
    cur ^= (1 << i);
  }
  reverse(ans.begin(), ans.end());
  int ac = dp[S] + __builtin_popcountll(adj[0][0]);
  printf("%d %d\n", ac, S);
  printf("%.9f\n", 1. * ac / (n-1));
  for (size_t i = 0; i < ans.size(); ++i) {
    printf("%d%c", ans[i] + 1, " \n"[i + 1 == ans.size()]);
  }
}

}

namespace S2 {

int id[N], di[N];
int k;
int prv[(1<<P)];
bool dp[(1<<P)];

void solve() {
  dp[0] = 1;
  for (int cmb = 0; cmb < (1<<P); ++cmb) {
  }

}

}

int main() {
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int u, v, e;
    cin >> u >> v >> e;
    --u, --v;
    g[u].push_back({v, e});
    g[v].push_back({u, e});
    adj[e][u] |= (1<<v);
    adj[e][v] |= (1<<u);
  }

  if (g[0].size() == 0) {
    printf("0\n\n");
    return 0;
  }
  if (g[0].size() <= TH) S1::solve();
  else S2::solve();
}
