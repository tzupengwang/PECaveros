
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;

pii pos[11];
set<int> nums;

inline bool ok(int x, int d) {
  return pos[x].first <= pos[d].first and pos[x].second <= pos[d].second;
}

void dfs(int cur, int n, int lst) {
  nums.insert(cur);
  if (n == 3) {
    return;
  }
  for (int d = 0; d <= 9; ++d) {
    if (lst == -1 or ok(lst, d)) {
      dfs(cur*10 + d, n+1, d);
    }
  }
}

void predo() {
  for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j)
    pos[i*3+j+1] = {i, j};
  pos[0] = {3, 1};
  dfs(0, 0, -1);
  //for (int x: nums) cout << x << endl;
}

int main(){
  predo();
  int tc; scanf("%d", &tc);
  while (tc--) {
    int k; scanf("%d", &k);
    auto it = nums.upper_bound(k);
    int r = *it;
    it--;
    int l = *it;
    int ans = l;
    if (abs(k-r) < abs(k-l)) ans = r;
    printf("%d\n", ans);
  }
}
