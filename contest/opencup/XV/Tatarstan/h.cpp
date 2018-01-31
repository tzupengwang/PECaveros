#include<bits/stdc++.h>
using namespace std;

int main() {
  int n, s, f;
  int ans = 0;
  scanf("%d%d%d", &n, &s, &f);
  if (s > f) swap(s, f);
  if (s > 1) ans ++, s ++;
  if (f < n) ans ++, f --;
  if (s > f) puts("-1");
  else {
    int k = f - s;
    ans += (k + 2) / 3 + (k % 3 == 2);
    printf("%d\n", ans);
  }
}
