
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long LL;
const LL LIM = (1ULL<<63ULL)-1LL;
//const LL LIM = (1LL<<32LL)-1;
const int P = 100;
int ps[P], pn;
int mxe[P];
LL pw[P][P];
bool np[P];
map<LL,LL> ans;
inline bool ok(LL x, LL a, LL b) {
  LL g = __gcd(a, b);
  a /= g, b /= g;
  g = __gcd(x, b);
  x /= g, b /= g;
  return x <= LIM / a;
}
inline LL f(LL x, LL a, LL b) {
  LL g = __gcd(a, b);
  a /= g, b /= g;
  g = __gcd(x, b);
  x /= g, b /= g;
  return x*a;
}
void dfs(int i, int e, int cnt, int mx, LL curn, LL curx) {
  if (i == pn) return;
  if (e > mx) return;
  if (cnt > 0) {
    if (ans.count(curn)) {
      ans[curn] = min(curx, ans[curn]);
    } else {
      ans[curn] = curx;
    }
  }
  {
    LL nxtn = curn, nxtx = curx;

    if ((LL)ps[i] <= LIM / curx and ok(curn, cnt+1, e+1)) {
      nxtn = f(curn, cnt+1, e+1);
      nxtx *= ps[i];
      dfs(i, e+1, cnt+1, mx, nxtn, nxtx);
    }

  }
  {
    LL nxtn = curn, nxtx = curx;
    dfs(i+1, 0, cnt, min(e, mxe[i+1]), nxtn, nxtx);
  }
}
void build() {
  for (int i = 2; i < P; ++i) if (!np[i]) {
    ps[pn++] = i;
    for (int j = i+i; j < P; j += i) np[j] = 1;
  }
  for (int i = 0; i < pn; ++i) {
    pw[i][0] = 1;
    mxe[i] = 0;
    for (int j = 1; j < P; ++j) {
      if ((LL)ps[i] > LIM / pw[i][j-1]) break;
      pw[i][j] = pw[i][j-1] * ps[i];
      mxe[i] = j;
    }
  }
  dfs(0, 0, 0, mxe[0], 1, 1);
  //cerr << ans.size() << endl;
}
int main(){
  build();
  LL n;
  while (cin >> n) {
    cout << n << " " << ans[n] << endl;
  }
}
