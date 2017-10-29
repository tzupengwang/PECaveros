#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 5e4+10;
const int M = 5e5+10;
const int D = 55;
const LL INF = 10000000000000000;

struct Q {
  int l, r, id;
};

int n, m;
LL d;
LL a[N][3];
Q qs[M];
LL ans[M];

void dq(int l, int r, int ql, int qr) {
  static Q tmp[M], cur[M];
  static LL ldp[N][D];
  static LL rdp[N][D];
  if (l == r) {
    LL mx = -1;
    for (int j = 0; j < 3; ++j) if (a[l][j] % d == 0)
      mx = max(mx, a[l][j]);
    for (int i = ql; i <= qr; ++i) {
      int id = qs[i].id;
      ans[id] = mx;
    }
    return;
  }
  int mid = (l+r) / 2;
  int ll = ql, rr = qr;
  int t = 0;
  for (int i = ql; i <= qr; ++i) {
    if (qs[i].l <= mid and mid + 1 <= qs[i].r) {
      ++t;
      cur[t] = qs[i];
    }
    else if (qs[i].r <= mid) {
      tmp[ll] = qs[i];
      ll++;
    }
    else if (mid+1 <= qs[i].l) {
      tmp[rr] = qs[i];
      rr--;
    }
  }
  for (int i = ql; i <= qr; ++i) qs[i] = tmp[i];

  fill(ldp[mid+1], ldp[mid+1]+d, -INF);
  ldp[mid+1][0] = 0;

  for (int i = mid; i >= l; --i) {
    fill(ldp[i], ldp[i]+d, -INF);
    for (int k = 0; k < d; ++k) {
      for (int j = 0; j < 3; ++j) {
        LL nxt = (k+a[i][j]) % d;
        ldp[i][nxt] = max(ldp[i][nxt], ldp[i+1][k] + a[i][j]);
      }
    }
  }

  fill(rdp[mid], rdp[mid]+d, -INF);
  rdp[mid][0] = 0;
  for (int i = mid+1; i <= r; ++i) {
    fill(rdp[i], rdp[i]+d, -INF);
    for (int k = 0; k < d; ++k) {
      for (int j = 0; j < 3; ++j) {
        LL nxt = (k+a[i][j]) % d;
        rdp[i][nxt] = max(rdp[i][nxt], rdp[i-1][k] + a[i][j]);
      }
    }
  }

  for (int i = 1; i <= t; ++i) {
    int tl = cur[i].l;
    int tr = cur[i].r;
    int id = cur[i].id;
    ans[id] = max(ans[id], ldp[tl][0] + rdp[tr][0]);
    for (int k = 1; k < d; ++k) {
      ans[id] = max(ans[id], ldp[tl][k] + rdp[tr][d-k]);
    }
  }

  dq(l, mid, ql, ll-1);
  dq(mid+1, r, rr+1, qr);
}

int main() {
  scanf("%d%d", &n, &d);
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < 3; ++j) {
      scanf("%d", a[i]+j);
    }
  }
  scanf("%d", &m);
  for (int i = 1; i <= m; ++i) {
    int l, r;
    scanf("%d%d", &l, &r);
    qs[i] = {l, r, i};
    ans[i] = -1;
  }
  dq(1, n, 1, m);
  for (int i = 1; i <= m; ++i) {
    printf("%lld\n", ans[i]);
  }
}
