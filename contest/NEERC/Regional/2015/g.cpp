#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

const int N = 10010;
const int C = 1010;

int n, k;
int id[N][C];
pii ans[N];

void fail() {
  puts("-1");
  exit(0);
}

int main(){
#ifndef EDDY
  freopen( "generators.in" , "r" , stdin );
  freopen( "generators.out" , "w" , stdout );
#endif
  scanf("%d%d", &n, &k);
  int av = 0;
  vector<pii> ac;
  for (int i = 1; i <= n; ++i) {
    int x0, a, b, c;
    scanf("%d%d%d%d", &x0, &a, &b, &c);
    int cur = x0, j = 1;
    int mx = 0;
    while (id[i][cur] == 0) {
      mx = max(mx, cur);
      id[i][cur] = j++;
      cur = (a*cur+b) % c;
    }
    av += mx;
    ans[i] = {id[i][mx], mx};
  }
  if (av % k == 0) {
    int desc = av+1, tid = -1;
    for (int i = 1; i <= n; ++i) {
      int x = ans[i].second;
      for (int j = x-1; j >= 0; --j) if (id[i][j] != 0) {
        if ((av - x + j) % k != 0) {
          if (x-j < desc) {
            desc = x-j;
            tid = i;
          }
          x = j;
          break;
        }
      }
    }
    if (tid == -1) fail();
    av -= desc;
    int nx = ans[tid].second - desc;
    ans[tid] = {id[tid][nx], nx};
  }
  printf("%d\n", av);
  for (int i = 1; i <= n; ++i) {
    printf("%d%c", ans[i].first-1, " \n"[i == n]);
  }
}
