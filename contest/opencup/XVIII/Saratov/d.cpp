#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;
int n;

vector<ii> s;
ll dp[200005];

int main() {
  while (scanf("%d", &n) == 1) {
    s.clear();
    for (int i = 0; i < n; i ++) {
      ll x, y;
      scanf("%lld%lld", &x, &y);

      while (s.size() && s.back().second <= y) s.pop_back();
      s.push_back(ii(x, y));
    }
    n = s.size();

    priority_queue<ii, vector<ii>, greater<ii> > pq;

    dp[0] = s[0].first + s[0].second * 2;

    int pt = 0;
    for (int i = 1; i < n; i ++) {
      pq.push(ii(dp[i - 1] + s[i].second * 2, i - 1));

      while (pt < i && dp[pt] <= s[i].first) pt ++;
      dp[i] = s[i].first + s[pt].second * 2;

      while (!pq.empty() && pq.top().second < pt) pq.pop();
      if (!pq.empty()) dp[i] = min(dp[i], pq.top().first);
    }

    printf("%lld\n", dp[n - 1]);
  }
}
