#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

ll f(ll a, ll b , ll n) {
  if (n >= a && n >= b) {
    if (b <= n - a - 1) return (b + 1) * (a + 1);
    else return (n - a) * (a + 1) + (a + n - b + 2) * (a + b - n + 1) / 2;
  } else if (n >= a && n < b) {
    return (n - a) * (a + 1) + (a + 2) * (a + 1) / 2;
  } else if (n < a && n >= b) {
    return (n + n - b + 2) * (b + 1) / 2;
  } else {
    return (n + 2) * (n + 1) / 2;
  }
}

ll go() {
  ll al, ar, bl, br, cl, cr, nn;
  scanf("%lld%lld%lld%lld%lld%lld%lld", &al, &ar, &bl, &br, &cl, &cr, &nn);
  ll a = ar - al;
  ll b = br - bl;
  ll c = cr - cl;
  ll n = nn - al - bl - cl;

  if (n < 0) return 0;
  if (n <= c) return f(a, b, n);
  else return f(a, b, n) - f(a, b, n - c - 1);
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i ++) {
    printf("Case #%d: %lld\n", i, go() % 1000000007);
  }
}
