#include <bits/stdc++.h>
using namespace std;

int s[305][305];

int main(){
  int t; scanf("%d", &t);
  while (t--) {
    int n;
    scanf("%d", &n);
    int K = n * (n - 1) / 2;
    for (int i = 0 ; i < K ; i ++) {
      int x, y, z;
      scanf("%d%d%d", &x, &y, &z);
      s[x][y] = s[y][x] = z;
    }
    int ans = -1;
    for (int k = 1; k <= n; k ++) {
      for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) if (i != k && j != k && i != j) {
          int vl = s[i][j] + s[i][k] + s[j][k];
          if (ans == -1) ans = vl;
          else if (ans < vl) ans = vl;
        }
      }
    }
    printf("%d\n", ans);
  }
}
