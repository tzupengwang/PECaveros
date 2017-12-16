#include<bits/stdc++.h>
using namespace std;

int main() {
  int x1, y1, x2, y2;
  while (scanf("%d%d%d%d", &x1, &y1, &x2, &y2)) {
    if (x1 == 0 && x2 == 0 && y1 == 0 && y2 == 0) break;

    if (x1 < x2) {
      swap(x1, x2), swap(y1, y2);
    }

    int ans;
    if (y2 >= y1) {
      int l1 = (x1 + y1) / 2;
      int l2 = (x2 + y2) / 2;
      if (l1 <= l2) {
        ans = (x1 - x2) + (y2 - y1);
      } else 
        ans = (x1 - x2) + (y2 - y1) + (l1 - l2) * 2;
    } else {
      int l1 = (x1 + 1000000000 - y1) / 2;
      int l2 = (x2 + 1000000000 - y2) / 2;
      if (l1 <= l2) {
        ans = (x1 - x2) + (y1 - y2);
      } else 
        ans = (x1 - x2) + (y1 - y2) + (l1 - l2) * 2;
    }
    printf("%d\n", ans);
  }
}
