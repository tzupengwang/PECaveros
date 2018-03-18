
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e6+10;

struct BIT {
  int n;
  LL s[N+N];
  void init(int _n) { n = _n; fill(s, s+n+1, 0); }
  void upd(int id, LL x) {
    for (int i = id; i <= n; i +=i&-i) s[i] += x;
  }
  LL qry(int id) {
    LL res = 0;
    for (int i = id; i > 0; i -= i&-i) res += s[i];
    return res;
  }
} bit;

struct XD {
  int x, l, r;
};

int n, a[N], prv[N];
deque<XD> dq;

inline void add(XD xd) {
  bit.upd(xd.l + xd.x, 1);
  bit.upd(xd.r + xd.x + 1, -1);
}

inline void del(XD xd) {
  bit.upd(xd.l + xd.x, -1);
  bit.upd(xd.r + xd.x + 1, 1);
}

int main(){
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) scanf("%d", a+i);
  bit.init(n+n);
  int j = 1;
  LL ans = 0;
  for (int i = 1; i <= n; ++i) {
    j = max(j, prv[a[i]]+1);
    while (dq.size() && dq[0].l < j) {
      del(dq[0]);
      if (j <= dq[0].r) {
        dq[0].l = j;
        add(dq[0]);
        break;
      }
      dq.pop_front();
    }
    while (dq.size() && dq.back().x < a[i]) {
      del(dq.back());
      dq.pop_back();
    }
    XD xd{a[i], j, i};
    if (dq.size()) xd.l = dq.back().r+1;
    add(xd);
    dq.push_back(xd);

    ans += bit.qry(i+1);

    prv[a[i]] = i;
  }
  cout << ans << endl;
}
