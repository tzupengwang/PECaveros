#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ll x1, x2, y1, y2;
  scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);

  if (y1 > y2 || (y1 == y2 && x1 > x2)) {
    swap(x1, x2);
    swap(y1, y2);
  }

  if (x1 <= x2) {
    ll dt = 4;
    dt = max(dt, y2 - y1);
    dt = max(dt, x2 - x1);
    printf("%lld\n", dt * 3 + 2);
  } else {
    ll dt = 4;
    dt = max(dt, y2 - y1 + x1 - x2);
    printf("%lld\n", dt * 3 + 2);
  }
}
