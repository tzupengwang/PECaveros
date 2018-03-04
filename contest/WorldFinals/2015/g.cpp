
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double D;

const int INF = 1e9;

D l, v1, v2, t, s;

D bp[33];
int dp[33];

int f(D len) {
  if (len <= t) return 0;
  return f(len/2) + 1;
  int ilen = ceil(len / t);
  int res = 0;
  while (ilen) {
    res++;
    ilen /= 2;
  }
  return res;
}

void main2() {
  cin >> l >> v1 >> v2 >> t >> s;
  for (int i = 0; i <= 30; ++i) {
    D L = l / s / (i+1);
    bp[i] = L;
  }
  bp[30] = 0;
  if (v2 > bp[0]) {
    puts("impossible");
    return;
  }
  for (int i = 0; i <= 30; ++i) {
    dp[i] = INF;
    if (v2 <= bp[i]) dp[i] = 0;
    else {
      for (int j = i-1; j >= 0; --j) {
        int t1 = dp[j];
        int t2 = f(min(v2, bp[j]+t) - max(bp[i], v1));
        if (t1 + t2 <= i and t2 <= j+1) {
          dp[i] = min(dp[i], t1+t2);
        }
      }
    }
  }
  if (dp[30] >= INF) {
    puts("impossible");
    return;
  }
  printf("%d\n", dp[30]);
}

int main(){
  int tc; scanf("%d", &tc);
  while (tc--) main2();
}
