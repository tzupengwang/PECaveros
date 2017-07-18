#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 1e5+10;
const int LG = 20;
const int X = 2500000;
const LL MOD = 1e9+7;

inline int mul(int x, int y) {
  LL res = (LL)x*(LL)y;
  return res >= MOD ? res%MOD: res;
}
inline int add(int x, int y) {
  int res = x+y;
  return res >= MOD ? res-MOD: res;
}
inline int sub(int x, int y) {
  int res = x-y;
  return res < 0 ? res+MOD: res;
}

int n, a[N];
vector<int> pos[X+1];

void input() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", a+i);
  }
}

int dat[LG][N];
int lg[N];

inline int gcd(int l, int r) {
  int b = lg[r-l+1];
  return __gcd(dat[b][l], dat[b][r-(1<<b)+1]);
}

void predo() {
  lg[1] = 0;
  for (int i = 1; i <= n; ++i) {
    pos[a[i]].push_back(i);
    if (i > 1) lg[i] = 1+lg[i/2];
    dat[0][i] = a[i];
  }
  for (int j = 0; j < LG-1; ++j) {
    for (int i = 1; i + (1<<(j+1)) - 1 <= n; ++i) {
      int ii = i+(1<<j);
      ii = min(n, ii);
      dat[j+1][i] = __gcd(dat[j][i], dat[j][ii]);
    }
  }
}

int dp[N], cnt[N];
int prvdp[N];
int scnt[N];

inline void go(int l, int r, int g, int& rval, int& rcnt) {
  // a[l...r]
  dp[l-1] = 0;
  prvdp[l-1] = l-1;

  cnt[l-1] = 1;
  scnt[l-1] = 1;
  int p = l;
  for (int i = l; i <= r; ++i) {
    while (p+1 <= i && gcd(p+1, i) == g) {
      ++p;
    }
    if (gcd(p, i) > g) {
      dp[i] = dp[i-1];

      cnt[i] = cnt[i-1];
    } else {
      dp[i] = max(dp[i-1], 1+dp[p-1]);
      cnt[i] = 0;
      if (dp[i-1] == dp[i]) {
        cnt[i] = add(cnt[i], cnt[i-1]);
      }
      if (1+dp[p-1] == dp[i]) {
        // dp[p-1] = ... = dp[pp]
        int pp = prvdp[p-1];
        // += cnt[p-1] + ... + cnt[pp]
        if (pp <= l-1) {
          cnt[i] = add(cnt[i], scnt[p-1]);
        }
        else {
          cnt[i] = add(cnt[i], sub(scnt[p-1], scnt[pp-1]));
        }
      }
    }
    if (dp[i] == dp[i-1]) prvdp[i] = prvdp[i-1];
    else prvdp[i] = i;
    scnt[i] = add(cnt[i], scnt[i-1]);
  }
  rval = dp[r];
  rcnt = cnt[r];
}

int m;
int ids[N];
int ansval, anscnt;

inline void calc(int g) {
  m = 0;
  for (int i = g; i <= X; i += g) {
    for (int j: pos[i]) {
      ids[++m] = j;
    }
  }
  int val = 0, ccnt = 1;
  sort(ids+1, ids+m+1);
  for (int i = 1; i <= m;) {
    int j = i;
    while (j <= m && ids[j]-ids[i] == j-i) {
      ++j;
    }
    int tval, tcnt;
    go(ids[i], ids[j-1], g, tval, tcnt);
    val += tval;
    ccnt = mul(ccnt, tcnt);
    i = j;
  }
  if (val > ansval) {
    ansval = val;
    anscnt = ccnt;
  } else if(val == ansval) {
    anscnt = add(anscnt, ccnt);
  }
}

void solve() {
  for (int g = 1; g <= X; ++g) calc(g);
  printf("%d %d\n", ansval, anscnt);
}

int main(){
  input();
  predo();
  solve();
}
