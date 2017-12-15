#include <bits/stdc++.h>
using namespace std;

#define SZ(c) ((int)(c).size())

const int N = 2e5+10;
const int SQ = 555;

int B;

int n, k, q;
int c[N];
vector<int> pos[N];
int light[N];

void init() {
  scanf("%d%d%d", &n, &k, &q);
  B = min(n, int(sqrt(n)+2));
  //B = 2;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", c+i);
    pos[c[i]].push_back(i);
  }
  fill(light, light+1+k, -1);
}

int ans1, ans2;
int big_ans[N];
int big_in[N];
int cb;
int bid[N], adj[SQ][SQ];
int dib[N];

inline bool isbig(int col) {
  return SZ(pos[col]) >= B;
}

inline void upd(int col) {
  ans1 += light[col] * SZ(pos[col]);
  if (not isbig(col)) {
    for (int i: pos[col]) {
      if (0 < i and c[i-1] != col) {
        if (light[c[i-1]] > 0) {
          ans2 += light[col];
        }
        if (isbig(c[i-1])) big_ans[c[i-1]] += light[col];
      }
      if (0 < i and c[i-1] == col) {
        ans2 += light[col];
      }
      if (i < n and c[i+1] != col) {
        if (light[c[i+1]] > 0) ans2 += light[col];
        if (isbig(c[i+1])) big_ans[c[i+1]] += light[col];
      }
    }
  } else {
    ans2 += light[col] * big_in[col];
    ans2 += light[col] * big_ans[col];
    for (int i = 1; i <= cb; ++i) if (i != bid[col]) {
      if (light[dib[i]] > 0) {
        ans2 += light[col] * adj[i][bid[col]];
      }
    }
  }
}

void solve() {
  for (int i = 1; i <= n; ++i) if (isbig(c[i]) and !bid[c[i]]) {
    bid[c[i]] = ++cb;
    dib[bid[c[i]]] = c[i];
  }
  for (int i = 1; i <= n - 1; ++i) {
    if (isbig(c[i]) and isbig(c[i+1])) {
      if (c[i] == c[i+1]) big_in[c[i]]++;
      adj[bid[c[i]]][bid[c[i+1]]]++;
      adj[bid[c[i+1]]][bid[c[i]]]++;
    }
  }
  for (int _ = 0; _ < q; ++_) {
    int col;scanf("%d", &col);
    light[col] *= -1;
    upd(col);
    printf("%d\n", ans1 - ans2);
  }
}

int main() {
  init();
  solve();
}
