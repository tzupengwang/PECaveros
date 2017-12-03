#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define N 111
int MD;
int n , m , l[ N ] , r[ N ], p[N];

int tr, trt, sgn[N], rt[N], vst[N];
int msk;
void dfs1(int x, int csgn) {
  if (vst[x]) return;
  vst[x] = true;
  tr = max(tr, x);
  rt[x] = trt;
  sgn[x] = csgn;

  for (int i = 1; i <= m; i ++) {
    if (l[i] - 1 == x) {
      dfs1(r[i], csgn ^ p[i]);
    }
    if (r[i] == x) {
      dfs1(l[i] - 1, csgn ^ p[i]);
    }
  }
}

int bit(int X, int Y) {
  return (X >> Y) & 1;
}

int s[45], ones, ones2;
int amn, alf, arf;

int dp[1 << 21][2];
int cs[1 << 21][2];

void rdfs(int mm, int ss, int x, int res) {
  if (x == n + 1) {
    if (dp[mm][ss] == -1) {
      dp[mm][ss] = res;
      cs[mm][ss] = ones2;
    } else if (ones2 < cs[mm][ss]) {
      dp[mm][ss] = res;
      cs[mm][ss] = ones2;
    } else if (ones2 == cs[mm][ss] && res < dp[mm][ss]) {
      dp[mm][ss] = res;
      cs[mm][ss] = ones2;
    }
    return;
  }

  if (rt[x] != x) {
    s[x] = s[rt[x]] ^ sgn[x];
    int nxt = 0;
    if (s[x] != s[x - 1]) nxt = 1 << (n - x);

    if (nxt) ones2 ++;
    if (s[x]) {
      rdfs(mm, ss, x + 1, res ^ nxt);
    } else {
      rdfs(mm, ss, x + 1, res ^ nxt);
    }
    if (nxt) ones2 --;
  } else {
    int nxt;
    {
      s[x] = 1;
      nxt = 0;
      if (s[x] != s[x - 1]) nxt = 1 << (n - x);
      if (nxt) ones2 ++;
      rdfs(mm, ss, x + 1, res ^ nxt);
      if (nxt) ones2 --;
    }
    {
      s[x] = 0;
      nxt = 0;
      if (s[x] != s[x - 1]) nxt = 1 << (n - x);
      if (nxt) ones2 ++;
      rdfs(mm, ss, x + 1, res ^ nxt);
      if (nxt) ones2 --;
    }
  }
}

void rdfs_val(int tmsk, int sum, int &res, int &cst) {
  if (dp[tmsk][sum] != -1) {
    res = dp[tmsk][sum];
    cst = cs[tmsk][sum];
    return;
  }
  ones2 = 0;
  rdfs(tmsk, sum, MD, 0);
  //rdfs(msk, psum, MD, (1 << (MD - 1)) * sum, 0);
  res = dp[tmsk][sum];
  cst = cs[tmsk][sum];
}

void fdfs(int x, int state, int res) {
  if (x == MD) {
    int res2, cst;
    rdfs_val(state & msk, bit(state, x - 1), res2, cst);
    if (ones + cst < amn ||
        (ones + cst == amn && res < alf)) {
      amn = ones + cst;
      alf = res, arf = res2;
    }
    return;
  }

  if (rt[x] != x) {
    s[x] = s[rt[x]] ^ sgn[x];
    int nxt = 0;
    if (s[x] != s[x - 1]) nxt = 1 << (MD - x - 1);

    if (nxt) ones ++;
    if (s[x]) {
      fdfs(x + 1, state ^ (1 << x), res ^ nxt);
    } else {
      fdfs(x + 1, state, res ^ nxt);
    }
    if (nxt) ones --;
  } else {
    int nxt;
    {
      s[x] = 1;
      nxt = 0;
      if (s[x] != s[x - 1]) nxt = 1 << (MD - x - 1);
      if (nxt) ones ++;
      fdfs(x + 1, state ^ (1 << x), res ^ nxt);
      if (nxt) ones --;
    }
    {
      s[x] = 0;
      nxt = 0;
      if (s[x] != s[x - 1]) nxt = 1 << (MD - x - 1);
      if (nxt) ones ++;
      fdfs(x + 1, state, res ^ nxt);
      if (nxt) ones --;
    }
  }
}

int main(){
  scanf("%d%d", &n, &m);
  MD = n / 2 + 1;
  for (int i = 1; i <= m; i ++) {
    scanf("%d%d%d", &l[i], &r[i], &p[i]);
  }

  msk = 0;
  for (int i = 0; i <= n; i ++) if (!vst[i]) {
    trt = i, tr = i;
    dfs1(i, 0);
    if (i < MD && tr >= MD) {
      msk += 1 << i;
    }
  }

  memset(dp, -1, sizeof dp);
  amn = 50;
  s[0] = 0;
  fdfs(1, 0, 0);

  //printf("%d\n", amn);
  for (int i = 1; i < MD; i ++) {
    printf("%d ", bit(alf, MD - i - 1));
  }
  for (int i = MD; i <= n; i ++) {
    printf("%d%c", bit(arf, n - i), " \n"[i == n]);
  }
}
