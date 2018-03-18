#include<bits/stdc++.h>
using namespace std;

int solve1(int n, int m) {
  if (n > m) swap(n, m);
  if (n == m) return n;

  int gcd = __gcd(n - 1, m - 1);
  int l = (n - 1) / gcd;
  l = (l - 1) / 2 + 1;
  return l * m;
  //int c = (m - 1 + n - 2) / (n - 1);
  int c = (m - 1) / (n - 1);
  return 1 + l * (m - 1) - l * (l - 1) / 2 * c;
}

typedef pair<int, int> ii;
bool vs[35][35];

int solve2(int n, int m) {
  ii p = ii(2, 2);
  ii dir = ii(1, 1);

  for (int i = 1; i <= n; i ++)
    for (int j = 1; j <= m; j ++)
      vs[i][j] = false;
  vs[1][1] = true;

  while (true) {
    vs[p.first][p.second] = true;

    if (p == ii(1, 1)) break;
    if (p == ii(1, m)) break;
    if (p == ii(n, 1)) break;
    if (p == ii(n, m)) break;

    if (p.first == n || p.first == 1) dir.first = -dir.first;
    if (p.second == m || p.second == 1) dir.second = -dir.second;

    p.first += dir.first;
    p.second += dir.second;
  }
  int cnt = 0;
  for (int i = 1; i <= n; i ++)
    for (int j = 1; j <= m; j ++)
      if (vs[i][j]) cnt ++;
  return cnt;
}

int main() {
  for (int i = 2; i <= 10; i ++) {
    for (int j = 2; j <= 10; j ++) {
      int a1 = solve1(i, j);
      int a2 = solve2(i, j);

      if (a1 != a2) {
        printf("%d, %d: ", i, j);
        printf("fail %d %d\n", a1, a2);
      }
    }
  }
}
