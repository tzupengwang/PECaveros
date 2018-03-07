#include<bits/stdc++.h>
using namespace std;

bool win(int p, int q, int n) {
  if (n % p == 0) return true;
  if (p > q) {
    if (n >= p) {
      if (n < p + q) return (n - p) % (p - q) == 0;
      return !win(q, p, n % p);
    } else return false;
  } else {
    if (n >= p) return true;
    else return !win(q, p, n + p);
  }
}

int main() {
  int T; scanf("%d", &T);
  while (T --) {
    int p, q, n;
    scanf("%d%d%d", &p, &q, &n);

    int gcd = __gcd(p, q);
    if (n % gcd) {
      puts("R");
      continue;
    }
    p /= gcd, q /= gcd, n /= gcd;

    if (win(p, q, n)) puts("E");
    else puts("P");
  }
}
