
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 16;
const int X = 111;
const int S = (1<<15)+10;

int n, x, y, a[N];

vector<int> ok[X][X];
int _cs;

void main2() {
  scanf("%d%d", &x, &y);
  for (int i = 0; i < n; ++i) scanf("%d", a+i);
  for (int i = 1; i <= x; ++i) for (int j = 1; j <= y; ++j) {
    ok[i][j].clear();
    for (int k = 0; k < n; ++k) if (i*j == a[k]) {
      ok[i][j].push_back((1 << k));
    }
  }
  for (int i = 1; i <= x; ++i) for (int j = 1; j <= y; ++j) {
    for (int k = 1; k < j; ++k) {
      // i*k i*(j-k)
      for (int s1: ok[i][k]) for (int s2: ok[i][j-k]) if ((s1 & s2) == 0) {
        ok[i][j].push_back(s1 | s2);
      }
    }
    for (int k = 1; k < i; ++k) {
      // k*j (i-k)*j
      for (int s1: ok[k][j]) for (int s2: ok[i - k][j]) if ((s1 & s2) == 0) {
        ok[i][j].push_back(s1 | s2);
      }
    }
    sort(ok[i][j].begin(), ok[i][j].end());
    ok[i][j].resize(unique(ok[i][j].begin(), ok[i][j].end()) - ok[i][j].begin());
  }
  bool flag = 0;
  for (int s: ok[x][y]) if (s == (1 << n) - 1) flag = 1;
  printf("Case %d: ", ++_cs);
  puts(flag? "Yes": "No");
}

int main(){
  while (scanf("%d", &n) == 1 && n) {
    main2();
  }
}
