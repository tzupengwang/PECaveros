#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

int m, n, k;
int val[205];
int cost[205];
priority_queue<ii, vector<ii>, greater<ii> > pq;
int tgt[205];
int tcst[205];
int degr[205];
vector<ii> v[205];

void init() {
  while (!pq.empty()) pq.pop();
  scanf("%d%d%d", &m, &n, &k);
  for (int i = 1; i <= n; i ++) {
    v[i].clear();
    cost[i] = -1;
    int can, c;
    scanf("%d", &can);
    if (can) {
      scanf("%d", &c);
      pq.push(ii(c, i));
    }
    scanf("%d", &val[i]);
  }

  for (int i = 0; i < k; i ++) {
    scanf("%d%d", &tgt[i], &degr[i]);
    tcst[i] = 0;
    for (int j = 0; j < degr[i]; j ++) {
      int x, y;
      scanf("%d%d", &x, &y);
      v[x].push_back(ii(y, i));
    }
  }
}

int ans[10005];

void solve() {
  while (!pq.empty()) {
    ii ttt = pq.top(); pq.pop();
    int x = ttt.second, c = ttt.first;
    if (cost[x] != -1) continue;

    cost[x] = c;
    for (ii pr: v[x]) {
      int y = pr.second, ml = pr.first;
      tcst[y] += ml * c;
      degr[y] --;
      if (degr[y] == 0) {
        pq.push(ii(tcst[y], tgt[y]));
      }
    }
  }

  for (int i = 0; i <= m; i ++)
    ans[i] = 0;
  for (int i = 1; i <= n; i ++) {
    if (cost[i] == -1) continue;
    int c = cost[i];
    for (int j = c; j <= m; j ++) {
      ans[j] = max(ans[j], ans[j - c] + val[i]);
    }
  }
  printf("%d\n", ans[m]);
}


int main(){
  int T; scanf("%d", &T);
  for (int tc = 1; tc <= T; tc ++) {
    init();
    printf("Case #%d: ", tc);
    solve();
  }

}
