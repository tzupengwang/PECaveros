#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int N = 256;
const int X = 10005;
const int Q = 250010;

struct BIT {
  int sz;
  int dat[N][N];
  vector<pii> log;
  void init(int n) {
    log.clear();
    sz = n;
    for (int i = 1; i <= n; ++i)
      fill(dat[i], dat[i]+n+1, 0);
  }
  void upd(int x, int y) {
    log.push_back({x, y});
    for (int i = x; i <= sz; i += i&-i) {
      for (int j = y; j <= sz; j += j&-j)
        dat[i][j]++;
    }
  }
  int qry(int x, int y) {
    int res = 0;
    for (int i = x; i > 0; i -= i&-i) {
      for (int j = y; j > 0; j -= j&-j)
        res += dat[i][j];
    }
    return res;
  }
  int qry(int x1, int y1, int x2, int y2) {
    return qry(x2, y2) - qry(x2, y1-1) - qry(x1-1, y2) + qry(x1-1, y1-1);
  }
  void reset() {
    for (pii p: log) {
      int x, y;
      tie(x, y) = p;
      for (int i = x; i <= sz; i += i&-i) {
        for (int j = y; j <= sz; j += j&-j)
          dat[i][j]--;
      }
    }
    log.clear();
  }
} bit;

struct XD {
  int x1, y1, x2, y2;
  int k, id;
};

int n, mx, q;
vector<pii> pos[X];
XD qs[Q];
int ans[Q];


void dq(int l, int r, int ql, int qr) {
  static XD tmp[Q];
  //printf("dq %d %d %d %d\n", l, r, ql, qr);
  if (l == r) {
    for (int i = ql; i <= qr; ++i) {
      ans[qs[i].id] = l;
    }
    return;
  }
  int mid = (l+r) / 2;

  for (int i = l; i <= mid; ++i) {
    for (pii p: pos[i]) {
      bit.upd(p.first, p.second);
    }
  }

  //puts("aaa");

  int ll = ql, rr = qr;

  for (int i = ql; i <= qr; ++i) {
    int cnt = bit.qry(qs[i].x1, qs[i].y1, qs[i].x2, qs[i].y2);
    if (cnt < qs[i].k) { // mid+1 r
      qs[i].k -= cnt;
      tmp[rr] = qs[i];
      rr--;
    } else { // l mid
      tmp[ll] = qs[i];
      ll++;
    }
  }
  //puts("aaa");

  for (int i = ql; i <= qr; ++i) {
    qs[i] = tmp[i];
  }

  int qm = rr;

  bit.reset();

  dq(l, mid, ql, qm);
  dq(mid+1, r, qm+1, qr);
}

void main2() {
  for (int i = 1; i <= mx; ++i) pos[i].clear();
  mx = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      int x;
      scanf("%d", &x);
      mx = max(x, mx);
      pos[x].push_back({i, j});
    }
  }
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    int r, c, s, k;
    scanf("%d%d%d%d", &r, &c, &s, &k);
    qs[i] = XD{r, c, r+s-1, c+s-1, k, i};
  }
  bit.init(n);
  dq(1, mx, 1, q);
  for (int i = 1; i <= q; ++i) {
    printf("%d\n", ans[i]);
  }
}

int main() {
  while (scanf("%d", &n) != EOF) {
    main2();
  }
}
