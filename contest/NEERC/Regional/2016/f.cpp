#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
char s[1000005];
double dp[1000005];

int main() {
  freopen( "foreign.in" , "r" , stdin );
  freopen( "foreign.out" , "w" , stdout );

  scanf("%s", s + 1);
  int n = strlen(s + 1);
  reverse(s + 1, s + n + 1);

  ll ws = 0, cs = 0;
  double tdp = 0;
  dp[0] = 0;
  for (int i = 1; i <= n; i ++) {
    dp[i] += tdp / i;
    if (s[i] == 'W') {
      dp[i] += (double)cs / i;
      ws += i;
    } else {
      dp[i] += (double)ws / i;
      cs += i;
    }
    tdp += dp[i];
  }
  printf("%.9f\n", dp[n]);
}
