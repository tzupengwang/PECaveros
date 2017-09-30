#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll mod = 1000000007;
int n;
ll s[105];

ll pow(ll bs, ll pw) {
  if (pw == 0) return 1LL;
  ll tp = pow(bs, pw / 2);
  tp = tp * tp % mod;
  if (pw % 2) tp = tp * bs % mod;
  return tp;
}
int fd(int *pr, int id) {
  //printf("%d\n", id);
  if (id == 0) return 0;
  if (pr[id] == 0) return 0;
  assert(id == 2 || id == 3 || id == 5 || id == 7);
  return (pr[id] == id) ? id : (pr[id] = fd(pr, pr[id]));
}
int trans(int x) {
  if (x == 2) return 1;
  else if (x == 3) return 2;
  else if (x == 5) return 3;
  else if (x == 7) return 4;
  else if (x == 0) return 0;
  assert(false);
}
int rtrans(int x) {
  if (x == 1) return 2;
  else if (x == 2) return 3;
  else if (x == 3) return 5;
  else if (x == 4) return 7;
  else if (x == 0) return 0;
  assert(false);
}
void add(ll &x, ll y) {
  x = (x + y) % mod;
}
ll mul(ll x, ll y) {
  return x * y % mod;
}

vector<int> dec(int x) {
  vector<int> v;
  for (int i = 2; i <= x; i ++) {
    if (x % i == 0) v.push_back(i);
    while (x % i == 0) x /= i;
  }
  return v;
}

vector<int> v[105];
vector<int> buk[105];
ll dp[2][9][9][9][9][9];
ll ans;

int main2();
int main() {
  int N;
  scanf("%d", &N);
  while (N --) main2();
}

