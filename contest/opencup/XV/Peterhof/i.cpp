
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int B = 64;
const int N = 8192;

bitset<N> f, h;
bitset<N> g[B], gB[B];
int n, m, t;

void read(bitset<N>& poly, int &deg) {
  scanf("%d", &deg);
  for (int i = 0; i <= deg; ++i) {
    int x; scanf("%d", &x);
    if (x) poly[i] = 1;
  }
}

inline void mod(bitset<N> &poly) {
  for (int i = N-1; i >= t; --i) if (poly[i]) {
    poly ^= h << (i-t);
  }
}

bitset<N> mul(const bitset<N> &a, const bitset<N> &b) {
  bitset<N> res;
  res.reset();
  for (int i = 0; i < N; ++i) if (a[i])
    res ^= b << i;
  mod(res);
  return res;
}

void predo() {
  g[0][0] = 1;
  for (int i = 2; i < B; ++i) {
    g[i] = mul(g[1], g[i-1]);
  }
  gB[0][0] = 1;
  gB[1] = mul(g[1], g[B-1]);
  for (int i = 2; i < B; ++i) {
    gB[i] = mul(gB[1], gB[i-1]);
  }
}

void solve() {
  bitset<N> ans, tmp, tmp2;
  ans.reset();
  for (int a = 0; a < B; ++a) {
    tmp.reset();
    for (int b = 0; b < B; ++b) {
      int i = a*B+b;
      if (f[i]) tmp ^= g[b];
    }
    tmp2 = mul(gB[a], tmp);
    ans ^= tmp2;
  }
  int deg = -1;
  for (int i = 0; i < N; ++i) if (ans[i]) deg = i;
  if (deg == -1) {
    puts("0 0");
    return;
  }
  printf("%d", deg);
  for (int i = 0; i <= deg; ++i) printf(" %c", "01"[ans[i]]);
  puts("");
}

int main(){
  read(f, n);
  read(g[1], m);
  read(h, t);
  predo();
  solve();
}
