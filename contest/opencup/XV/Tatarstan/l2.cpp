
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e5+10;

int n, p[N];
map<LL, LL> cnt;

int main(){
  scanf("%d", &n);
  LL mx = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d", p+i);
    mx = max(mx, (LL)p[i]);
    cnt[p[i]]++;
  }
  LL ans = 1LL * (LL)mx * cnt[mx];
  if (mx > 0) {
    for (int i = 0; i < n; ++i) if (p[i]) {
      for (int j = i-1; j < i+2; j += 2) {
        if (0 > j || n <= j) continue;
        cnt[p[i]]--;
        cnt[p[j]]--;
        cnt[p[i]-1]++;
        cnt[p[j]+1]++;
        auto it = cnt.end(); --it;
        while (it->second == 0) --it;
        ans = min(ans, 1LL * (LL)it->first * it->second);
        cnt[p[i]]++;
        cnt[p[j]]++;
        cnt[p[i]-1]--;
        cnt[p[j]+1]--;
      }
    }
  }
  cout << ans << endl;
}
