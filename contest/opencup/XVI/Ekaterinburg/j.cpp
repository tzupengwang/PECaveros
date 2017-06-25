#include <bits/stdc++.h>
using namespace std;

void omimi() {
  puts("Impossible");
  exit(0);
}

const int N = 155;

typedef pair<int, int> pii;

int n , a[N][N];
int m;
int d[N];
vector<pii> g[N];

int main(){
  cin >> n;
  for (int i=1; i <= n; i++)
    for (int j=1; j<=n; j++)
      cin >> a[i][j];
  cin >> m;
  for (int i = 1; i <= m; i++) {
    int s, t, x;
    cin >> s >> t >> x;
    if (s == t) omimi();
    g[s].push_back({t, x});
    g[t].push_back({s, -x});
  }

  for (int cnt = 0; cnt <= n; cnt++) {
    bool upd = 0;
    for (int i = 1; i <= n; i++)
      for (auto e: g[i]) {
        int u = i;
        int v = e.first;
        int c = e.second;
        if (d[u] > d[v]+c) {
          d[u] = d[v]+c;
          upd = 1;
        }
      }
    if (upd && cnt == n) omimi();
  }
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      printf("%d%c", a[i][j]+d[i]-d[j], " \n"[j==n]);
}
