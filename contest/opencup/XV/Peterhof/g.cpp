#include<bits/stdc++.h>
using namespace std;

int n, a, b;

bool s[55][55];

void print(vector<int> v1, vector<int> v2, bool ss) {
  printf("%d", (int)v1.size());
  for (int x : v1) printf(" %d", x);
  printf(" %c %d", "^="[ss], (int)v2.size());
  for (int x : v2) printf(" %d", x);
}

bool usd[55];

void go() {
  printf("1000\n");
  int cnt = 0;
  for (int i = 1; i <= n; i ++) {
    for (int j = i + 1; j <= n; j ++) if (s[i][j] == false) {
      vector<int> v1, v2;
      memset(usd, false, sizeof usd);
      usd[i] = usd[j] = true;
      v1.push_back(i);
      v2.push_back(j);
      int pt = 1;
      while ((int)v1.size() < n / 2) {
        while (usd[pt]) pt ++;
        usd[pt] = true;
        v1.push_back(pt);
      }
      while ((int)v2.size() < n / 2) {
        while (usd[pt]) pt ++;
        usd[pt] = true;
        v2.push_back(pt);
      }
      for (int x : v1)
        for (int y : v2) s[x][y] = true;
      print(v1, v2, false);
      cnt ++;
    }
  }
  while (cnt < 1000) {
    cnt ++;
    print({1}, {2, 3}, false);
  }
}

int main() {
  scanf("%d%d%d", &n, &a, &b);

  if (n % 2) puts("-1");
  else {
    if (a % 2 == 0) {
      printf("1\n");
      printf("%d", n / 2);
      for (int i = 1; i <= n / 2; i ++) printf(" %d", i);
      printf(" = %d", n / 2);
      for (int i = n / 2 + 1; i <= n; i ++) printf(" %d", i);
      puts("");
    } else {
      if (a == 3 && b == 2) {
        printf("4\n");
        printf("%d", 4);
        for (int i = 1; i <= 4; i ++) printf(" %d", i);
        printf(" ^ ");
        printf("%d", 4);
        for (int i = 5; i <= 8; i ++) printf(" %d", i);
        puts("");

        printf("%d", (n - 8) / 2);
        for (int i = 9; i <= (n + 8) / 2; i ++) printf(" %d", i);
        printf(" ^ ");
        printf("%d", (n - 8) / 2);
        for (int i = (n + 8) / 2 + 1; i <= n; i ++) printf(" %d", i);
        puts("");

        printf("%d", n / 2);
        for (int i = 1; i <= 4; i ++) printf(" %d", i);
        for (int i = 9; i <= (n + 8) / 2; i ++) printf(" %d", i);
        printf(" ^ ");
        printf("%d", n / 2);
        for (int i = 5; i <= 8; i ++) printf(" %d", i);
        for (int i = (n + 8) / 2 + 1; i <= n; i ++) printf(" %d", i);
        puts("");

        printf("%d", n / 2);
        for (int i = 5; i <= 8; i ++) printf(" %d", i);
        for (int i = 9; i <= (n + 8) / 2; i ++) printf(" %d", i);
        printf(" ^ ");
        printf("%d", n / 2);
        for (int i = 1; i <= 4; i ++) printf(" %d", i);
        for (int i = (n + 8) / 2 + 1; i <= n; i ++) printf(" %d", i);
        puts("");
      } else if (a == 3 && b == 4) {
        printf("5\n");
        printf("%d", 4);
        for (int i = 1; i <= 4; i ++) printf(" %d", i);
        printf(" ^ ");
        printf("%d", 4);
        for (int i = 5; i <= 8; i ++) printf(" %d", i);
        puts("");

        printf("%d", 4);
        for (int i = 9; i <= 12; i ++) printf(" %d", i);
        printf(" ^ ");
        printf("%d", 4);
        for (int i = 13; i <= 16; i ++) printf(" %d", i);
        puts("");

        printf("%d", (n - 16) / 2);
        for (int i = 17; i <= (n + 16) / 2; i ++) printf(" %d", i);
        printf(" ^ ");
        printf("%d", (n - 16) / 2);
        for (int i = (n + 16) / 2 + 1; i <= n; i ++) printf(" %d", i);
        puts("");

        printf("%d", (n - 16) / 2 + 4);
        for (int i = 1; i <= 4; i ++) printf(" %d", i);
        for (int i = 17; i <= (n + 16) / 2; i ++) printf(" %d", i);
        printf(" ^ ");
        printf("%d", (n - 16) / 2 + 4);
        for (int i = 5; i <= 8; i ++) printf(" %d", i);
        for (int i = (n + 16) / 2 + 1; i <= n; i ++) printf(" %d", i);
        puts("");

        printf("%d", (n - 16) / 2 + 4);
        for (int i = 9; i <= 12; i ++) printf(" %d", i);
        for (int i = 17; i <= (n + 16) / 2; i ++) printf(" %d", i);
        printf(" ^ ");
        printf("%d", (n - 16) / 2 + 4);
        for (int i = 13; i <= 16; i ++) printf(" %d", i);
        for (int i = (n + 16) / 2 + 1; i <= n; i ++) printf(" %d", i);
        puts("");
      } else if (a == 1 && b == 2) {
        go();
      }
    }
  }
}
