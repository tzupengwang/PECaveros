#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> PII;

const int N = 1e5+10;
const int INF = 2e9;

struct SEG {
  int dat[N<<2], mnid[N<<2];
  void upd(int id, int l, int r, int i, int x) {
    if (l == r) {
      dat[id] = x;
      mnid[id] = l;
      return;
    }
    int mid = (l+r) / 2;
    if (i <= mid) upd(id*2, l, mid, i, x);
    else upd(id*2+1, mid+1, r, i, x);
    int from = id*2;
    if (dat[id*2] > dat[id*2+1]) from = id*2+1;
    dat[id] = dat[from];
    mnid[id] = mnid[from];
  }
  PII qry(int id, int l, int r, int a, int b) {
    if (b < l || r < a) return {INF, -1};
    if (a <= l && r <= b) return {dat[id], mnid[id]};
    int mid = (l+r) / 2;
    PII r1 = qry(id*2, l, mid, a, b);
    PII r2 = qry(id*2+1, mid+1, r, a, b);
    if (r1.first < r2.first) return r1;
    else return r2;
  }
} seg1, seg2;

int n, a[N], m;
set<int> ban;

inline int lft(int i) {
  auto it = ban.lower_bound(i);
  --it;
  return *it + 1;
}

inline int rgt(int i) {
  auto it = ban.upper_bound(i);
  return *it - 1;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", a+i);
    seg1.upd(1, 1, n, i, a[i]-i);
    seg2.upd(1, 1, n, i, a[i]+i);
  }
  scanf("%d", &m);
  ban.insert(0);
  ban.insert(n+1);
  for (int i = 0; i < m; ++i) {
    int x;scanf("%d", &x);
    int xl = lft(x);
    int xr = rgt(x);
    int ans = 0;
    {
      while (1) {
        PII res = seg1.qry(1, 1, n, xl, x);
        if (res.first > a[x]-x) break;
        seg1.upd(1, 1, n, res.second, INF);
        ban.insert(res.second);
        ++ans;
      }
    }
    {
      while (1) {
        PII res = seg2.qry(1, 1, n, x+1, xr);
        if (res.first > a[x]+x) break;
        seg2.upd(1, 1, n, res.second, INF);
        ban.insert(res.second);
        ++ans;
      }
    }
    printf("%d\n", ans);
  }
}