int main2() {
  ans = 0;
  scanf("%d", &n);
  for (int i = 1; i <= n; i ++) {
    double x;
    scanf("%lf", &x);
    s[i] = x * 100;
  }

  for (int i = 0; i <= 100; i ++) buk[i].clear();
  for (int i = 0; i <= 100; i ++) v[i].clear();
  for (int i = 2; i <= n; i ++) {
    v[i] = dec(i);
    buk[v[i].back()].push_back(i);
  }

  int left = n;

  memset(dp, 0, sizeof dp);
  dp[0][0][0][0][0][0] = 1;
  for (int pp = 100; pp >= 9; pp --) if (buk[pp].size()) {

    for (int i : buk[pp]) {
      for (int p2 = 0; p2 < 5; p2 ++) {
      for (int p3 = 0; p3 < 5; p3 ++) {
      for (int p5 = 0; p5 < 5; p5 ++) {
      for (int p7 = 0; p7 < 5; p7 ++) {

        for (int ps = 0; ps < 3; ps ++) if (dp[0][p2][p3][p5][p7][ps]) {
          int pr[8];
          pr[2] = rtrans(p2), pr[3] = rtrans(p3), pr[5] = rtrans(p5), pr[7] = rtrans(p7);
          for (int j : v[i]) if (j <= 7 && pr[j] == 0) {
            pr[j] = j;
          }
          for (int dd = 0; dd < (int)v[i].size() - 2; dd ++) {
            int x1 = v[i][dd];
            int x2 = v[i][dd + 1];
            x1 = fd(pr, x1);
            x2 = fd(pr, x2);
            pr[x2] = x1;
          }
          int p2p = trans(pr[2]), p3p = trans(pr[3]), p5p = trans(pr[5]), p7p = trans(pr[7]);

          add(dp[1][p2][p3][p5][p7][ps], mul(dp[0][p2][p3][p5][p7][ps], 100 - s[i]));

          ll val = mul(dp[0][p2][p3][p5][p7][ps], s[i]);
          int psp = ps;
          if (ps == 0) {
            if (v[i].size() == 1) psp = 1;
            else psp = 2;
          } else if (ps == 1 && v[i].size() > 1) psp = 2;
          add(dp[1][p2p][p3p][p5p][p7p][psp], val);
        }
      }}}}
      memset(dp[0], 0, sizeof dp[0]);
      for (int p2 = 0; p2 < 5; p2 ++) {
      for (int p3 = 0; p3 < 5; p3 ++) {
      for (int p5 = 0; p5 < 5; p5 ++) {
      for (int p7 = 0; p7 < 5; p7 ++) {
        for (int ps = 0; ps < 3; ps ++) if (dp[1][p2][p3][p5][p7][ps]) {
          dp[0][p2][p3][p5][p7][ps] = dp[1][p2][p3][p5][p7][ps];
        }
      }}}}
    }

    left -= buk[pp].size();
    for (int p2 = 0; p2 < 5; p2 ++) {
    for (int p3 = 0; p3 < 5; p3 ++) {
    for (int p5 = 0; p5 < 5; p5 ++) {
    for (int p7 = 0; p7 < 5; p7 ++) {
      add(ans, mul(dp[0][p2][p3][p5][p7][1], pow(100, left)));
      for (int ps = 1; ps < 3; ps ++) if (dp[0][p2][p3][p5][p7][ps]) {
        add(dp[0][p2][p3][p5][p7][0], dp[0][p2][p3][p5][p7][ps]);
        dp[0][p2][p3][p5][p7][ps] = 0;
      }
    }}}}
  }

  // small primes
  for (int pp = 7; pp >= 2; pp --) if (buk[pp].size()) {

    for (int i : buk[pp]) {
      memset(dp[1], 0, sizeof dp[1]);
      for (int p2 = 0; p2 < 5; p2 ++) {
      for (int p3 = 0; p3 < 5; p3 ++) {
      for (int p5 = 0; p5 < 5; p5 ++) {
      for (int p7 = 0; p7 < 5; p7 ++) if (dp[0][p2][p3][p5][p7][0]) {
        int pr[8];
        pr[2] = rtrans(p2), pr[3] = rtrans(p3), pr[5] = rtrans(p5), pr[7] = rtrans(p7);
        for (int j : v[i]) if (j <= 7 && pr[j] == 0) {
          pr[j] = j;
        }
        for (int dd = 0; dd < (int)v[i].size() - 1; dd ++) {
          int x1 = v[i][dd];
          int x2 = v[i][dd + 1];
          x1 = fd(pr, x1);
          x2 = fd(pr, x2);
          pr[x2] = x1;
        }
        int p2p = trans(pr[2]), p3p = trans(pr[3]), p5p = trans(pr[5]), p7p = trans(pr[7]);

        add(dp[1][p2][p3][p5][p7][0], mul(dp[0][p2][p3][p5][p7][0], 100 - s[i]));

        ll val = mul(dp[0][p2][p3][p5][p7][0], s[i]);
        add(dp[1][p2p][p3p][p5p][p7p][0], val);
      }}}}
      for (int p2 = 0; p2 < 5; p2 ++) {
      for (int p3 = 0; p3 < 5; p3 ++) {
      for (int p5 = 0; p5 < 5; p5 ++) {
      for (int p7 = 0; p7 < 5; p7 ++) if (dp[1][p2][p3][p5][p7][0]) {
        dp[0][p2][p3][p5][p7][0] = dp[1][p2][p3][p5][p7][0];
      }}}}
    }
  }
  for (int p2 = 0; p2 < 5; p2 ++) {
  for (int p3 = 0; p3 < 5; p3 ++) {
  for (int p5 = 0; p5 < 5; p5 ++) {
  for (int p7 = 0; p7 < 5; p7 ++) if (dp[0][p2][p3][p5][p7][0]) {
    int pr[8];
    pr[2] = rtrans(p2), pr[3] = rtrans(p3), pr[5] = rtrans(p5), pr[7] = rtrans(p7);
    //printf("in\n");
    if (fd(pr, 2) == 2) add(ans, mul(dp[0][p2][p3][p5][p7][0], 100));
    //printf("out\n");
    if (fd(pr, 3) == 3) add(ans, mul(dp[0][p2][p3][p5][p7][0], 100));
    //printf("out\n");
    if (fd(pr, 5) == 5) add(ans, mul(dp[0][p2][p3][p5][p7][0], 100));
    //printf("out\n");
    if (fd(pr, 7) == 7) add(ans, mul(dp[0][p2][p3][p5][p7][0], 100));
    //printf("out\n");
  }}}}
  add(ans, mul(s[1], pow(100, n - 1)));
  printf("%lld\n", ans);
  return 0;
}
