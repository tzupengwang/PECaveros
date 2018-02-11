
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 3e5+10;

int k, n, m;
int ip[N], ans[N];

void fail() { puts("-1"); exit(0); }

int main(){
  scanf("%d%d%d", &k, &n, &m);
  if (k > n) fail();
  for (int i = 1; i <= k; ++i) {
    scanf("%d", ip+i);
  }
  int prv = (ip[1]==-1)? 1: ip[1];
  int cur = 1;
  for (int i = 1; i <= k; ++i) {
    if (ip[i] == -1) ip[i] = prv;
    else if (prv > ip[i]) fail();
    for (int j = m; j > ip[i]; --j) {
      if (n-cur+1 <= k-i+1) break;
      ans[cur++] = j;
    }
    if (n-cur+1 < k-i+1) fail();
    ans[cur++] = ip[i];
    prv = ip[i];
  }
  if (cur != n+1) fail();
  for (int i = 1; i <= n; ++i) printf("%d%c", ans[i], " \n"[i == n]);
}
