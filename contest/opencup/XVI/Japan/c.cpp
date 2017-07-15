#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
const int N = 1e5+10;
const LL  INF = 1e12;


int n, w[N];
LL sum[N];
int q, s[N], t[N];
int cov[N];

LL calc() {
  LL res = 0;
  fill(cov, cov+n+1, 0);
  for (int i = 1; i <= q; ++i) if(s[i] < t[i]) {
    res += sum[t[i]-1] - sum[s[i]-1];
    ++cov[s[i]];
    --cov[t[i]];
  }
  for (int i = 1; i <= n; ++i) cov[i] += cov[i-1];
  set<int> ban;
  for (int i = 1; i <= n; ++i) {
    if (cov[i]) {
      ban.insert(i);
    }
  }
  for (int i = 1; i <= q; ++i) if(s[i] > t[i]) {
    int r = s[i]-1;
    int l = t[i];
    auto it = ban.lower_bound(l);
    
  }
  return res;
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", w+i);
    sum[i] = sum[i-1] + w[i];
  }
  for (int i = 1; i <= q; ++i) {
    scanf("%d%d", s+i, t+i);
    ++s[i], ++t[i];
  }
  LL a1 = calc();

  reverse(w+1, w+1+n);
  for (int i = 1; i <= n; ++i) {
    sum[i] = sum[i-1] + w[i];
  }
  for (int i = 1; i <= q; ++i) {
    s[i] = n-s[i]+1;
    t[i] = n-t[i]+1;
  }
  LL a2 = calc();

  LL ans = min(a1, a2);
  if (ans >= INF) puts("-1");
  else printf("%lld\n", ans);
}
