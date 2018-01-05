#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, int> ii;

int X, A, Y, B, L;

int dp[505][505];
bool ok(int bd) {
  vector<ii> can;
  for (int xi = 0; xi <= X ; xi ++) {
    if (bd <= xi * A) {
      can.push_back(ii(xi, 0));
      break;
    }
    int yi = (bd - xi * A + B - 1) / B;
    if (xi <= X && yi <= Y)
      can.push_back(ii(xi, yi));

    if (yi == 0 || xi == X) break;
  }
  int got = 0;
  for (int i = 0; i <= X; i ++) {
    for (int j = 0; j <= Y; j ++) {
      dp[i][j] = -1;
    }
  }
  dp[0][0] = 0;
  for (int i = 0; i <= X; i ++) {
    for (int j = 0; j <= Y; j ++) if (dp[i][j] != -1) {
      if( dp[i][j] >= L ) return true;
      got = max(got, dp[i][j]);
      for (ii x: can) {
        if (i + x.first <= X && j + x.second <= Y) 
          dp[i + x.first][j + x.second] = max(dp[i + x.first][j + x.second],
                                              dp[i][j] + 1);
      }
    }
  }
  return false;
  //return got >= L;
}

int main(){
  while (scanf("%d%d%d%d%d", &X, &A, &Y, &B, &L) == 5) {
    if (A == B) {
      int ans = (X + Y) / L * A;
      printf("%d\n", ans);
    } else {
      if (A < B) {
        swap(A, B);
        swap(X, Y);
      }

      int l = 0, r = 600000;
      while (l < r) {
        int mid = (l + r + 1) / 2;
        if (ok(mid)) l = mid;
        else r = mid - 1;
      }
      printf("%d\n", l);
    }
  }
}


