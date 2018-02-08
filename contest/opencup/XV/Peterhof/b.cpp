#include<bits/stdc++.h>
using namespace std;

inline bool g(int x) {
  return (x % 4) == 0;
}

int main() {
  int a, b, c, d, ap, bp;
  scanf("%d%d%d%d", &a, &b, &c, &d);

  ap = a - c, bp = b - d;
  if (ap > bp) {
    swap(a, b);
    swap(c, d);
    swap(ap, bp);
  }

  int ans = 0;

  if (ap == 2) {
    if (bp == 2) {
      if (g(b)) {
        ans += 2;
        if (g(c)) ans += 2;
      }
      if (g(a)) {
        ans += 2;
        if (g(d)) ans += 2;
      }
    } else {
      if (g(b)) ans += 2;
      if (g(a)) {
        ans += 2;
        if (g(d)) ans += 2;
      }
    }
  } else {
    if (g(b)) ans += 2;
    if (g(a)) ans += 2;
  }
  printf("%d\n", ans);
}
