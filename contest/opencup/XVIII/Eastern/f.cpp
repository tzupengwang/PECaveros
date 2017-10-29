#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int N = 80000;
const int M = 16e4+10;
const int MOD = 1e9+7;
const int D2 = (MOD+1) / 2;

inline int add(int a, int b) {
  a += b;
  if (a >= MOD) a -= MOD;
  return a;
}

inline int mul(ll a, int b) {
  a *= b;
  if (a >= MOD) a %= MOD;
  return a;
}

inline int sub(int a, int b) {
  a -= b;
  if (a < 0) a += MOD;
  return a;
}

int mpow(int bs, int pw) {
  if (pw == 0) return 1;
  int rt = mpow(bs, pw / 2);
  rt = mul(rt, rt);
  if (pw % 2) rt = mul(rt, bs);
  return rt;
}

int m;
vector<ii> op[M];
int slen[M];
int f[M], h[M];
int mu[M];
int fac[M];
int inv[M];

int C2(int l) {
  return mul(D2, mul(l, l+1));
}

int Blah(int d, int l, int r, vector<ii> &pr, vector<int> &len) {
  int sid = op[d][l].first;
  int front = 0, back = 0, ret = 0;
  for (int i = l; i < r; ) {
    int j = i;
    while (j < r && op[d][j].second == op[d][i].second + j - i) j ++;

    if (j - i == slen[sid]) {
      len.push_back(j - i);
      return C2(j - i);
    }

    if (op[d][i].second == 1) {
      front = j - i;
    } else if (op[d][j - 1].second == slen[sid]) {
      back = j - i;
    }

    ret = add(ret, C2(j - i));
    i = j;
  }
  pr.push_back(ii(front, back));
  return ret;
}

int BlahBlah(vector<ii> &pr, vector<int> &len) {
  int l1 = len.size();
  int l2 = m - l1;
  ll tans = 0;

  int sl = 0, sr = 0, slr = 0;
  for (ii lr : pr) {
    sl = add(sl, lr.first);
    sr = add(sr, lr.second);
    slr = add(slr, mul(lr.first, lr.second));
  }
  tans = add(tans, mul(mul(sub(mul(sl, sr), slr), fac[m]), inv[l2]));

  int longs = 0, longs2 = 0;
  for (int oln : len) {
    longs = add(longs, oln);
    longs2 = add(longs2, mul(oln, oln));
  }
  tans = add(tans, mul(mul(mul(add(sl, sr), longs), fac[m]), inv[l2 + 1]));

  tans = add(tans, mul(mul(mul(sub(mul(longs, longs), longs2), 1), fac[m]), inv[l2 + 2]));

  return tans;
}

int process(int d) {
  // TODO: Paul
  ll tans = 0;
  vector<ii> pr;
  vector<int> len;
  for (int i = 0; i < (int)op[d].size(); ) {
    int j = i;
    while (j < (int)op[d].size() && op[d][j].first == op[d][i].first) j ++;
    tans = add(tans, mul(Blah(d, i, j, pr, len), fac[m]));
    i = j;
  }
  tans = add(tans, BlahBlah(pr, len));
  return tans;
}

void predo() {
  // mu, fac
  fac[0] = 1;
  for (int i = 1; i < M; ++i) {
    fac[i] = mul(i, fac[i-1]);
    inv[i] = mpow(i, MOD - 2);
  }
}

int fcnt[M];

int main() {
  predo();
  scanf("%d", &m);
  for (int i = 1; i <= m; ++i) {
    scanf("%d", slen+i);
    for (int j = 1; j <= slen[i]; ++j) {
      int x;
      scanf("%d", &x);
      for (int k = 1; k*k <= x; ++k) {
        if (x%k != 0) continue;
        op[k].push_back({i, j});
        if (k*k != x) {
          op[x/k].push_back({i, j});
        }
      }
    }
  }
  for (int i = 1; i <= N; ++i) {
    h[i] = process(i);
    //if (i <= 8) printf("h[%d] = %d\n", i, h[i]);
    for (int j = i; j <= N; j += i)
      fcnt[i]++;
  }
  int ans = 0;
  for (int i = N; i >= 1; --i) {
    assert(fcnt[i] == 1);
    f[i] = h[i];
    ans = add(ans, mul(i, f[i]));
    for (int k = 1; k*k <= i; ++k) {
      if (i%k != 0) continue;
      fcnt[k]--;
      h[k] = sub(h[k], f[i]);
      if (k*k != i) {
        fcnt[i/k]--;
        h[i/k] = sub(h[i/k], f[i]);
      }
    }
  }
  printf("%d\n", ans);
}
