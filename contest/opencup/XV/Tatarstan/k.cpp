#include<bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
int n, k, m;

ii solve(int x) {
  if (n <= 2 * k + 1) {
    if (x == 1) return ii(k - (n - 1) / 2, k - (n - 1) / 2);
    else if (x % 2 == 0) return ii(0, 0);
    else return ii(1, 1);
  } else if (n == 2 * k + 2) {
    if (x == 1) return ii(0, 0);
    else if (x == 2) return ii(0, 1);
    else if (x % 2 == 1) return ii(0, 1);
    else return ii(0, 0);
  } else if (n == 2 * k + 3) {
    if (x == 1) return ii(-1, -1);
    x --;

    if (x == 1) return ii(0, 0);
    else if (x == 2) return ii(0, 1);
    else if (x % 2 == 1) return ii(0, 1);
    else return ii(0, 0);
  } else {
    int nw = 2 * k + 2;
    int lnd = 0;
    while (true) {
      int nd = nw - 2 * k;
      if (nw + nd > n) {
        break;
      }

      nw += nd;
      lnd = nd;
    }

    int bnd = n - nw;
    if (x <= bnd) return ii(-1, -1);
    x -= bnd;
    if (x <= lnd) return ii(0, 0);
    else return ii(0, 1);
  }
}

int main() {

  scanf("%d%d%d", &n, &k, &m);
  for (int i = 0; i < m; i ++) {
    int x; scanf("%d", &x);
    ii aa = solve(x);
    printf("%d %d\n", aa.first, aa.second);
  }

}
