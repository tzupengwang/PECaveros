
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 210;

int n, m;
char ip[N], pat[N];
bool vis[N][N];
bool dp[N][N];
int cnt[27], tcnt[27];

string ans;

bool DP(int l, int r) {
  if (vis[l][r]) return dp[l][r];
  vis[l][r] = 1;
  if (l > r) return dp[l][r] = 1;
  for (int k = r-m; k >= l; k -= m) {
    bool lft = DP(l, k);
    bool rgt = DP(k+1, r);
    if (lft and rgt) {
      return dp[l][r] = 1;
    }
  }
  int id = (r-l+1) % m;
  if (id == 0) id = m;
  if (ip[r] == pat[id]) {
    return dp[l][r] = DP(l, r-1);
  }
  return dp[l][r] = 0;
}

bool chk(int l, int r) {
  int occ = n / (r-l+1);
  m = r-l+1;
  for (int i = l; i <= r; ++i)
    pat[i-l+1] = ip[i];
  pat[m+1] = 0;
  //printf("chk %d %d\n", l, r);
  //printf("%d %s\n", m, pat);
  fill(tcnt, tcnt+26, 0);
  for (int i = l; i <= r; ++i) tcnt[ip[i]-'a']++;
  for (int c = 0; c < 26; ++c) if (cnt[c] > 0) {
    if (cnt[c] > 0 and tcnt[c] == 0)
      return 0;
    if ((cnt[c] % tcnt[c]) != 0 or (cnt[c] / tcnt[c]) != occ)
      return 0;
  }
  for (int i = n; i >= 1; --i) {
    dp[i][i-1] = 1;
    for (int j = i; j <= n; ++j) {
      dp[i][j] = 0;
      for (int k = j - m; k >= i; k -= m) {
        if (dp[i][k] and dp[k+1][j]) dp[i][j] = 1;
      }
      int id = (j-i+1) % m;
      if (id == 0) id = m;
      if (ip[j] == pat[id]) dp[i][j] = dp[i][j] or dp[i][j-1];
    }
  }
  return dp[1][n];
}

int main(){
  scanf("%s", ip+1);
  n = strlen(ip+1);
  for (int i = 1; i <= n; ++i) cnt[ip[i]-'a']++;
  ans = string(ip+1);
  for (int l = 1; l <= n; ++l) {
    if (n % l != 0) continue;
    for (int i = 1; i + l - 1 <= n; ++i) {
      if (chk(i, i+l-1)) {
        string tmp = string(ip+i, ip+i+l);
        if (tmp.size() < ans.size()) ans = tmp;
        else if (tmp.size() == ans.size() and tmp < ans) ans = tmp;
      }
    }
  }
  cout << ans << endl;
}
