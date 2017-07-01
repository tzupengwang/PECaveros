#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

inline LL solve(LL n) {
  if (n == 1) return n;
  for (LL k = 2; k <= n; k++) {
    if (n % k == 0) return -1;
    n -= n/k;
  }
  return n;
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    LL n;
    cin >> n;
    cout << solve(n) << endl;
  }
}
