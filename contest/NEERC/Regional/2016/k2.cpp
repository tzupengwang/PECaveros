#include<bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;

struct B {
  int n, m;
  char s[3005][3005];
  void input() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i ++) {
      scanf("%s", s[i]);
    }
  }
  ii tl() {
    for (int i = 0; i < n; i ++) {
      for (int j = 0; j < m; j ++) {
        if (s[i][j] == '*') return ii(i, j);
      }
    }
  }
} x, y, z;

ii cross(B &a, B &b, B &c) {
}

int main() {
  x.input();
  y.input();
  z.input();
}
