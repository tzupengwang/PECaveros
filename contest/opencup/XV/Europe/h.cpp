
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 2e5+10;
const int INF = 1e8;

typedef pair<int,int> pii;

int n, k;
int v[N], c[N];
pii item[N];

int dp[N][12];

bool ok(int x) {
  fill(dp[0], dp[0]+12, INF);
  dp[0][0] = 0;
  for (int i = 1; i <= n; ++i) {
    fill(dp[i], dp[i]+12, INF);
    dp[i][0] = 0;
    for (int j = 1; j <= k+1; ++j) {
      dp[i][j] = dp[i-1][j];
      if (v[i] - c[i] - dp[i-1][j-1] >= x) {
        dp[i][j] = min(dp[i][j], c[i] + dp[i-1][j-1]);
      }
    }
  }
  return dp[n][k+1] < INF;
}

void main2() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", v+i, c+i);
    item[i] = {v[i],c[i]};
  }
  sort(item+1, item+n+1);
  for (int i = 1; i <= n; ++i) {
    tie(v[i], c[i]) = item[i];
  }
  int l = 1, r = INF, ans = 0;
  while (l <= r) {
    int mid = (l+r) / 2;
    if (ok(mid)) ans = mid, l = mid+1;
    else r = mid-1;
  }
  printf("%d\n", ans);
}

int main(){
  int tc;scanf("%d", &tc);while(tc--) main2();

}
